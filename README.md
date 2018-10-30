		# Robot-Planning, university project

	The program controls the behavior of some robots. In a warehouse there are robots responsible for moving the boxes. Robots receive orders to collect/deliver the boxes.

	The commands are :
		1. ADD_GET_BOX/ADD_DROP_BOX RobotId x y NrBoxexs priority
			- adds to the robot's queue (CommandType, x, y, NrBoxes) according to priority. CommandType can be "GET" or "DROP".
		2. EXECUTE RobotId 
			- execute the first command from the RobotId queue. If the command is "GET" type, then the robot collect the boxes, else , if the command is "DROP" type, then the robot adds boxes in the cell.
		3. PRINT_COMMANDS RobotId
			- display the robot commands.
		4. LAST_EXECUTED_COMMAND
			- display the last executed command.
		5. UNDO
			- cancels the last "EXECUTE" or "ADD" command
		6. HOW_MUCH_TIME
			- diplay how much time the last executed command stayed in the robot queue until executed it.
		7. HOW_MANY_BOXES RobotId
			- display how many boxes has the robot in that moment.

	Program testing is done automaticaly by running the check.sh script. The check.sh script compares the result of each test 
	with the corresponding reference file from "ref" folder. For each test, the commands are read from corresponding input file from "input" folder.
