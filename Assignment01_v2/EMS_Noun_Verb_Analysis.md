# Noun–Verb Analysis — Employee Management System

## 1. Objective

The purpose of noun–verb analysis is to identify potential domain classes from the nouns appearing in the three use-case specifications and to use the verbs to identify actions/responsibilities associated with those classes.

The three specifications analyzed are:

1. Login (Employee)
2. Update Task Progress
3. Generate Payroll

---

# 2. Raw Candidate List

The following nouns were extracted from all three use-case specifications. At this stage, they are only candidate nouns and have not yet been filtered into classes.

| # | Raw Candidate | Source |
|---:|---|---|
| 1 | Employee | UC1, UC2, UC3 |
| 2 | Administrator | UC1, UC2 |
| 3 | Admin | UC3 |
| 4 | HR Department | UC1, UC3 |
| 5 | Organization | UC2 |
| 6 | Employee Account | UC1 |
| 7 | System | UC1, UC2, UC3 |
| 8 | Employee ID | UC1 |
| 9 | Password | UC1 |
| 10 | Credentials | UC1 |
| 11 | Personal Tasks | UC1 |
| 12 | Task | UC1, UC2, UC3 |
| 13 | Salary Information | UC1 |
| 14 | Dashboard | UC1 |
| 15 | Function | UC1 |
| 16 | Error Message | UC1, UC2 |
| 17 | User Session | UC1 |
| 18 | Authentication | UC1 |
| 19 | Service Error | UC1 |
| 20 | Task Management Section | UC2 |
| 21 | Assigned Tasks | UC2 |
| 22 | Progress | UC2 |
| 23 | Progress Update | UC2 |
| 24 | Due Date | UC2 |
| 25 | Submission | UC2 |
| 26 | Penalty | UC2, UC3 |
| 27 | Late Penalty | UC2 |
| 28 | Task Information | UC2 |
| 29 | Operation | UC2 |
| 30 | Payroll System | UC3 |
| 31 | Payroll | UC3 |
| 32 | Salary | UC1, UC3 |
| 33 | Employment Data | UC3 |
| 34 | Attendance | UC3 |
| 35 | Payroll Period | UC3 |
| 36 | Earnings | UC3 |
| 37 | Deductions | UC3 |
| 38 | Final Salary | UC3 |
| 39 | Payroll Record | UC3 |
| 40 | Report | UC3 |
| 41 | Payroll Information | UC3 |
| 42 | Employee Record | UC3 |
| 43 | Salary Calculation | UC3 |
| 44 | Transfer | UC3 |
| 45 | Pending Queue | UC3 |
| 46 | Salary Slip | UC3 |
| 47 | Information | UC1, UC2, UC3 |
| 48 | Access | UC1 |
| 49 | Error | UC2 |
| 50 | Record | UC2, UC3 |

---

# 3. Four Filters Used

The following four filters are applied to each raw candidate:

1. **Redundancy / Synonym Filter** — removes duplicate or synonymous candidates representing the same concept.
2. **Irrelevant / Out-of-Scope Filter** — removes nouns that are merely stakeholders, generic references, or otherwise not required as domain classes.
3. **Attribute / Property Filter** — removes nouns that are properties or values of another domain object.
4. **Implementation / UI / Process Filter** — removes nouns representing interface elements, technical mechanisms, operations, errors, or external implementation details rather than domain classes.

---

# 4. Candidate Filtering

