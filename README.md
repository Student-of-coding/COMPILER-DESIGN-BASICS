# COMPILER‑DESIGN‑BASICS

*COMPANY*: CODTECH IT SOLUTIONS

*NAME*: VAIBHAV SINGH

*INTERN ID*: CT06DK432

*DOMAIN*: C++ Programming

*DURATION*: 6 WEEKS

*MENTOR*: NEELA SANTOSH

## Description

This project implements a **simple compiler** that can **parse basic arithmetic expressions and evaluate them**. The deliverable is a C++ program that takes input expressions and outputs results after parsing.

This is a lightweight native Win32 C++ application—**Arithmetic Expression Evaluator**—that provides a simple GUI front‑end for entering expressions and viewing their computed results. It uses a recursive‑descent parser to support:

* Binary operators: `+`, `−`, `*`, `/` (with proper precedence)
* Unary `+` and `−`
* Parentheses for grouping
* Decimal numbers

Runtime errors (invalid syntax, unexpected characters, division by zero) are reported via MessageBox dialogs. Results are formatted to remove redundant trailing zeros.

## Features

* **Recursive‑Descent Parser** with operator precedence and parentheses
* **Error Handling**: syntax errors, unexpected tokens, division by zero
* **Result Formatting**: strips unnecessary trailing zeros
* **Win32 GUI**: EDIT control for input, BUTTON to evaluate, STATIC control for output
* **Static Build**: single `calculator.exe` with no external dependencies

## Requirements

* Windows OS (7, 8, 10 or 11)
* MinGW‑w64 or MSYS2 GCC (C++17) or Visual Studio C++ toolchain
* No external libraries—uses only the Win32 API

## Build Instructions

Clone this repository:

```bash
git clone https://github.com/Student-of-coding/compiler-design-basics.git
cd compiler-design-basics
```

Compile from the Command Prompt using MinGW-w64:

```bash
g++ -std=c++17 -static -mwindows -o Arithmetic_Expression_Evaluator.exe simple_compiler_win32.cpp -lgdi32 -luser32 -lkernel32
```

Or, in a Visual Studio x64 Native Tools prompt:

```bat
cl.exe /EHsc /std:c++17 /Fe:Arithmetic_Expression_Evaluator.exe simple_compiler_win32.cpp gdi32.lib user32.lib kernel32.lib
```

## Usage

1. Run `Arithmetic_Expression_Evaluator.exe`.
2. Enter any valid arithmetic expression (e.g., `-(3.5+2)*4/2`) into the input box.
3. Click **Evaluate**.
4. See the result displayed below, or an error dialog if the expression is invalid.

## Code Overview

* **`evaluateExpression()`** — entry point: sets up parsing state, calls `parseExpression()`, and checks for leftover characters.
* **Parser Functions**

  * `parseExpression()` handles `+`/`−`
  * `parseTerm()` handles `*`/`/` (checks for division by zero)
  * `parseFactor()` handles unary ops, parentheses, or calls `parseNumber()`
  * `parseNumber()` reads optional sign, integer and fraction parts, calls `std::stod()`, throws on bad format
* **`formatResult()`** — formats results to up to 10 decimals, then strips trailing zeros and the decimal point if unnecessary.
* **Win32 GUI** (`WinMain`, `WndProc`)

  * Creates EDIT, BUTTON, and STATIC controls
  * On button click: reads input text, invokes evaluator, updates the STATIC control or shows a MessageBox

## Limitations & Future Work

* No support for variables, functions, or additional operators (exponentiation, modulo).
* No keyboard‑enter shortcut; evaluation only via button click.
* Fixed-size, non‑DPI‑aware GUI.

  ## OUTPUT

![Image](https://github.com/user-attachments/assets/7f93d0d7-34ac-40e9-a601-d88d47620ae6)

Above, the expression +3 - -2 evaluates to 5, demonstrating handling of unary minus.

![Image](https://github.com/user-attachments/assets/fb8b7327-74e8-4f66-bfc9-54d26e355c28)

Here, (5 - 3) * 4.5 evaluates to 9, illustrating proper operator precedence, parentheses, and decimal support.

![Image](https://github.com/user-attachments/assets/865fe99e-77e3-4bcc-a604-67da8642722f)

Attempting 5/0 pops up an error dialog with the message "Division by zero", demonstrating runtime error handling.

---

📌 **Arithmetic Expression Evaluator** demonstrates the core steps of building a minimal expression‑parsing compiler with a Win32 GUI front‑end. Feel free to extend it by adding new operators, variable support, or a more advanced UI!
