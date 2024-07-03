
# Project: Vacuum Cleaner Algorithm

## Contributors
- Ahmad Khalaila 207177197
- Mariam Khalaila 212346076

## Approach

The vacuum cleaner algorithm is designed to navigate and clean a house by using sensors to detect dirt levels, walls, and battery status. The algorithm employs a naive implementation where the vacuum keeps a stack of all previous steps. The vacuum returns to the docking station when the steps required to go back to the docking station are equal to the remaining battery life.

### Key Features
1. **House Representation:** The house is represented as a grid where each cell can either be an empty space, a wall, or a dirty spot.
2. **Vacuum Movement:** The vacuum moves through the grid, cleaning dirty spots and avoiding walls.
3. **Battery Management:** The vacuum returns to the docking station when the steps required to go back to the docking station are equal to the remaining battery life.

### Input Format

The input files describe the layout of the house. Each file follows this format:

- The house grid is represented by multiple lines where each cell can be:
  - ` ` for no dirt
  - `#` for walls
  - `D` for the starting position of the vacuum cleaner
  - Any number from `1` to `9` for dirt levels

Example:
```
#######
#1D0 1#
#  9  #
#1  1 #
#######
20 50
```

### Output Format

The output files contain the log of the vacuum cleaner's actions and final statistics. Each output file includes:

- A list of moves made by the vacuum cleaner.
- Total steps taken.
- Remaining dirt levels.
- The status of the vacuum cleaner (Alive/Dead).
- The mission status (Success/Failure).

Example:
```
North
East
South
Total steps: 10
Remaining dirt: 5
Vacuum cleaner status: Alive
Mission status: Success
```

### How to Build and Run

1. **Build the Project:**

   Ensure you have a suitable version of `g++` (11.4 or above). Use the provided `Makefile` to compile the project. Navigate to the directory containing your files and run:

   ```sh
   make
   ```

2. **Run the Program:**

   To run the program with an input file:

   ```sh
   ./myrobot input_a.txt
   ```

   This will produce an output file named `output_input_a.txt`.

3. **Clean the Project:**

   To clean up the compiled files:

   ```sh
   make clean
   ```

## Additional Information

- The algorithm uses random movement when multiple directions are available.
- The vacuum returns to the docking station for recharging when the battery is low.
- The house layout can include walls (`#`), dirt spots (`1-9`), and empty spaces (` `).

### Example Files

Here are examples of input and output files provided for testing different scenarios:

- **test1.txt:** grid where the Docking station is blocked with walls
  - Expected output for `input_a.txt` is failure and not cleaning anything
- **test2.txt:** A simple grid with dirt and wall configuration.
- **test.txt:** Grid without surrounding walls.
