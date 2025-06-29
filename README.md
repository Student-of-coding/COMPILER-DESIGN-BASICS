# COMPILER‑DESIGN‑BASICS

*COMPANY*: CODTECH IT SOLUTIONS

*NAME*: VAIBHAV SINGH

*INTERN ID*: CT06DK432

*DOMAIN*: C++ Programming

*DURATION*: 6 WEEKS

*MENTOR*: NEELA SANTOSH

## Description

This is a lightweight native Win32 C++ application—**Arithmetic Expression Evaluator**—that provides a simple GUI front‑end for parsing and evaluating arithmetic expressions. It uses a recursive‑descent parser to support `+`, `−`, `*`, `/`, unary operators, decimals and parentheses. Input is typed into an edit box, and the result is displayed on a static label; errors (syntax, division by zero, etc.) pop up as message boxes. Written purely with the Win32 API and statically linked, it demonstrates fundamental concepts in parsing, error‑handling, and GUI programming on Windows.

## Features

* **Recursive‑Descent Parser** supporting

  * Operator precedence (`*`/`/` over `+`/`−`)
  * Unary `+`/`−`
  * Parentheses
  * Decimal numbers
* **Error Handling** for invalid syntax, unexpected characters, division by zero
* **Result Formatting**: strips unnecessary trailing zeros
* **Win32 GUI**

  * Editable input field
  * “Evaluate” button
  * Static result label
  * Message boxes for runtime errors
* **Standalone, Static Build** (`-static -mwindows`)

## Requirements

* Windows OS (7, 8, 10 or 11)
* MinGW‑w64 or MSYS2 with a GCC toolchain supporting C++17
* No external libraries—only Win32 API

## Build Instructions

Clone this repository:

```bash
git clone https://github.com/Student-of-coding/compiler-design-basics.git
cd compiler-design-basics
```

Compile from the Command Prompt using MinGW-w64:

```bash
g++ -std=c++17 -static -mwindows -o calculator.exe simple_compiler_win32.cpp -lgdi32 -luser32 -lkernel32
```

## Usage

1. Run `calculator.exe`.
2. Type any valid arithmetic expression (e.g., `-(3.5+2)*4/2`) into the input box.
3. Click **Evaluate**.
4. View the formatted result in the label below, or an error dialog if the expression was invalid.

## Code Overview

* **`evaluateExpression()`** — entry point: initializes parser state, invokes `parseExpression()`, ensures full‑string consumption.
* **Parser Functions**

  * `parseExpression()` handles `+`/`−`
  * `parseTerm()` handles `*`/`/` (with zero‑division checks)
  * `parseFactor()` handles unary ops, parentheses, and delegates to `parseNumber()`
  * `parseNumber()` reads optional sign, integer/fraction part, uses `std::stod()`, throws on bad format
* **`formatResult()`** — prints with 10 decimals, then strips trailing zeros and lone decimal point
* **Win32 GUI (in `WinMain` + `WndProc`)**

  * Creates an EDIT, BUTTON and STATIC control
  * On button click: reads input text, calls evaluator, updates STATIC or shows a MessageBox

## Limitations & Future Work

* No support for variables, functions or other operators (exponentiation, modulo).
* No keyboard‑enter shortcut (Evaluate only on button click).
* GUI is fixed size and not DPI‑aware.
* Future: add history log, function support (`sin`, `log`), keyboard shortcuts, resizable/DPI‑aware layout.

## OUTPUT

![Image](https://github.com/user-attachments/assets/7f93d0d7-34ac-40e9-a601-d88d47620ae6)

Above, the expression +3 - -2 evaluates to 5, demonstrating handling of unary minus.

![Image](https://github.com/user-attachments/assets/fb8b7327-74e8-4f66-bfc9-54d26e355c28)

Here, (5 - 3) * 4.5 evaluates to 9, illustrating proper operator precedence, parentheses, and decimal support.

![Image](https://github.com/user-attachments/assets/865fe99e-77e3-4bcc-a604-67da8642722f)

Attempting 5/0 pops up an error dialog with the message "Division by zero", demonstrating runtime error handling.

---

📌 **Arithmetic Expression Evaluator** is perfect for anyone learning how to implement an expression parser from scratch and hook it up to a minimal Win32 GUI.
