#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <exception>

using namespace std;

// Custom Exception Handling

class AppException : public exception {
private:
    string message;

public:
    AppException(const string& msg) {
        message = msg;
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Basic Function Template

template <class T>
T addValues(T a, T b) {
    return a + b;
}

// User Base Class
// Core OOP: Encapsulation, Abstraction and Inheritance

class User {
private:
    string password;

protected:
    string userId;
    string name;

public:
    User() {
        userId = "";
        name = "";
        password = "";
    }

    User(string id, string userName, string pass) {
        userId = id;
        name = userName;
        password = pass;
    }

    virtual ~User() {}

    string getId() const {
        return userId;
    }

    string getName() const {
        return name;
    }

    void setName(string userName) {
        if (userName.empty()) {
            throw AppException("Name cannot be empty.");
        }
        name = userName;
    }

    bool login(string enteredPassword) const {
        return password == enteredPassword;
    }

    virtual void logout() const = 0;
    virtual void showRole() const = 0;
};

// Employee Status

enum EmployeeStatus {
    ACTIVE,
    INACTIVE,
    ON_LEAVE,
    TERMINATED
};

string statusToString(EmployeeStatus status) {
    if (status == ACTIVE) return "ACTIVE";
    if (status == INACTIVE) return "INACTIVE";
    if (status == ON_LEAVE) return "ON_LEAVE";
    if (status == TERMINATED) return "TERMINATED";

    return "UNKNOWN";
}

// Task Class

class Task {
private:
    static int nextId;

    int taskId;
    string title;
    string description;
    int dueDay;
    int progress;

public:
    Task() {
        taskId = nextId++;
        title = "Untitled";
        description = "";
        dueDay = 1;
        progress = 0;
    }

    Task(string taskTitle, string taskDescription, int dueDayNumber) {
        if (taskTitle.empty()) {
            throw AppException("Task title cannot be empty.");
        }

        if (dueDayNumber < 1) {
            throw AppException("Due day must be at least 1.");
        }

        taskId = nextId++;
        title = taskTitle;
        description = taskDescription;
        dueDay = dueDayNumber;
        progress = 0;
    }

    int getId() const {
        return taskId;
    }

    string getTitle() const {
        return title;
    }

    int getDueDay() const {
        return dueDay;
    }

    int getProgress() const {
        return progress;
    }

    void updateProgress(int value) {
        if (value < 0 || value > 100) {
            throw AppException("Progress must be between 0 and 100.");
        }

        progress = value;
    }

    bool isLate(int currentDay) const {
        return currentDay > dueDay && progress < 100;
    }

    void display() const {
        cout << "Task ID: " << taskId
             << " | Title: " << title
             << " | Due day: " << dueDay
             << " | Progress: " << progress << "%\n";

        cout << "Description: " << description << "\n";
    }
};

int Task::nextId = 1;

// Penalty Class

class Penalty {
private:
    string reason;
    double amountPerDay;
    int delayDays;

public:
    Penalty() {
        reason = "Late task";
        amountPerDay = 0;
        delayDays = 0;
    }

    Penalty(string why, double rate, int days) {
        if (rate < 0 || days < 0) {
            throw AppException("Penalty rate and delay days cannot be negative.");
        }

        reason = why;
        amountPerDay = rate;
        delayDays = days;
    }

    double calculateAmount() const {
        return amountPerDay * delayDays;
    }

    string getReason() const {
        return reason;
    }

    int getDelayDays() const {
        return delayDays;
    }
};

// Salary Slip Class

class SalarySlip {
private:
    string slipId;
    string employeeId;
    string employeeName;

    double basicSalary;
    double earnings;
    double deductions;
    double penalties;
    double netSalary;

public:
    SalarySlip() {
        slipId = "N/A";
        employeeId = "";
        employeeName = "";
        basicSalary = 0;
        earnings = 0;
        deductions = 0;
        penalties = 0;
        netSalary = 0;
    }

    SalarySlip(string id, string empId, string empName,
               double basic, double extraEarnings,
               double deductionAmount, double penaltyAmount) {

        if (basic < 0 || extraEarnings < 0 ||
            deductionAmount < 0 || penaltyAmount < 0) {
            throw AppException("Salary values cannot be negative.");
        }

        slipId = id;
        employeeId = empId;
        employeeName = empName;
        basicSalary = basic;
        earnings = extraEarnings;
        deductions = deductionAmount;
        penalties = penaltyAmount;

        netSalary = basicSalary + earnings - deductions - penalties;
    }

    double getNetSalary() const {
        return netSalary;
    }

    void display() const {
        cout << "\n========== SALARY SLIP ==========\n";
        cout << "Slip ID: " << slipId << "\n";
        cout << "Employee: " << employeeName
             << " (" << employeeId << ")\n";

        cout << fixed << setprecision(2);

        cout << "Basic salary: Rs. " << basicSalary << "\n";
        cout << "Additional earnings: Rs. " << earnings << "\n";
        cout << "Deductions: Rs. " << deductions << "\n";
        cout << "Penalties: Rs. " << penalties << "\n";
        cout << "Net salary: Rs. " << netSalary << "\n";
        cout << "=================================\n";
    }
};

// Payroll Class
// Function overloading and basic template usage

class Payroll {
private:
    double basicSalary;
    double deductions;
    vector<Penalty> penalties;

public:
    Payroll() {
        basicSalary = 0;
        deductions = 0;
    }

    Payroll(double basic) {
        if (basic < 0) {
            throw AppException("Basic salary cannot be negative.");
        }

        basicSalary = basic;
        deductions = 0;
    }

    void setBasicSalary(double amount) {
        if (amount < 0) {
            throw AppException("Salary cannot be negative.");
        }

        basicSalary = amount;
    }

    double getBasicSalary() const {
        return basicSalary;
    }

    void setDeductions(double amount) {
        if (amount < 0) {
            throw AppException("Deductions cannot be negative.");
        }

        deductions = amount;
    }

    void addPenalty(const Penalty& penalty) {
        penalties.push_back(penalty);
    }

    // Function overloading
    double calculateEarnings() const {
        return basicSalary;
    }

    double calculateEarnings(double bonus) const {
        if (bonus < 0) {
            throw AppException("Bonus cannot be negative.");
        }

        return addValues(basicSalary, bonus);
    }

    double calculatePenaltyTotal() const {
        double total = 0;

        for (int i = 0; i < (int)penalties.size(); i++) {
            total += penalties[i].calculateAmount();
        }

        return total;
    }

    SalarySlip generateSalarySlip(string slipId, string employeeId,
                                  string employeeName, double bonus) const {
        if (bonus < 0) {
            throw AppException("Bonus cannot be negative.");
        }

        return SalarySlip(
            slipId,
            employeeId,
            employeeName,
            basicSalary,
            bonus,
            deductions,
            calculatePenaltyTotal()
        );
    }
};

// Employee Class
// Inheritance: Employee inherits User

class Employee : public User {
private:
    string email;
    EmployeeStatus status;

    vector<Task> tasks;

    SalarySlip latestSlip;
    bool hasSalarySlip;

    double pendingPenalty;

public:
    Employee() : User() {
        email = "";
        status = ACTIVE;
        hasSalarySlip = false;
        pendingPenalty = 0;
    }

    Employee(string id, string employeeName,
             string pass, string employeeEmail)
        : User(id, employeeName, pass) {

        email = employeeEmail;
        status = ACTIVE;
        hasSalarySlip = false;
        pendingPenalty = 0;
    }

    string getEmail() const {
        return email;
    }

    EmployeeStatus getStatus() const {
        return status;
    }

    void setStatus(EmployeeStatus newStatus) {
        status = newStatus;
    }

    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    bool updateTaskProgress(int taskId, int value) {
        for (int i = 0; i < (int)tasks.size(); i++) {
            if (tasks[i].getId() == taskId) {
                tasks[i].updateProgress(value);
                return true;
            }
        }

        return false;
    }

    void viewTasks() const {
        if (tasks.empty()) {
            cout << "No tasks assigned.\n";
            return;
        }

        for (int i = 0; i < (int)tasks.size(); i++) {
            tasks[i].display();
        }
    }

    bool hasLateTask(int currentDay) const {
        for (int i = 0; i < (int)tasks.size(); i++) {
            if (tasks[i].isLate(currentDay)) {
                return true;
            }
        }

        return false;
    }

    void setSalarySlip(const SalarySlip& slip) {
        latestSlip = slip;
        hasSalarySlip = true;
    }

    void viewSalarySlip() const {
        if (hasSalarySlip) {
            latestSlip.display();
        } else {
            cout << "No salary slip has been generated yet.\n";
        }
    }

    void setPendingPenalty(double amount) {
        pendingPenalty += amount;
    }

    double getPendingPenalty() const {
        return pendingPenalty;
    }

    void clearPendingPenalty() {
        pendingPenalty = 0;
    }

    void logout() const override {
        cout << name << " logged out.\n";
    }

    void showRole() const override {
        cout << name << " is an Employee.\n";
    }

    // Friend function
    friend ostream& operator<<(ostream& out, const Employee& employee);
};

ostream& operator<<(ostream& out, const Employee& employee) {
    out << "ID: " << employee.userId
        << " | Name: " << employee.name
        << " | Email: " << employee.email
        << " | Status: " << statusToString(employee.status);

    return out;
}

// Admin Class
// Inheritance: Admin inherits User

class Admin : public User {
private:
    string adminRole;

public:
    Admin() : User() {
        adminRole = "Administrator";
    }

    Admin(string id, string adminName, string pass, string role)
        : User(id, adminName, pass) {

        adminRole = role;
    }

    void logout() const override {
        cout << name << " (admin) logged out.\n";
    }

    void showRole() const override {
        cout << name << " is an Admin.\n";
    }

    string getAdminRole() const {
        return adminRole;
    }
};

// Report Interface
// SOLID: Interface Segregation and Open/Closed Principles

class IReportGenerator {
public:
    virtual ~IReportGenerator() {}

    virtual void generateSummary(const vector<Employee>& employees) const = 0;
    virtual void generateDetailed(const vector<Employee>& employees) const = 0;
};

class PayrollReport : public IReportGenerator {
public:
    void generateSummary(const vector<Employee>& employees) const override {
        int active = 0;

        for (int i = 0; i < (int)employees.size(); i++) {
            if (employees[i].getStatus() == ACTIVE) {
                active++;
            }
        }

        cout << "\n--- Payroll Summary ---\n";
        cout << "Employees: " << employees.size() << "\n";
        cout << "Active employees: " << active << "\n";
        cout << "Detailed salary amounts are available through each employee's salary slip.\n";
    }

    void generateDetailed(const vector<Employee>& employees) const override {
        cout << "\n--- Detailed Employee/Payroll Report ---\n";

        for (int i = 0; i < (int)employees.size(); i++) {
            cout << employees[i] << "\n";
            employees[i].viewSalarySlip();
        }
    }
};

class TaxReport : public IReportGenerator {
public:
    void generateSummary(const vector<Employee>& employees) const override {
        cout << "\n--- Tax Report Summary ---\n";
        cout << "Employees included: " << employees.size() << "\n";
        cout << "Demo assumption: estimated tax is 10% of basic salary "
             << "when a salary slip is generated.\n";
    }

    void generateDetailed(const vector<Employee>& employees) const override {
        cout << "\n--- Detailed Tax Report (illustrative only) ---\n";

        for (int i = 0; i < (int)employees.size(); i++) {
            cout << employees[i].getName()
                 << " (" << employees[i].getId()
                 << "): see salary slip for current salary details.\n";
        }
    }
};

// Employee Management System
// SOLID: Single Responsibility for system operations

class EmployeeManagementSystem {
private:
    vector<Employee> employees;
    Admin admin;

    int nextSlipNumber;
    int currentDay;

    mutex dataMutex;

    Employee* findEmployee(string id) {
        for (int i = 0; i < (int)employees.size(); i++) {
            if (employees[i].getId() == id) {
                return &employees[i];
            }
        }

        return NULL;
    }

    const Employee* findEmployee(string id) const {
        for (int i = 0; i < (int)employees.size(); i++) {
            if (employees[i].getId() == id) {
                return &employees[i];
            }
        }

        return NULL;
    }

    int readInt(string prompt) {
        int value;

        while (true) {
            cout << prompt;

            if (cin >> value) {
                cin.ignore(10000, '\n');
                return value;
            }

            cout << "Please enter a valid whole number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    double readDouble(string prompt) {
        double value;

        while (true) {
            cout << prompt;

            if (cin >> value) {
                cin.ignore(10000, '\n');
                return value;
            }

            cout << "Please enter a valid number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    string readLine(string prompt) {
        string value;
        cout << prompt;
        getline(cin, value);
        return value;
    }

    void adminMenu();
    void employeeMenu(Employee& employee);

    void addEmployee();
    void removeEmployee();
    void assignTask();
    void generatePayroll();
    void showEmployees() const;
    void reportMenu();

    // Thread worker functions
    void processPenalty(string id, string employeeName, int days, double rate);
    void processPayroll(string id, string employeeName,
                        double basic, double bonus,
                        double deductions, double penaltyAmount);

public:
    EmployeeManagementSystem() {
        admin = Admin("admin", "System Admin", "admin123", "Administrator");
        nextSlipNumber = 1;
        currentDay = 1;
    }

    void run() {
        while (true) {
            cout << "\n===== EMPLOYEE MANAGEMENT SYSTEM =====\n";
            cout << "1. Admin login\n";
            cout << "2. Employee login\n";
            cout << "0. Exit\n";

            try {
                int choice = readInt("Choice: ");

                if (choice == 0) {
                    cout << "Goodbye!\n";
                    return;
                }

                if (choice == 1) {
                    string id = readLine("Admin ID: ");
                    string password = readLine("Password: ");

                    if (id != admin.getId() || !admin.login(password)) {
                        throw AppException("Invalid admin login.");
                    }

                    admin.showRole();
                    adminMenu();
                    admin.logout();
                }
                else if (choice == 2) {
                    string id = readLine("Employee ID: ");
                    string password = readLine("Password: ");

                    Employee* employee = findEmployee(id);

                    if (employee == NULL || !employee->login(password)) {
                        throw AppException("Invalid employee ID or password.");
                    }

                    if (employee->getStatus() != ACTIVE) {
                        throw AppException("This employee account is not active.");
                    }

                    employee->showRole();
                    employeeMenu(*employee);
                    employee->logout();
                }
                else {
                    cout << "Choose a valid menu option.\n";
                }
            }
            catch (const AppException& error) {
                cout << "Error: " << error.what() << "\n";
            }
            catch (const exception& error) {
                cout << "Unexpected error: " << error.what() << "\n";
            }
        }
    }
};

// Admin Menu

void EmployeeManagementSystem::adminMenu() {
    while (true) {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1. Add employee\n";
        cout << "2. Remove employee\n";
        cout << "3. List employees\n";
        cout << "4. Assign task\n";
        cout << "5. Generate payroll\n";
        cout << "6. Apply late-task penalty\n";
        cout << "7. Reports\n";
        cout << "8. Set current day\n";
        cout << "0. Logout\n";

        try {
            int choice = readInt("Choice: ");

            if (choice == 0) {
                return;
            }

            switch (choice) {
                case 1:
                    addEmployee();
                    break;

                case 2:
                    removeEmployee();
                    break;

                case 3:
                    showEmployees();
                    break;

                case 4:
                    assignTask();
                    break;

                case 5:
                    generatePayroll();
                    break;

                case 6: {
                    string id = readLine("Employee ID: ");
                    string employeeName;

                    {
                        lock_guard<mutex> lock(dataMutex);

                        Employee* employee = findEmployee(id);

                        if (employee == NULL) {
                            throw AppException("Employee not found.");
                        }

                        if (!employee->hasLateTask(currentDay)) {
                            cout << "No late incomplete tasks found.\n";
                            break;
                        }

                        employeeName = employee->getName();
                    }

                    int days = readInt("Delay days: ");
                    double rate = readDouble("Penalty per day (Rs.): ");

                    // Basic threading: start a thread and wait for its completion.
                    thread penaltyThread(
                        &EmployeeManagementSystem::processPenalty,
                        this, id, employeeName, days, rate
                    );

                    penaltyThread.join();

                    cout << "Penalty application completed.\n";
                    break;
                }

                case 7:
                    reportMenu();
                    break;

                case 8:
                    currentDay = readInt("Current day number: ");

                    if (currentDay < 1) {
                        throw AppException("Day must be at least 1.");
                    }
                    break;

                default:
                    cout << "Choose a valid menu option.\n";
            }
        }
        catch (const AppException& error) {
            cout << "Error: " << error.what() << "\n";
        }
        catch (const exception& error) {
            cout << "Unexpected error: " << error.what() << "\n";
        }
    }
}

// Employee Menu

void EmployeeManagementSystem::employeeMenu(Employee& employee) {
    while (true) {
        cout << "\n--- EMPLOYEE MENU ---\n";
        cout << "1. View my tasks\n";
        cout << "2. Update task progress\n";
        cout << "3. View salary slip\n";
        cout << "0. Logout\n";

        try {
            int choice = readInt("Choice: ");

            if (choice == 0) {
                return;
            }

            if (choice == 1) {
                employee.viewTasks();
            }
            else if (choice == 2) {
                int taskId = readInt("Task ID: ");
                int progress = readInt("Progress (0-100): ");

                if (!employee.updateTaskProgress(taskId, progress)) {
                    cout << "Task not found.\n";
                } else {
                    cout << "Task progress updated.\n";
                }
            }
            else if (choice == 3) {
                employee.viewSalarySlip();
            }
            else {
                cout << "Choose a valid menu option.\n";
            }
        }
        catch (const AppException& error) {
            cout << "Error: " << error.what() << "\n";
        }
        catch (const exception& error) {
            cout << "Unexpected error: " << error.what() << "\n";
        }
    }
}

// Add Employee

void EmployeeManagementSystem::addEmployee() {
    string id = readLine("New employee ID: ");

    if (id.empty() || findEmployee(id) != NULL) {
        throw AppException("ID is empty or already exists.");
    }

    string name = readLine("Name: ");
    string password = readLine("Password: ");
    string email = readLine("Email: ");

    if (name.empty() || password.empty() || email.empty()) {
        throw AppException("Name, password and email cannot be empty.");
    }

    Employee newEmployee(id, name, password, email);
    employees.push_back(newEmployee);

    cout << "Employee added.\n";
}

// Remove Employee

void EmployeeManagementSystem::removeEmployee() {
    string id = readLine("Employee ID to remove: ");

    for (int i = 0; i < (int)employees.size(); i++) {
        if (employees[i].getId() == id) {
            employees.erase(employees.begin() + i);
            cout << "Employee removed.\n";
            return;
        }
    }

    throw AppException("Employee not found.");
}

// Show Employees

void EmployeeManagementSystem::showEmployees() const {
    if (employees.empty()) {
        cout << "No employees found.\n";
        return;
    }

    cout << "\n--- EMPLOYEE LIST ---\n";

    for (int i = 0; i < (int)employees.size(); i++) {
        cout << employees[i] << "\n";
    }
}

// Assign Task

void EmployeeManagementSystem::assignTask() {
    string id = readLine("Employee ID: ");
    string title = readLine("Task title: ");
    string description = readLine("Task description: ");
    int dueDay = readInt("Due day number (e.g. 10): ");

    Employee* employee = findEmployee(id);

    if (employee == NULL) {
        throw AppException("Employee not found.");
    }

    Task newTask(title, description, dueDay);
    employee->addTask(newTask);

    cout << "Task assigned. Tasks are kept in memory for this run.\n";
}

// Penalty Thread Function

void EmployeeManagementSystem::processPenalty(
    string id, string employeeName, int days, double rate) {

    try {
        Penalty penalty("Late task", rate, days);
        double amount = penalty.calculateAmount();

        lock_guard<mutex> lock(dataMutex);

        Employee* employee = findEmployee(id);

        if (employee == NULL) {
            cout << "[Penalty Thread] Employee no longer exists.\n";
            return;
        }

        employee->setPendingPenalty(amount);

        cout << "[Penalty Thread] Penalty of Rs. "
             << amount << " recorded for "
             << employeeName << ".\n";
    }
    catch (const AppException& error) {
        cout << "[Penalty Thread] Error: " << error.what() << "\n";
    }
}

// Payroll Generation

void EmployeeManagementSystem::generatePayroll() {
    string id = readLine("Employee ID: ");

    Employee* employee = findEmployee(id);

    if (employee == NULL) {
        throw AppException("Employee not found.");
    }

    string employeeName = employee->getName();
    bool lateTask = employee->hasLateTask(currentDay);
    double penaltyAmount = employee->getPendingPenalty();

    double basic = readDouble("Basic salary (Rs.): ");
    double bonus = readDouble("Bonus (Rs.): ");
    double deductions = readDouble("Deductions (Rs.): ");

    if (lateTask && penaltyAmount == 0) {
        cout << "Employee has a late incomplete task.\n";

        double rate = readDouble("Penalty per day (Rs.; enter 0 for none): ");
        int days = readInt("Delay days: ");

        Penalty penalty("Late task", rate, days);
        penaltyAmount = penalty.calculateAmount();
    }

    // Basic threading: payroll is processed by a separate thread.
    thread payrollThread(
        &EmployeeManagementSystem::processPayroll,
        this, id, employeeName, basic, bonus, deductions, penaltyAmount
    );

    payrollThread.join();

    cout << "Payroll generation completed.\n";
}

// Payroll Thread Function

void EmployeeManagementSystem::processPayroll(
    string id, string employeeName, double basic,
    double bonus, double deductions, double penaltyAmount) {

    try {
        lock_guard<mutex> lock(dataMutex);

        Employee* employee = findEmployee(id);

        if (employee == NULL) {
            cout << "Payroll cancelled: employee no longer exists.\n";
            return;
        }

        Payroll payroll(basic);
        payroll.setDeductions(deductions);

        if (penaltyAmount > 0) {
            // Amount is stored as a one-day penalty to preserve the total.
            payroll.addPenalty(Penalty("Late task", penaltyAmount, 1));
        }

        string slipId = "SLIP" + to_string(nextSlipNumber++);

        SalarySlip slip = payroll.generateSalarySlip(
            slipId, id, employeeName, bonus
        );

        employee->setSalarySlip(slip);
        employee->clearPendingPenalty();

        cout << "\n[Payroll Thread] Payroll generated successfully.\n";
        slip.display();
    }
    catch (const AppException& error) {
        cout << "[Payroll Thread] Error: " << error.what() << "\n";
    }
}

// Report Menu
// SOLID: Dependency Inversion through report abstraction

void EmployeeManagementSystem::reportMenu() {
    cout << "\nReport type: 1. Payroll  2. Tax\n";
    int type = readInt("Choice: ");

    cout << "Report detail: 1. Summary  2. Detailed\n";
    int detail = readInt("Choice: ");

    PayrollReport payrollReport;
    TaxReport taxReport;

    const IReportGenerator* report = NULL;

    if (type == 1) {
        report = &payrollReport;
    }
    else if (type == 2) {
        report = &taxReport;
    }
    else {
        throw AppException("Unknown report type.");
    }

    if (detail == 1) {
        report->generateSummary(employees);
    }
    else if (detail == 2) {
        report->generateDetailed(employees);
    }
    else {
        throw AppException("Unknown report detail option.");
    }
}

// Main Function

int main() {
    try {
        EmployeeManagementSystem system;
        system.run();
    }
    catch (const AppException& error) {
        cout << "Fatal error: " << error.what() << "\n";
        return 1;
    }
    catch (const exception& error) {
        cout << "Unexpected fatal error: " << error.what() << "\n";
        return 1;
    }

    return 0;
}
