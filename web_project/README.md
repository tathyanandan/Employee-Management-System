# PeopleDesk Employee Management System

A small browser-based version of the Employee Management System in `source.cpp`.
It has a responsive frontend and a Node.js backend that exposes a JSON API and saves data in `data/db.json`.

## Run it

1. Install Node.js if it is not already installed.
2. Open this folder in File Explorer.
3. Double-click `run.bat`.
4. Open `http://localhost:3000` in your browser.

The project uses only built-in Node.js modules, so you do not need to run `npm install`.
Keep the terminal window open while using the app. Press `Ctrl+C` in that window to stop it.

## Demo sign-ins

| Role | ID | Password |
|---|---|---|
| Admin | `Abhinav` | `1234` |
| Employee | `E001` | `emp123` |
| Employee | `E002` | `emp123` |

The employee list starts empty. Add employees from the admin workspace; each employee's temporary password is entered during creation.

## Features

- Admin overview with employee, task, overdue-task, and latest payroll totals
- Add employees and change employee account status
- Assign tasks and update task progress from employee accounts
- Generate salary slips with basic salary, bonus, deductions, and penalties
- Payroll and illustrative tax reports (the 10% tax estimate mirrors the assumption in the C++ source)
- Employee view for assigned work and the latest salary slip
- Persistent JSON storage in `data/db.json`; records remain after the server is stopped and restarted

## Project files

- `public/` — browser frontend (HTML, CSS, JavaScript)
- `server.js` — Node.js HTTP server, API, sign-in, and data persistence
- `data/db.json` — created on first run and updated as you use the app; do not delete it if you want to keep your records
- `source.cpp` — the C++ source you provided, included as the feature reference

This is a classroom/demo project. It keeps passwords in a local JSON file and uses an in-memory session, so do not expose it to the public internet or use real employee information. On startup, it removes the old built-in sample employees (Asha Shah and Rohan Patel) from an earlier version while preserving other employee records.
