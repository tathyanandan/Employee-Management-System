const http = require('http');
const fs = require('fs');
const path = require('path');
const crypto = require('crypto');

const ROOT = __dirname;
const PUBLIC = path.join(ROOT, 'public');
const DATA_FILE = path.join(ROOT, 'data', 'db.json');
const PORT = Number(process.env.PORT || 3000);
const sessions = new Map();

function initialData() {
  return {
    currentDay: 1,
    nextTaskId: 1,
    nextSlipNumber: 1,
    employees: []
  };
}

function loadData() {
  try {
    const data = JSON.parse(fs.readFileSync(DATA_FILE, 'utf8'));
    // Remove only the two built-in demo employees from data files created by
    // earlier versions. Keep any employees the admin has added.
    const before = (data.employees || []).length;
    data.employees = (data.employees || []).filter(e => !(
      (e.id === 'E001' && e.name === 'Asha Shah') ||
      (e.id === 'E002' && e.name === 'Rohan Patel')
    ));
    if (data.employees.length !== before) saveData(data);
    return data;
  }
  catch { const data = initialData(); saveData(data); return data; }
}
function saveData(data) { fs.mkdirSync(path.dirname(DATA_FILE), { recursive: true }); fs.writeFileSync(DATA_FILE, JSON.stringify(data, null, 2)); }
let db = loadData();

