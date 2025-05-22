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

### Prerequisites
*   A C++ compiler that supports C++11 (e.g., g++).
*   GNU Make (optional, but useful for managing compilation).

### Manual Compilation and Execution

**Calculator Application:**
1.  **Compile:** Open your terminal in the project root directory and run:
    ```bash
    g++ -std=c++11 main.cpp Calc.cpp -o calculator -lm
    ```
    *   `-std=c++11`: Specifies the C++ standard.
    *   `main.cpp Calc.cpp`: The source files.
    *   `-o calculator`: Names the output executable `calculator`.
    *   `-lm`: Links the math library (necessary for functions like `sqrt`, `sin`, etc.).
2.  **Run:** Execute the compiled application:
    ```bash
    ./calculator
    ```

**Unit Tests:**
1.  **Compile:** To compile the unit tests, include `test_calc.cpp`:
    ```bash
    g++ -std=c++11 main.cpp Calc.cpp test_calc.cpp -o test_runner -lm
    ```
    *   (Note: Including `main.cpp` here is unusual for a test runner if `test_calc.cpp` has its own `main`. The provided `test_calc.cpp` does have its own `main`. So, `main.cpp` should be excluded from the test compilation.)
    Corrected test compilation command:
    ```bash
    g++ -std=c++11 Calc.cpp test_calc.cpp -o test_runner -lm
    ```
2.  **Run Tests:** Execute the test runner:
    ```bash
    ./test_runner
    ```
    You should see output indicating the status of each test and a final summary.

### Running with Docker

If you have Docker installed, you can build and run the calculator application in a container:

1.  **Build the Docker Image:** Open your terminal in the project root directory (where the `Dockerfile` is located) and run:
    ```bash
    docker build -t cpp-calculator .
    ```
    *   `docker build`: Command to build an image from a Dockerfile.
    *   `-t cpp-calculator`: Tags the image with the name `cpp-calculator`.
    *   `.`: Specifies that the Dockerfile is in the current directory.

2.  **Run the Docker Container:** After the image is built successfully, run:
    ```bash
    docker run -it cpp-calculator
    ```
    *   `docker run`: Command to run a container from an image.
    *   `-it`: Runs the container in interactive mode and allocates a pseudo-TTY, allowing you to interact with the calculator.
    *   `cpp-calculator`: The name of the image to run.

## Future Enhancements

*   **Advanced Expression Parsing**: The current expression processing in `Calc::process` handles single operations or function calls at a time. A significant improvement would be to implement a more sophisticated parsing technique, such as the Shunting-yard algorithm or a recursive descent parser. This would allow the calculator to handle:
    *   Complex expressions with multiple operators and operator precedence (e.g., `2 + 3 * 4` correctly evaluated as 14).
    *   Nested parentheses in expressions (e.g., `10 * (2 + sin(0.5))`).
    *   Unary minus operators in more contexts.
*   **Variable Support**: Allow users to define and use variables.
*   **More Built-in Functions**: Add other useful mathematical or scientific functions.
```
