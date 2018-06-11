[Part B]
- Took approximately 9 hours to complete this task
- Evacuating a rack involves searching through the physical server of each instance and checking if
  the physical server belongs to the specified rack. If so, using can_host and comparing racks, the
  code will transfer virtual machines accordingly
- If anything were to fail, including not enough resources to transfer all virtual machines, changes
  will not be committed and will result in a failure log. 
- Similarly for removing a machine, if the machine is hosting virtual machines, the action will fail
  Otherwise, the machine will be removed and won't be seen from any output. 
- Adding a physical server when a server with the same name already exists will fail

[How to run]
- Program accepts arguments using the command line. 
- Ex. python script.py aggiestack config --hardware hdwr-config.txt

[Note]
- Python Version = 3.6.2

[GitHub Commit]
[Nov 24, 2017, 10:39 PM CST]
- https://github.tamu.edu/rawrbyte/489-17-c/tree/fe877c399b687f8c2b27f197d5fe3a7574032f1c/P4/B