function send(res, status, body, type = 'application/json; charset=utf-8') {
  res.writeHead(status, { 'Content-Type': type, 'Cache-Control': 'no-store', 'X-Content-Type-Options': 'nosniff' });
  res.end(type.startsWith('application/json') ? JSON.stringify(body) : body);
}
function readBody(req) {
  return new Promise((resolve, reject) => {
    let raw = '';
    req.on('data', chunk => { raw += chunk; if (raw.length > 1e6) req.destroy(); });
    req.on('end', () => { try { resolve(raw ? JSON.parse(raw) : {}); } catch { reject(new Error('Request body must be valid JSON.')); } });
    req.on('error', reject);
  });
}
function safeEmployee(e) {
  const { password, ...safe } = e;
  return safe;
}
function auth(req) {
  const token = (req.headers.authorization || '').replace(/^Bearer\s+/i, '');
  return sessions.get(token) || null;
}
function requireRole(req, res, role) {
  const user = auth(req);
  if (!user) { send(res, 401, { error: 'Please sign in again.' }); return null; }
  if (role && user.role !== role) { send(res, 403, { error: 'You do not have permission for this action.' }); return null; }
  return user;
}
function num(value, label, min = 0, max = Number.MAX_SAFE_INTEGER) {
  const n = Number(value);
  if (!Number.isFinite(n) || n < min || n > max) throw new Error(`${label} must be between ${min} and ${max}.`);
  return n;
}
function routeApi(req, res, url) {
  (async () => {
    const method = req.method;
    const parts = url.pathname.split('/').filter(Boolean).map(decodeURIComponent);
    const body = ['POST', 'PATCH', 'PUT'].includes(method) ? await readBody(req) : {};

    if (method === 'POST' && parts.join('/') === 'api/login') {
      const { id = '', password = '' } = body;
      let user;
      if (String(id).trim().toLowerCase() === 'abhinav' && password === '1234') user = { id: 'admin', name: 'Abhinav', role: 'admin' };
      else {
        const employee = db.employees.find(e => e.id.toLowerCase() === String(id).trim().toLowerCase() && e.password === password);
        if (employee && employee.status === 'ACTIVE') user = { id: employee.id, name: employee.name, role: 'employee' };
      }
      if (!user) return send(res, 401, { error: 'ID or password is incorrect, or the account is inactive.' });
      const token = crypto.randomBytes(24).toString('hex'); sessions.set(token, user);
      return send(res, 200, { token, user });
    }
    if (method === 'POST' && parts.join('/') === 'api/logout') {
      const token = (req.headers.authorization || '').replace(/^Bearer\s+/i, ''); sessions.delete(token);
      return send(res, 200, { ok: true });
    }

    if (method === 'GET' && parts.join('/') === 'api/me') {
      const user = requireRole(req, res); if (!user) return;
      if (user.role === 'employee') {
        const e = db.employees.find(x => x.id === user.id);
        if (!e || e.status !== 'ACTIVE') return send(res, 401, { error: 'This employee account is no longer active.' });
        return send(res, 200, { user, employee: safeEmployee(e) });
      }
      return send(res, 200, { user });
    }

    if (parts[0] !== 'api') return send(res, 404, { error: 'API route not found.' });
    const user = requireRole(req, res); if (!user) return;

    if (method === 'GET' && parts.join('/') === 'api/dashboard') {
      if (user.role === 'employee') {
        const e = db.employees.find(x => x.id === user.id);
        return send(res, 200, { employee: safeEmployee(e), taskCount: e.tasks.length, completedTasks: e.tasks.filter(t => t.progress === 100).length });
      }
      const active = db.employees.filter(e => e.status === 'ACTIVE').length;
      const slips = db.employees.map(e => e.salarySlip).filter(Boolean);
      const payroll = slips.reduce((sum, s) => sum + s.netSalary, 0);
      const tasks = db.employees.flatMap(e => e.tasks.map(t => ({ ...t, employeeId: e.id, employeeName: e.name })));
      return send(res, 200, { employees: db.employees.length, active, tasks: tasks.length, overdue: tasks.filter(t => db.currentDay > t.dueDay && t.progress < 100).length, payroll, recentTasks: tasks.slice(-5).reverse() });
    }
    if (method === 'GET' && parts.join('/') === 'api/employees') {
      if (user.role === 'employee') return send(res, 200, [safeEmployee(db.employees.find(e => e.id === user.id))]);
      return send(res, 200, db.employees.map(safeEmployee));
    }
    if (method === 'POST' && parts.join('/') === 'api/employees') {
      if (user.role !== 'admin') return send(res, 403, { error: 'Admin access required.' });
      const id = String(body.id || '').trim();
      const name = String(body.name || '').trim(); const email = String(body.email || '').trim(); const password = String(body.password || '');
      if (!id || !name || !email || !password) return send(res, 400, { error: 'Employee ID, name, email, and password are required.' });
      if (db.employees.some(e => e.id.toLowerCase() === id.toLowerCase())) return send(res, 409, { error: 'That employee ID already exists.' });
      const employee = { id, name, email, password, status: 'ACTIVE', tasks: [], salarySlip: null, pendingPenalty: 0 };
      db.employees.push(employee); saveData(db); return send(res, 201, safeEmployee(employee));
    }
    if (method === 'PATCH' && parts[1] === 'employees' && parts.length === 4 && parts[3] === 'status') {
      if (user.role !== 'admin') return send(res, 403, { error: 'Admin access required.' });
      const e = db.employees.find(x => x.id === parts[2]); if (!e) return send(res, 404, { error: 'Employee not found.' });
      if (!['ACTIVE', 'INACTIVE', 'ON_LEAVE', 'TERMINATED'].includes(body.status)) return send(res, 400, { error: 'Invalid employee status.' });
      e.status = body.status; saveData(db); return send(res, 200, safeEmployee(e));
    }
    if (method === 'DELETE' && parts[1] === 'employees' && parts.length === 3) {
      if (user.role !== 'admin') return send(res, 403, { error: 'Admin access required.' });
      const i = db.employees.findIndex(e => e.id === parts[2]); if (i < 0) return send(res, 404, { error: 'Employee not found.' });
      db.employees.splice(i, 1); saveData(db); return send(res, 200, { ok: true });
    }
    if (method === 'GET' && parts.join('/') === 'api/tasks') {
      const employees = user.role === 'admin' ? db.employees : db.employees.filter(e => e.id === user.id);
      return send(res, 200, employees.flatMap(e => e.tasks.map(t => ({ ...t, employeeId: e.id, employeeName: e.name, late: db.currentDay > t.dueDay && t.progress < 100 }))));
    }
    if (method === 'POST' && parts.join('/') === 'api/tasks') {
      if (user.role !== 'admin') return send(res, 403, { error: 'Admin access required.' });
      const employee = db.employees.find(e => e.id === String(body.employeeId || ''));
      if (!employee) return send(res, 404, { error: 'Employee not found.' });
      const title = String(body.title || '').trim(); if (!title) return send(res, 400, { error: 'Task title is required.' });
      const task = { id: db.nextTaskId++, title, description: String(body.description || '').trim(), dueDay: num(body.dueDay, 'Due day', 1), progress: 0 };
      employee.tasks.push(task); saveData(db); return send(res, 201, { ...task, employeeId: employee.id, employeeName: employee.name });
    }
    if (method === 'PATCH' && parts[1] === 'tasks' && parts.length === 5 && parts[4] === 'progress') {
      const employee = db.employees.find(e => e.id === parts[2]);
      if (!employee || (user.role === 'employee' && employee.id !== user.id)) return send(res, 404, { error: 'Employee or task not found.' });
      const task = employee.tasks.find(t => t.id === Number(parts[3])); if (!task) return send(res, 404, { error: 'Task not found.' });
      task.progress = num(body.progress, 'Progress', 0, 100); saveData(db); return send(res, 200, task);
    }
    if (method === 'POST' && parts.join('/') === 'api/payroll') {
      if (user.role !== 'admin') return send(res, 403, { error: 'Admin access required.' });
      const employee = db.employees.find(e => e.id === String(body.employeeId || '')); if (!employee) return send(res, 404, { error: 'Employee not found.' });
      const basic = num(body.basicSalary, 'Basic salary'); const bonus = num(body.bonus || 0, 'Bonus'); const deductions = num(body.deductions || 0, 'Deductions');
      let penalties = num(body.penalties ?? employee.pendingPenalty ?? 0, 'Penalties');
      const late = employee.tasks.some(t => db.currentDay > t.dueDay && t.progress < 100);
      if (late && penalties === 0 && Number(body.penaltyPerDay) > 0) penalties = num(body.penaltyPerDay, 'Penalty per day') * num(body.delayDays, 'Delay days', 0);
      const slip = { slipId: `SLIP${db.nextSlipNumber++}`, employeeId: employee.id, employeeName: employee.name, basicSalary: basic, earnings: bonus, deductions, penalties, netSalary: basic + bonus - deductions - penalties, createdAt: new Date().toISOString() };
      employee.salarySlip = slip; employee.pendingPenalty = 0; saveData(db); return send(res, 201, slip);
    }
    if (method === 'GET' && parts.join('/') === 'api/reports') {
      if (user.role !== 'admin') return send(res, 403, { error: 'Admin access required.' });
      const slips = db.employees.filter(e => e.salarySlip).map(e => ({ employeeId: e.id, employeeName: e.name, status: e.status, slip: e.salarySlip, estimatedTax: e.salarySlip.basicSalary * 0.10 }));
      return send(res, 200, { employees: db.employees.map(safeEmployee), payroll: { employees: db.employees.length, active: db.employees.filter(e => e.status === 'ACTIVE').length, totalNetSalary: slips.reduce((s, x) => s + x.slip.netSalary, 0), slips }, tax: { note: 'Illustrative estimate: 10% of basic salary when a salary slip exists.', totalEstimatedTax: slips.reduce((s, x) => s + x.estimatedTax, 0), employees: slips } });
    }
    if (method === 'GET' && parts.join('/') === 'api/salary-slip') {
      const employee = db.employees.find(e => e.id === (user.role === 'employee' ? user.id : url.searchParams.get('employeeId')));
      if (!employee) return send(res, 404, { error: 'Employee not found.' });
      return send(res, 200, employee.salarySlip || {});
    }
    return send(res, 404, { error: 'API route not found.' });
  })().catch(error => send(res, 400, { error: error.message || 'Request failed.' }));
}

const MIME = { '.html': 'text/html; charset=utf-8', '.css': 'text/css; charset=utf-8', '.js': 'text/javascript; charset=utf-8', '.json': 'application/json; charset=utf-8', '.ico': 'image/x-icon' };
const server = http.createServer((req, res) => {
  const url = new URL(req.url, `http://${req.headers.host || 'localhost'}`);
  if (url.pathname.startsWith('/api/')) return routeApi(req, res, url);
  const requested = url.pathname === '/' ? '/index.html' : decodeURIComponent(url.pathname);
  const file = path.resolve(PUBLIC, `.${requested}`);
  if (!file.startsWith(PUBLIC + path.sep)) return send(res, 403, 'Forbidden', 'text/plain; charset=utf-8');
  fs.readFile(file, (err, data) => err ? send(res, 404, 'Not found', 'text/plain; charset=utf-8') : send(res, 200, data, MIME[path.extname(file)] || 'application/octet-stream'));
});
server.listen(PORT, () => console.log(`Employee Management System running at http://localhost:${PORT}`));
