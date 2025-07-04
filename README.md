# MiniLang

## Description
A compiler for a simple programming language that translates source code into C or RISC-V assembly.

Features:
- **Lexer**
- **Parser**
- **Code Generation** for **C** and "RISC-V Assembly"
- Supported language constructs:
    - Variables
    - Arithmetic expressions
    - Conditional statements (`if ... then ... fi`)
    - Loops (`while ... do ... done`)

---

## Requirements
- **C++17 or later**
- **CMake**
- For RISC-V assembly output and execution:
    - `riscv64-linux-gnu-gcc`, `as`, `ld`
    - **QEMU** for RISC-V program emulation

On Ubuntu:
```bash
sudo apt install build-essential cmake qemu-user binutils-riscv64-linux-gnu
```

---

## Building the Project
1) Clone the repository
```bash
git clone https://github.com/IBokai/Minilang.git 
```
2) Change directory
```bash
cd Minilang/
```

3) Run build script
```bash
./build.sh
```

---

## Usage
1) After building the project, change directory to build
```bash
cd build/
```
2) Run the compiler
```bash
./main <input_path> <output_path> <(default: RISC-V) language(C|RISC-V)>
```
## How to launch output
- C
```bash
gcc output.c -o output
```
```bash
./output
```

- RISC-V
```bash
riscv64-linux-gnu-as -march=rv64gc output.s -o output.o
```
```bash
riscv64-linux-gnu-ld temp.o -o file.exe
```
```bash
qemu-riscv64 -L /usr/riscv64-linux-gnu -cpu rv64 ./file.exe
```

---

## Code Samples
You can find various code samples in the corresponding [folder](samples/) of the project repository

---

## Future work/Possible improvements
- Function support
- Console ouput
- Optimized RISC-V code generation
- More flexible cli parer
- Add BNF grammar specification for the programming language

---

## LICENSE
[MIT LICENSE](LICENSE)
