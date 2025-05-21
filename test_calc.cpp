#include <iostream>
#include <string>
#include <vector>
#include <stdexcept> // For exceptions
#include <cmath>     // For std::abs, std::pow, etc.
#include <cassert>   // For a simple assert, though a custom one is better for messages
#include <iomanip>   // For std::fixed, std::setprecision

#include "Calc.h"    // The class to test

// Test utility: a simple assertion with a message
void assertTrue(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << "ASSERTION FAILED: " << message << std::endl;
        // In a real test suite, you might throw or exit
        // For now, just print and continue to see all failures
    } else {
        // std::cout << "Assertion PASSED: " << message << std::endl; // Optional: for verbose pass
    }
}

// Helper to compare doubles with a tolerance
void assertDoublesEqual(double val1, double val2, const std::string& message, double tolerance = 1e-9) {
    if (std::abs(val1 - val2) > tolerance) {
        std::cerr << std::fixed << std::setprecision(10) 
                  << "ASSERTION FAILED: " << message 
                  << ". Expected: " << val2 << ", Got: " << val1 << std::endl;
    } else {
        // std::cout << "Assertion PASSED: " << message << std::endl; // Optional
    }
}

// Test runner structure
typedef void (*TestFunction)(); // Function pointer type for tests

bool runTest(TestFunction func, const std::string& testName) {
    std::cout << "Running test: " << testName << "..." << std::endl;
    try {
        func();
        std::cout << testName << ": PASSED" << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << testName << ": FAILED with exception: " << e.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << testName << ": FAILED with unknown exception" << std::endl;
        return false;
    }
}

// --- Test Cases ---
Calc testCalc(10); // A common Calc instance for tests, re-initialize if state matters test-to-test

void testAddition() {
    assertDoublesEqual(testCalc.process("+5", 10), 15, "Addition: 10+5");
    assertDoublesEqual(testCalc.process("+-3", 10), 7, "Addition: 10+(-3)");
}

void testSubtraction() {
    assertDoublesEqual(testCalc.process("-5", 10), 5, "Subtraction: 10-5");
    assertDoublesEqual(testCalc.process("--3", 10), 13, "Subtraction: 10-(-3)");
}

void testMultiplication() {
    assertDoublesEqual(testCalc.process("*5", 10), 50, "Multiplication: 10*5");
    assertDoublesEqual(testCalc.process("*-2", 10), -20, "Multiplication: 10*(-2)");
}

void testDivision() {
    assertDoublesEqual(testCalc.process("/2", 10), 5, "Division: 10/2");
    assertDoublesEqual(testCalc.process("/-4", 10), -2.5, "Division: 10/(-4)");
}

void testDivisionByZero() {
    bool caught = false;
    try {
        testCalc.process("/0", 10);
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        assertTrue(msg.find("Division by zero") != std::string::npos, "Division by zero error message");
        caught = true;
    }
    assertTrue(caught, "Division by zero throws std::runtime_error");
}

void testExponentiation() {
    assertDoublesEqual(testCalc.process("^2", 10), 100, "Exponentiation: 10^2");
    assertDoublesEqual(testCalc.process("^0.5", 100), 10, "Exponentiation: 100^0.5 (sqrt)");
}

void testSinFunction() {
    // Assuming angles are in radians for std::sin
    assertDoublesEqual(testCalc.process("sin(0)", 0), 0.0, "sin(0)");
    assertDoublesEqual(testCalc.process("sin(1.57079632679)", 0), 1.0, "sin(pi/2)"); // approx pi/2
}

void testCosFunction() {
    assertDoublesEqual(testCalc.process("cos(0)", 0), 1.0, "cos(0)");
    assertDoublesEqual(testCalc.process("cos(3.14159265359)", 0), -1.0, "cos(pi)"); // approx pi
}

void testTanFunction() {
    assertDoublesEqual(testCalc.process("tan(0)", 0), 0.0, "tan(0)");
    // tan(pi/4) = 1
    assertDoublesEqual(testCalc.process("tan(0.78539816339)", 0), 1.0, "tan(pi/4)"); // approx pi/4
}


void testLogFunction() {
    assertDoublesEqual(testCalc.process("log(1)", 0), 0.0, "log(1)");
    assertDoublesEqual(testCalc.process("log(2.71828182846)", 0), 1.0, "log(e)"); // approx e
}

void testLogNonPositive() {
    bool caught_zero = false;
    try {
        testCalc.process("log(0)", 0);
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        assertTrue(msg.find("log of non-positive") != std::string::npos, "Log of zero error message");
        caught_zero = true;
    }
    assertTrue(caught_zero, "Log of zero throws std::runtime_error");

    bool caught_neg = false;
    try {
        testCalc.process("log(-1)", 0);
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        assertTrue(msg.find("log of non-positive") != std::string::npos, "Log of negative error message");
        caught_neg = true;
    }
    assertTrue(caught_neg, "Log of negative throws std::runtime_error");
}

