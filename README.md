# Digital Logic Simulator in C++

## Overview

This project implements a **digital logic simulator** in C++ capable of simulating combinational circuits defined in `.bench` files. The simulator reads the circuit structure, levelizes the nodes for correct evaluation, processes testbench input vectors, and writes output results to a file.

---

## Features

- Parses `.bench` files for circuit definition (inputs, outputs, gates).
- Levelizes the circuit nodes to ensure proper evaluation order.
- Supports these gate types:
  - NAND, AND, OR, NOR, XOR, XNOR, NOT
- Reads testbench vectors from `testbench.txt`.
- Generates simulation output in `sim_output.txt`.
- Sorts input and output nodes by gate ID.
- Fully functional, modular, and extensible.

---

## Requirements

- **C++17** or higher
- **g++** compiler or any IDE supporting C++17

---

## File Structure
├── main.cpp # Driver code<br>
├── node.h / node.cpp # Node class definition<br>
├── graph.h / graph.cpp # Graph construction & levelization<br>
├── simulator.cpp # Simulation logic<br>
├── testbench.txt # Test vectors<br>
├── sim_output.txt # Simulation output<br>
└── README.md # Documentation & report<br>


---

## Implementation Details

### 1. Circuit Parsing

- Nodes are created for each input, output, and gate.
- Each node maintains:
  - `id`, `type`, `inputs`, `parents`, `children`, `level`, `output`
- Inputs and outputs are treated as nodes for consistent handling.

### 2. Graph Construction & Levelization

- The circuit is represented as a **directed graph**.
- Each node stores pointers to parent and child nodes.
- **Levelization** ensures that each node is evaluated **after its inputs are ready**.
- A BFS/queue-based approach is used to traverse nodes in level order.

### 3. Sorting Inputs and Outputs

- Input nodes are sorted by `id` to match the testbench order.
- Output nodes are sorted by `id` for consistent result writing.

### 4. Simulation

1. Read test vectors from `testbench.txt`.
2. Assign input values to input nodes.
3. Evaluate each node **level by level** using the gate type.
4. Write output values to `sim_output.txt`.

---

## Testbench Format

Each line represents a test vector of inputs (0 or 1):

---

## Implementation Details

### 1. Circuit Parsing

- Nodes are created for each input, output, and gate.
- Each node maintains:
  - `id`, `type`, `inputs`, `parents`, `children`, `level`, `output`
- Inputs and outputs are treated as nodes for consistent handling.

### 2. Graph Construction & Levelization

- The circuit is represented as a **directed graph**.
- Each node stores pointers to parent and child nodes.
- **Levelization** ensures that each node is evaluated **after its inputs are ready**.
- A BFS/queue-based approach is used to traverse nodes in level order.

### 3. Sorting Inputs and Outputs

- Input nodes are sorted by `id` to match the testbench order.
- Output nodes are sorted by `id` for consistent result writing.

### 4. Simulation

1. Read test vectors from `testbench.txt`.
2. Assign input values to input nodes.
3. Evaluate each node **level by level** using the gate type.
4. Write output values to `sim_output.txt`.

---

## Testbench Format

Each line represents a test vector of inputs (0 or 1):<br>
00000<br>
00100<br>
10000<br>
00001<br>
11100<br>
01010<br>
10010<br>
10101<br>
11101<br>


- Inputs correspond to input nodes sorted by ID.
- Outputs are written in order of their gate IDs.

---

## Usage

### Compile

```bash
g++ -std=c++17 parser.cpp nodify.cpp graphiphy.cpp levelizer.cpp simulator.cpp -o my_parser
```
### Run
```bash
./my_parser
```
Outputs will appear in sim_output.txt.

### Sample Input
00000<br>
00100<br>
10000<br>


The sim_output.txt might contain:<br>
01<br>
11<br>
10<br>
(Depends on the circuit defined in your .bench file.)


### Future Work

1. Add support for sequential circuits (flip-flops, latches)
2. Implement circuit visualization with Graphviz
3. Add interactive testbench generation
4. Extend gate support for multi-input gates