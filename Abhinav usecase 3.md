usecase3: Generate Payroll

Primary Actor: Admin

Stakeholders:

- Admin — wants to generate accurate payroll for employees.
- HR Department — requires correct salary and payroll records.
- Employees — expect accurate salary calculations and salary slips.
- Payroll System — receives the generated payroll information for salary disbursement.

Preconditions:

1. Admin must be registered and logged in.
2. Employee salary and employment data must be available.
3. Attendance/task/penalty information must be available where applicable.
4. The payroll period must be defined.
5. Payroll System must be available for final transfer.

Trigger:
Admin selects “Generate Payroll” for a specified payroll period.

Main Flow:

1. Admin selects the payroll period.
2. System retrieves employee information.
3. System retrieves relevant salary, attendance, task, and penalty data.
4. System validates the retrieved information.
5. System calculates employee earnings.
6. System calculates applicable deductions and late penalties.
7. System calculates the final salary for each employee.
8. System generates the payroll record/report.
9. System sends the generated payroll information to the external Payroll System.
10. Payroll System receives the payroll information.
11. System confirms successful payroll generation and transfer.

Alternate Flows:

- A1: Missing employee data
  
  1. System detects missing or incomplete employee information.
  2. System identifies the affected employee record.
  3. System reports the missing information to the Admin.
  4. The affected record is excluded until the information is corrected.

- A2: Payroll System unavailable
  
  1. System generates the payroll internally.
  2. System attempts to send the payroll to the external Payroll System.
  3. The external system is unavailable.
  4. System stores the payroll in a pending queue.
  5. Admin is informed that the transfer will be retried.

- A3: Salary calculation error
  
  1. System detects an error while calculating salary.
  2. System stops processing the affected employee.
  3. System displays an error message to the Admin.
  4. The incorrect payroll record is not sent to the Payroll System.

- A4: Invalid payroll period
  
  1. Admin enters an invalid or overlapping payroll period.
  2. System rejects the request.
  3. System asks the Admin to select a valid payroll period.

Postconditions:

- Payroll is successfully generated for all valid employee records.
- Final salary calculations are stored in the system.
- Payroll information is transferred to the external Payroll System.
- Employees can subsequently access their generated salary slips.
- Failed transfers remain pending for later processing.
