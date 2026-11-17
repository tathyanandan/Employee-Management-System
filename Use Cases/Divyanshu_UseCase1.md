Use Case-1: Login (Employee)

Primary Actor: Employee

Stakeholders:

- Employee — wants secure access to personal tasks and salary information.
- Administrator — requires only authorized employees to access the system.
- HR Department — requires secure employee account management.

Preconditions:

1. Employee must be registered in the system.
2. Employee account must be active.
3. System must be available.

Trigger:
Employee selects “Login” and enters their credentials.

Main Flow:

1. Employee enters Employee ID and password.
2. System receives the login credentials.
3. System validates the Employee ID and password.
4. System verifies that the employee account is active.
5. System grants access to the employee dashboard.
6. System displays available functions such as Update Task Progress and View Salary Slip.

Alternate Flows:

- A1: Invalid credentials
  
  1. System detects an incorrect Employee ID or password.
  2. System displays an error message.
  3. Employee is asked to enter the credentials again.

- A2: Inactive account
  
  1. System detects that the employee account is inactive.
  2. System denies access.
  3. System displays a message instructing the employee to contact HR/Admin.

- A3: System unavailable
  
  1. System cannot process the login request.
  2. System displays a temporary service error.
  3. Employee can retry later.

Postconditions:

- Employee is successfully authenticated and logged in.
- Employee dashboard becomes accessible.
- If authentication fails, no user session is created.
