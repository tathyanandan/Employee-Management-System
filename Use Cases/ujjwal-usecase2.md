UseCase-2: Update Task Progress

Primary Actor: Employee

Stakeholders:

- Employee — wants to record and submit task progress.
- Administrator — wants to monitor employee task completion.
- Organization — wants accurate task and performance records.

Preconditions:

1. Employee must be registered.
2. Employee must be logged in.
3. Employee must have at least one assigned task.
4. The selected task must not already be completed.

Trigger:
Employee selects “Update Task Progress” and chooses an assigned task.

Main Flow:

1. Employee opens the task management section.
2. System displays the employee's assigned tasks.
3. Employee selects a task.
4. Employee enters or updates the current progress.
5. Employee submits the progress update.
6. System validates the submitted information.
7. System records the updated task progress.
8. System checks the task's due date.
9. If the task is submitted on time, the system confirms the update.
10. System makes the updated progress available to the Administrator.

Alternate Flows:

- A1: Task already completed
  
  1. Employee selects a completed task.
  2. System prevents further progress modification.
  3. System displays a message indicating that the task is already completed.

- A2: Task submitted after the due date
  
  1. System detects that the current submission is late.
  2. The Apply Late Penalty use case is triggered.
  3. System calculates and records the applicable penalty.
  4. System saves the updated task progress.

- A3: Invalid progress value
  
  1. Employee enters an invalid progress value.
  2. System rejects the update.
  3. System displays the required valid range/format.
  4. Employee corrects and resubmits the progress.

- A4: System error
  
  1. System fails while saving the update.
  2. System displays an error message.
  3. The previous task information remains unchanged.
  4. Employee can retry the operation.

Postconditions:

- Task progress is successfully updated and stored.
- Administrator can view the updated progress.
- If the submission is late, the applicable penalty is recorded.
- If the operation fails, no incomplete update is stored.
