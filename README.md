# calculator-application

This is a calculator application I made using only C++. C++ is my most preferred programming language not because of the complex memory management but the fast execution. This calculator has been enhanced with several new features.

## Features

*   **Basic Arithmetic Operations**: Supports addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`), and exponentiation (`^`).
    *   Example: `+5`, `-10`, `*2`, `/4`, `^3` (applied to the current value).
*   **Advanced Mathematical Functions**:
    *   `sin(value)`: Calculates the sine of a value (angle in radians).
    *   `cos(value)`: Calculates the cosine of a value (angle in radians).
    *   `tan(value)`: Calculates the tangent of a value (angle in radians).
    *   `log(value)`: Calculates the natural logarithm of a value.
    *   `sqrt(value)`: Calculates the square root of a value.
    *   Example: `sin(3.14159)`, `log(10)`, `sqrt(25)`.
*   **Error Handling**: The calculator robustly handles errors such as division by zero, square root of negative numbers, logarithm of non-positive numbers, and invalid input formats. Errors are reported to the user.
*   **Expression History**: The calculator can store a user-defined number of completed expression sequences. Each sequence's final result is stored.

## How to Use

1.  **Set History Capacity**: When the program starts, it will ask you to "Please enter the maximum number of expressions you would like to store:". Enter a positive integer.
2.  **Interactive Calculation**:
    *   The calculator will then show you the `Current value:` (initially 0 for each new sequence) and prompt you to enter an expression.
    *   You can enter operations like `+5`, `*2`, or functions like `sin(0.5)`, `sqrt(16)`.
    *   The input is processed, and the `Current value:` is updated.
    *   You can continue applying operations or functions to the `Current value:`.
3.  **Completing an Expression Sequence**:
    *   When you are finished with the current calculation sequence and want to store its final result, type `done`.
    *   The result will be added to the history if there is space.
    *   A new sequence will begin (if history is not full).
4.  **Exiting**:
    *   Type `quit` at any time during expression input to terminate the calculator session.
5.  **Viewing History**:
    *   After you type `quit`, or after the expression history is filled and you complete the last sequence, the calculator will print all the stored expression results.

## Compiling and Running

(Optional: Add compilation instructions if needed, e.g., `g++ -std=c++11 main.cpp Calc.cpp -o calculator`)
