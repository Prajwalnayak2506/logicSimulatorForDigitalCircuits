# Digital Logic Circuit Simulator in C++

A robust, command-line digital logic simulator developed in C++ for parsing and simulating combinational circuits from `.bench` file formats. This tool provides a complete workflow from circuit parsing and graph levelization to test vector simulation and output generation, serving as a foundational tool for digital circuit analysis.

---

## 📖 Table of Contents

- [ About The Project](#-about-the-project)
  - [ Features](#-features)
- [ Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation & Compilation](#installation--compilation)
- [ Usage](#-usage)
  - [Testbench Format](#testbench-format)
  - [Example Walkthrough](#example-walkthrough)
- [ File Structure](#-file-structure)
- [ Implementation Details](#️-implementation-details)
  - [Circuit Parsing](#circuit-parsing)
  - [Graph Levelization](#graph-levelization)
  - [Simulation Logic](#simulation-logic)
- [ Future Enhancements](#-future-enhancements)
- [ Contributing](#-contributing)
- [ Contact](#-contact)

---

## About The Project

This project was an assignment by Prof. Virendra Singh, IITB, for the course EE677 : VLSI CAD. The aim of the project is to make a simulator for a given vhdl file, which gives an output file for a given set of testcases.
###  Features
* **Conversion of `.vhdl` to `.bench`**: Accurately converts vhdl file to bench format having `INPUT`, `OUTPUT`, and gate definitions.
* **Comprehensive `.bench` File Parsing**: Accurately reads circuit netlists, including `INPUT`, `OUTPUT`, and gate definitions.
* **Multiple Gate Support**: Natively supports a wide range of standard logic gates:
    * `AND`
    * `OR`
    * `NAND`
    * `NOR`
    * `XOR`
    * `XNOR`
    * `NOT` (Inverter)
* **Circuit Levelization**: Implements a Breadth-First Search (BFS) based algorithm to levelize the circuit, ensuring that gates are evaluated in the correct topological order.
* **Test Vector Simulation**: Reads a `testbench.txt` file containing binary input vectors and simulates the circuit's response for each vector.
* **File-based I/O**: Generates a clear, readable `sim_output.txt` file with the corresponding outputs for each input vector.

---

## 🚀 Getting Started

Follow these instructions to get a local copy of the project up and running.

### Prerequisites

This project requires a C++ compiler supporting the C++17 standard. The `g++` compiler is recommended.

* **To install g++ on Debian/Ubuntu:**
    ```sh
    sudo apt-get update
    sudo apt-get install g++
    ```
* **To install developer tools on macOS (includes Clang, compatible with g++):**
    ```sh
    xcode-select --install
    ```
* **For Windows:** You can use MinGW-w64 (through MSYS2) or Windows Subsystem for Linux (WSL).

### Installation & Compilation

1.  **Clone the repository:**
    ```sh
    git clone [https://github.com/Prajwalnayak2506/logicSimulatorForDigitalCircuits.git](https://github.com/Prajwalnayak2506/logicSimulatorForDigitalCircuits.git)
    cd logicSimulatorForDigitalCircuits
    ```

2.  **Compile the source code:**
    Use the following command in the project's root directory. This will compile all `.cpp` files and create an executable named `Bencher`.
    ```sh
    g++ -std=c++17 *.cpp -o Bencher
    ```

---

## Usage

After successful compilation, run the executable from the terminal.

```sh
./Bencher
```

The program will automatically:
1.  Read the circuit definition from the `.vhdl` file in the directory.
2.  Create a corresponding `.bench` file in the direction.
3.  Read the input vectors from `testbench.txt`.
4.  Execute the simulation.
5.  Write the results to `sim_output.txt`.

### Testbench Format

The `testbench.txt` file should contain one binary input vector per line. The length of each line must match the number adn orderof `INPUT` nodes defined in the `.vhdl` file. The order of bits corresponds to the sorted order of input node IDs.

For a circuit with 3 inputs (`INPUT(1)`, `INPUT(2)`, `INPUT(3)`), the testbench file would look like this:
```
000
001
010
...
111
```

### Example Walkthrough
1.  **VHDL file (`testCode1.vhdl`):**
```
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity LogicCircuit is
    Port ( 
        input_1  : in  STD_LOGIC;
        input_2  : in  STD_LOGIC;
        output_4 : out STD_LOGIC 
    );
end LogicCircuit;
architecture Behavioral of LogicCircuit is
    signal signal_3 : STD_LOGIC;
begin
    signal_3 <= not input_1;
    output_4 <= input_2 and signal_3;
end Behavioral;
   ```
2.  **Bench file (`testCode1.bench`):**
    ```
    INPUT(1)
    INPUT(2)
    OUTPUT(3)
    4 = NOT(1)
    3 = AND(2, 2)
    ```

3.  **Testbench (`testbench.txt`):**
    The inputs correspond to nodes `1` and `2` respectively.
    ```
    00
    01
    10
    11
    ```

4.  **Run the simulator:**
    ```sh
    ./Bencher
    ```

5.  **Output (`sim_output.txt`):**
    The output corresponds to node `3`.
    ```
    0
    1
    0
    0
    ```

---

##  File Structure

Here is an overview of the key files and their roles in the project:

| File/Folder         | Description                                                    |
| ------------------- | -------------------------------------------------------------- |
| `Bencher.exe`       | The compiled executable file.                                  |
| `bencher.cpp`       | Converts the .vhdl to .bench file and has the main function    |
| `parser.h/.cpp`     | Handles parsing of the `.bench` files.                         |
| `nodify.h/.cpp`     | Manages the creation and properties of circuit nodes (gates).  |
| `graphiphy.h/.cpp`  | Constructs the circuit graph from the parsed nodes.            |
| `levelizer.h/.cpp`  | Implements the BFS-based levelization algorithm.               |
| `simulator.h/.cpp`  | Contains the core logic for simulating the circuit.            |
| `*.vhdl `           | Circuit netlist definition files used as input.                |
| `*.bench `          | Files generated  by the bench.exe from input vhdl files.       |
| `testbench.txt`     | Contains the input test vectors for the simulation.            |
| `sim_output.txt`    | The output file where simulation results are stored.           |

---

##  Implementation Details

The simulator operates in three main phases:

### File conversion
The `bencher` module reads the `.vhdl` file given as input and converts it into a `.bench` file. But this converter works on certain assumptions which are not necessarily true. 
1. Strict Syntax: The code requires one statement per line and cannot parse code that spans multiple lines.
2. No Behavioral VHDL: It completely ignores essential constructs like PROCESS, IF-THEN-ELSE, and CASE statements.
3. Simple Logic Only: It can't handle expressions with more than one operator (e.g., y <= a and b or c;) and doesn't understand operator precedence.
4. Naming assumption : It assumes a component's output port must be named starting with 'o' or 'O'. It will misidentify any output port named q, sum, result, etc., as an input.
5. Unsupported Features: It doesn't handle INOUT ports, assignments from constants (e.g., led <= '1'), or GENERATE statements.

### Circuit Parsing

The `parser` module reads the `.bench` file line by line. It identifies `INPUT` and `OUTPUT` declarations and gate definitions. For each line, it creates `Node` objects with attributes like gate type, fan-in, and fan-out connections. These nodes form the basis of the circuit graph.

### Graph Levelization

To ensure correct propagation of signals, the circuit must be evaluated in a specific order. This is achieved by levelization:
1.  A directed graph is constructed where gates are vertices and wires are edges.
2.  A **Breadth-First Search (BFS)** algorithm starts from the primary input nodes (which are at level 0).
3.  As the algorithm traverses the graph, it assigns an integer level to each node. A node's level is guaranteed to be greater than the level of any of its fan-in nodes.
4.  This process effectively creates a topological sort of the gates, which dictates the order of evaluation during simulation.

### Simulation Logic

For each input vector from `testbench.txt`:
1.  The values are assigned to the primary input nodes (level 0).
2.  The simulator iterates through the levels in increasing order (1, 2, 3, ...).
3.  Within each level, it evaluates the output of every gate based on the already-computed values of its fan-in nodes (from previous levels).
4.  This process continues until all nodes, including the primary outputs, have been evaluated.
5.  The final values of the primary output nodes are written to `sim_output.txt`.

---

## Future Enhancements

Potential areas for future development include:
* **Sequential Circuit Support**: Add functionality to simulate sequential elements like D-Flip-Flops and Latches, requiring state management across clock cycles.
* **Circuit Visualization**: Integrate with a tool like [Graphviz](https://graphviz.org/) to generate visual diagrams of the parsed circuit graph.
* **VHDL/Verilog Support**: Extend the parser to support more widely used Hardware Description Languages (HDLs).
* **Performance Optimization**: For very large circuits, explore performance enhancements through parallelization or more advanced simulation algorithms.

---

## Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

To contribute:
1.  Fork the Project.
2.  Create your Feature Branch (`git checkout -b feature/NewFeature`).
3.  Commit your Changes (`git commit -m 'Add some NewFeature'`).
4.  Push to the Branch (`git push origin feature/NewFeature`).
5.  Open a Pull Request.

Please ensure your code adheres to a consistent style and that you provide clear commit messages.


## Contact

Prajwal Nayak - [prajwal.nayak.ee.iitb@gmail.com](mailto:prajwal.nayak.ee.iitb@gmail.com)

Project Link: [https://github.com/Prajwalnayak2506/logicSimulatorForDigitalCircuits](https://github.com/Prajwalnayak2506/logicSimulatorForDigitalCircuits)