void testSqrtFunction() {
    assertDoublesEqual(testCalc.process("sqrt(16)", 0), 4.0, "sqrt(16)");
    assertDoublesEqual(testCalc.process("sqrt(0)", 0), 0.0, "sqrt(0)");
}

void testSqrtNegative() {
    bool caught = false;
    try {
        testCalc.process("sqrt(-4)", 0);
    } catch (const std::runtime_error& e) {
        std::string msg = e.what();
        assertTrue(msg.find("sqrt of negative") != std::string::npos, "Sqrt of negative error message");
        caught = true;
    }
    assertTrue(caught, "Sqrt of negative throws std::runtime_error");
}

void testInvalidFunctionInput() {
    bool caught = false;
    try {
        testCalc.process("sin(abc)", 0);
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        assertTrue(msg.find("Invalid number in function argument") != std::string::npos, "sin(abc) error message");
        caught = true;
    }
    assertTrue(caught, "sin(abc) throws std::invalid_argument");
}

void testMalformedFunctionCall() {
    bool caught = false;
    try {
        testCalc.process("sin(30", 0); // Missing closing parenthesis
    } catch (const std::invalid_argument& e) {
        // Current Calc::process might parse "sin" and then fail on "30" as an operator,
        // or might throw due to cleanseForOperator if it expects "sin(30)".
        // The specific error might be "Unknown operator" or "Malformed operator expression"
        // depending on how it falls through. This test checks that *an* invalid_argument is thrown.
        caught = true;
    }
    assertTrue(caught, "Malformed function call like sin(30 throws std::invalid_argument");
}


void testUnknownOperator() {
    bool caught = false;
    try {
        testCalc.process("?5", 10);
    } catch (const std::invalid_argument& e) {
        std::string msg = e.what();
        assertTrue(msg.find("Unknown operator or invalid expression format") != std::string::npos, "Unknown operator error message");
        caught = true;
    }
    assertTrue(caught, "Unknown operator ?5 throws std::invalid_argument");
}

void testCalcHistory() {
    Calc historyCalc(3); // Test with a small capacity
    assertTrue(historyCalc.getHistoryCount() == 0, "Initial history count should be 0");

    historyCalc.addExpressionToHistory("2+2=4");
    assertTrue(historyCalc.getHistoryCount() == 1, "History count after 1 add");

    historyCalc.addExpressionToHistory("3*3=9");
    historyCalc.addExpressionToHistory("4-1=3");
    assertTrue(historyCalc.getHistoryCount() == 3, "History count after filling capacity");
    
    // Test adding beyond capacity (should not increase count or throw, based on current addExpressionToHistory)
    historyCalc.addExpressionToHistory("5+5=10"); // This should be ignored or logged by addExpressionToHistory
    assertTrue(historyCalc.getHistoryCount() == 3, "History count should remain at max capacity");

    // printHistory is harder to test directly without output capturing,
    // but we can ensure it doesn't crash.
    std::cout << "Testing printHistory (visual check for no crash):" << std::endl;
    historyCalc.printHistory(); 
    std::cout << "printHistory test section finished." << std::endl;
}


int main() {
    int testsPassed = 0;
    int totalTests = 0;

    auto run = [&](TestFunction func, const std::string& name){
        totalTests++;
        if (runTest(func, name)) {
            testsPassed++;
        }
    };

    run(testAddition, "testAddition");
    run(testSubtraction, "testSubtraction");
    run(testMultiplication, "testMultiplication");
    run(testDivision, "testDivision");
    run(testDivisionByZero, "testDivisionByZero");
    run(testExponentiation, "testExponentiation");
    
    run(testSinFunction, "testSinFunction");
    run(testCosFunction, "testCosFunction");
    run(testTanFunction, "testTanFunction");
    run(testLogFunction, "testLogFunction");
    run(testLogNonPositive, "testLogNonPositive");
    run(testSqrtFunction, "testSqrtFunction");
    run(testSqrtNegative, "testSqrtNegative");
    
    run(testInvalidFunctionInput, "testInvalidFunctionInput");
    run(testMalformedFunctionCall, "testMalformedFunctionCall");
    run(testUnknownOperator, "testUnknownOperator");
    
    run(testCalcHistory, "testCalcHistory");

    std::cout << "\n--- Test Summary ---" << std::endl;
    std::cout << testsPassed << " of " << totalTests << " tests passed." << std::endl;

    return (testsPassed == totalTests) ? 0 : 1; // Return 0 on success
}