| Raw Candidate | Decision | Filter | Reason |
|---|---|---|---|
| Employee | **Survives** | — | Core domain entity involved in all three use cases. |
| Administrator | **Eliminated** | Redundancy / Synonym | Same role/concept as Admin. |
| Admin | **Survives** | — | Domain actor responsible for payroll generation. |
| HR Department | **Eliminated** | Irrelevant / Out-of-Scope | Stakeholder in the specifications; no direct responsibility modeled in the three use cases. |
| Organization | **Eliminated** | Irrelevant / Out-of-Scope | Stakeholder rather than a domain entity manipulated by these use cases. |
| Employee Account | **Survives** | — | Represents registration, credentials, and active/inactive account status. |
| System | **Eliminated** | Implementation / UI / Process | Generic reference to the software system, not a domain entity. |
| Employee ID | **Eliminated** | Attribute / Property | Identifier belonging to an Employee. |
| Password | **Eliminated** | Attribute / Property | Credential stored as part of an Account. |
| Credentials | **Eliminated** | Attribute / Property | Authentication data represented by Account attributes. |
| Personal Tasks | **Eliminated** | Redundancy / Synonym | Same domain concept as Task. |
| Task | **Survives** | — | Core domain entity whose progress and due date are managed. |
| Salary Information | **Eliminated** | Attribute / Property | Salary-related data belongs to Employee/PayrollRecord/SalarySlip. |
| Dashboard | **Eliminated** | Implementation / UI / Process | User-interface element. |
| Function | **Eliminated** | Irrelevant / Out-of-Scope | Generic reference to system functionality rather than a domain entity. |
| Error Message | **Eliminated** | Implementation / UI / Process | UI/output detail. |
| User Session | **Eliminated** | Implementation / UI / Process | Technical authentication/session mechanism. |
| Authentication | **Eliminated** | Implementation / UI / Process | Behavior/process rather than a domain entity. |
| Service Error | **Eliminated** | Implementation / UI / Process | Technical error condition. |
| Task Management Section | **Eliminated** | Implementation / UI / Process | UI section. |
| Assigned Tasks | **Eliminated** | Redundancy / Synonym | Represents the collection of Task objects assigned to an Employee. |
| Progress | **Eliminated** | Attribute / Property | Property/state of a Task. |
| Progress Update | **Eliminated** | Implementation / UI / Process | Action/update operation rather than a required domain class. |
| Due Date | **Eliminated** | Attribute / Property | Property of a Task. |
| Submission | **Eliminated** | Implementation / UI / Process | Action/event in the update workflow; not required as an independent class for these specifications. |
| Penalty | **Survives** | — | Domain entity because penalties are calculated, recorded, and used in payroll. |
| Late Penalty | **Eliminated** | Redundancy / Synonym | A specific type of Penalty; no separate class is required. |
| Task Information | **Eliminated** | Attribute / Property | Data belonging to Task. |
| Operation | **Eliminated** | Implementation / UI / Process | Generic action/process rather than a domain entity. |
| Payroll System | **Eliminated** | Implementation / UI / Process | External system involved in transferring payroll information. |
| Payroll | **Eliminated** | Redundancy / Synonym | The persistent/generated payroll information is represented by PayrollRecord. |
| Salary | **Eliminated** | Attribute / Property | Salary is a value associated with Employee and/or PayrollRecord. |
| Employment Data | **Eliminated** | Attribute / Property | Data belonging to Employee. |
| Attendance | **Survives** | — | Domain information retrieved and used in payroll calculation. |
| Payroll Period | **Survives** | — | Defines the period for which payroll is generated and validated. |
| Earnings | **Eliminated** | Attribute / Property | Calculated value stored in PayrollRecord. |
| Deductions | **Eliminated** | Attribute / Property | Calculated payroll value stored in PayrollRecord. |
| Final Salary | **Eliminated** | Attribute / Property | Calculated value stored in PayrollRecord/SalarySlip. |
| Payroll Record | **Survives** | — | Domain entity that stores generated payroll calculations. |
| Report | **Eliminated** | Irrelevant / Out-of-Scope | Output artifact of payroll generation rather than a core domain entity. |
| Payroll Information | **Eliminated** | Attribute / Property | Information represented by PayrollRecord. |
| Employee Record | **Eliminated** | Redundancy / Synonym | Same underlying domain entity as Employee. |
| Salary Calculation | **Eliminated** | Implementation / UI / Process | Calculation operation/process, not a domain entity. |
| Transfer | **Eliminated** | Implementation / UI / Process | Operation performed when sending payroll to the external system. |
| Pending Queue | **Eliminated** | Implementation / UI / Process | Technical mechanism for handling failed transfers. |
| Salary Slip | **Survives** | — | Domain artifact generated from payroll and subsequently accessed by employees. |
| Information | **Eliminated** | Irrelevant / Out-of-Scope | Generic term with no independent domain meaning. |
| Access | **Eliminated** | Implementation / UI / Process | Represents an action/permission rather than an independent domain entity. |
| Error | **Eliminated** | Implementation / UI / Process | Error condition rather than a domain entity. |
| Record | **Eliminated** | Irrelevant / Out-of-Scope | Generic term; specific domain records are represented by Employee, Attendance, and PayrollRecord. |

---

# 5. Surviving Classes

After applying the four filters, the following candidates survive as domain classes:

| # | Surviving Class | Main reason for survival |
|---:|---|---|
| 1 | **Employee** | Central domain entity across login, task progress, and payroll. |
| 2 | **Admin** | Performs the Generate Payroll use case. |
| 3 | **EmployeeAccount** | Maintains credentials and active/inactive account status. |
| 4 | **Task** | Represents assigned work and its progress/due date. |
| 5 | **Penalty** | Represents calculated and recorded penalties used in payroll. |
| 6 | **Attendance** | Provides attendance information used in payroll calculation. |
| 7 | **PayrollPeriod** | Defines and validates the payroll period. |
| 8 | **PayrollRecord** | Stores calculated payroll information and final salary. |
| 9 | **SalarySlip** | Represents the generated salary information accessible to employees. |

## Final Class Set

```text
Employee
Admin
EmployeeAccount
Task
Penalty
Attendance
PayrollPeriod
PayrollRecord
SalarySlip
```

---

# 6. Role of Verbs in the Analysis

The verbs extracted from the specifications help identify responsibilities/operations for the surviving classes.

| Use Case | Important Verbs | Potential Class Responsibilities |
|---|---|---|
| Login | enter, validate, verify, grant, deny | EmployeeAccount validates credentials and account status |
| Update Task Progress | select, update, validate, record, check, calculate | Task updates progress and checks completion/due date; Penalty calculates applicable penalty |
| Generate Payroll | retrieve, validate, calculate, generate, store, send | PayrollRecord calculates/stores payroll; PayrollPeriod validates period |

Therefore, the noun analysis identifies the **candidate classes**, while the verbs help determine the **responsibilities and operations** that will be used later in the CRC cards and domain class diagram.

---

# 7. Result

The noun–verb analysis reduces the nouns extracted from the three use cases to the following domain model candidates:

```text
Employee
Admin
EmployeeAccount
Task
Penalty
Attendance
PayrollPeriod
PayrollRecord
SalarySlip
```

These surviving classes will be used as the basis for the next stages of the assignment: **CRC cards, the domain class diagram, and the object diagram.**
