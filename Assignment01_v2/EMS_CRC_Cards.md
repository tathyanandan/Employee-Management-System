# CRC Cards — Employee Management System

## 1. Objective

CRC stands for:

- **Class** — the class being analyzed.
- **Responsibilities** — what the class is responsible for knowing or doing.
- **Collaborators** — other classes that the class interacts with to fulfill its responsibilities.

The CRC cards below are based on the nine surviving classes identified during the noun–verb analysis of the three use cases:

1. Employee
2. Admin
3. EmployeeAccount
4. Task
5. Penalty
6. Attendance
7. PayrollPeriod
8. PayrollRecord
9. SalarySlip

The verbs from the three use cases were used to identify the responsibilities, while interactions between the surviving classes were used to identify collaborators.

---

# 2. CRC Cards

## CRC Card 1 — Employee

| Category | Details |
|---|---|
| **Class** | **Employee** |
| **Responsibilities** | 1. Store employee information. 2. Access employee account. 3. View assigned tasks. 4. Update task progress. 5. Access generated salary slips. |
| **Collaborators** | EmployeeAccount, Task, Attendance, PayrollRecord, SalarySlip |

---

## CRC Card 2 — Admin

| Category | Details |
|---|---|
| **Class** | **Admin** |
| **Responsibilities** | 1. Authenticate as an administrator. 2. Initiate payroll generation. 3. Review payroll information. 4. Handle payroll validation errors. |
| **Collaborators** | Employee, PayrollPeriod, PayrollRecord, Attendance, Penalty |

---

## CRC Card 3 — EmployeeAccount

| Category | Details |
|---|---|
| **Class** | **EmployeeAccount** |
| **Responsibilities** | 1. Store login credentials. 2. Maintain account active/inactive status. 3. Validate employee credentials. 4. Allow or deny access based on account status. |
| **Collaborators** | Employee, Admin |

---

## CRC Card 4 — Task

| Category | Details |
|---|---|
| **Class** | **Task** |
| **Responsibilities** | 1. Store task details. 2. Store current task progress. 3. Store task due date. 4. Update task progress. 5. Check whether the task is completed. 6. Check whether the task is overdue. |
| **Collaborators** | Employee, Penalty |

---

## CRC Card 5 — Penalty

| Category | Details |
|---|---|
| **Class** | **Penalty** |
| **Responsibilities** | 1. Store penalty information. 2. Calculate the applicable late penalty. 3. Provide penalty information for payroll calculation. |
| **Collaborators** | Task, Employee, PayrollRecord |

---

## CRC Card 6 — Attendance

| Category | Details |
|---|---|
| **Class** | **Attendance** |
| **Responsibilities** | 1. Store employee attendance information. 2. Provide attendance data for payroll calculation. |
| **Collaborators** | Employee, PayrollRecord |

---

## CRC Card 7 — PayrollPeriod

| Category | Details |
|---|---|
| **Class** | **PayrollPeriod** |
| **Responsibilities** | 1. Store payroll start date. 2. Store payroll end date. 3. Validate the payroll period. 4. Identify the period for which payroll is generated. |
| **Collaborators** | Admin, PayrollRecord |

---

## CRC Card 8 — PayrollRecord

| Category | Details |
|---|---|
| **Class** | **PayrollRecord** |
| **Responsibilities** | 1. Store payroll information. 2. Calculate employee earnings. 3. Calculate deductions. 4. Include applicable penalties. 5. Calculate final salary. 6. Store payroll status. |
| **Collaborators** | Employee, Attendance, Penalty, PayrollPeriod, SalarySlip |

---

## CRC Card 9 — SalarySlip

| Category | Details |
|---|---|
| **Class** | **SalarySlip** |
| **Responsibilities** | 1. Store generated salary information. 2. Display final salary and deductions. 3. Provide salary information to the employee. |
| **Collaborators** | Employee, PayrollRecord |

---

# 3. CRC Relationship Summary

The major collaborations identified through the CRC analysis are:

```text
Employee ─────────── EmployeeAccount
   │
   ├──────────────── Task
   │                    │
   │                    └──────── Penalty
   │
   ├──────────────── Attendance
   │
   ├──────────────── PayrollRecord
   │                    │
   │                    ├──────── PayrollPeriod
   │                    ├──────── Penalty
   │                    └──────── SalarySlip
   │
   └──────────────── SalarySlip

Admin ─────────────── PayrollPeriod
  │
  └────────────────── PayrollRecord
```

These collaborations will later form the basis for the associations and multiplicities in the domain class diagram.

---

# 4. Responsibility–Verb Mapping

The responsibilities were derived from verbs appearing in the use cases.

| Use Case | Important Verbs | Resulting Responsibilities |
|---|---|---|
| **Login** | enter, validate, verify, grant, deny | EmployeeAccount validates credentials and account status; Employee accesses the account. |
| **Update Task Progress** | select, update, validate, record, check, calculate | Employee updates Task; Task checks progress/completion/due date; Penalty handles late penalties. |
| **Generate Payroll** | retrieve, validate, calculate, generate, store, send | Admin initiates payroll; PayrollRecord performs/stores payroll calculations; PayrollPeriod validates the period. |

---

# 5. Final CRC Class Set

The completed CRC analysis gives the following classes:

| # | Class | Main Responsibility |
|---:|---|---|
| 1 | **Employee** | Manage employee-related actions and access tasks/salary information |
| 2 | **Admin** | Initiate and review payroll generation |
| 3 | **EmployeeAccount** | Authenticate and maintain account status |
| 4 | **Task** | Maintain task information and progress |
| 5 | **Penalty** | Calculate and store applicable penalties |
| 6 | **Attendance** | Maintain attendance information for payroll |
| 7 | **PayrollPeriod** | Define and validate the payroll period |
| 8 | **PayrollRecord** | Calculate and store payroll information |
| 9 | **SalarySlip** | Store and provide generated salary information |

---

# 6. Result

The CRC analysis establishes the responsibilities of each surviving class and the classes with which they collaborate.

These CRC cards provide the conceptual basis for the next step: the **domain class diagram**, where the surviving classes will be represented with attributes, operations, visibility markers, associations, and multiplicities.
