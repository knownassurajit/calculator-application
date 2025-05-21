#include <iostream>
#include "Calc.h"
#include <cmath>     // For mathematical functions
#include <string>    // For std::string, std::stod
#include <stdexcept> // For std::invalid_argument, std::runtime_error
#include <algorithm> // For std::remove_if
#include <vector>    // Often useful, though not strictly required by current string array

// Helper function to cleanse string for operators (minimal changes from original)
std::string cleanseForOperator(std::string input) {
    input.erase(std::remove_if(input.begin(), input.end(), 
        [](char c){ return c == '=' || c == ' ' || c == '(' || c == ')'; }), input.end());
    return input;
}

Calc::Calc(int max_expressions) : stored(0), max_stored_expressions(max_expressions) {
    if (max_expressions > 0) {
        storedExpressions = new std::string[max_expressions];
    } else {
        storedExpressions = nullptr;
        // Optionally, throw an error or set a default minimum capacity
        // For now, matches previous behavior of allowing 0 but not using if values < 1
    }
}

Calc::Calc(const Calc &rhs) : stored(rhs.stored), max_stored_expressions(rhs.max_stored_expressions) {
    if (max_stored_expressions > 0) {
        storedExpressions = new std::string[max_stored_expressions];
        for (size_t i = 0; i < stored; ++i) { // Copy only the stored elements
            storedExpressions[i] = rhs.storedExpressions[i];
        }
    } else {
        storedExpressions = nullptr;
    }
}

Calc::~Calc() {
	delete[] storedExpressions;
	storedExpressions = nullptr;
	stored = 0;
    max_stored_expressions = 0;
}

const Calc &Calc::operator=(const Calc &rhs) {
	if (this != &rhs) {
        delete[] storedExpressions;

        stored = rhs.stored;
        max_stored_expressions = rhs.max_stored_expressions;

        if (max_stored_expressions > 0) {
            storedExpressions = new std::string[max_stored_expressions];
            for (size_t i = 0; i < stored; ++i) { // Copy only the stored elements
                storedExpressions[i] = rhs.storedExpressions[i];
            }
        } else {
            storedExpressions = nullptr;
        }
	}
	return *this;
}

double Calc::process(std::string userInput, double prevValue) {
    std::string originalInput = userInput; 

    size_t openParen = userInput.find('(');
    size_t closeParen = userInput.find(')');

    if (openParen != std::string::npos && closeParen != std::string::npos && closeParen > openParen) {
        std::string funcName = userInput.substr(0, openParen);
        std::string argStr = userInput.substr(openParen + 1, closeParen - openParen - 1);
        double argVal;

        try {
            argVal = std::stod(argStr);
        } catch (const std::invalid_argument& ia) {
            throw std::invalid_argument("Error: Invalid number in function argument: " + argStr);
        } catch (const std::out_of_range& oor) {
            throw std::out_of_range("Error: Number in function argument out of range: " + argStr);
        }

        if (funcName == "sin") return std::sin(argVal);
        if (funcName == "cos") return std::cos(argVal);
        if (funcName == "tan") return std::tan(argVal);
        if (funcName == "log") {
            if (argVal <= 0) throw std::runtime_error("Error: log of non-positive number");
            return std::log(argVal);
        }
        if (funcName == "sqrt") {
            if (argVal < 0) throw std::runtime_error("Error: sqrt of negative number");
            return std::sqrt(argVal);
        }
    }

    std::string cleansedString = cleanseForOperator(userInput);
    if (cleansedString.empty()) {
        throw std::invalid_argument("Error: Empty or invalid expression after cleansing");
    }

    char op = cleansedString[0];
    double value;

    try {
        if (cleansedString.length() <= 1 && (op == '+' || op == '-' || op == '*' || op == '/' || op == '^')) {
             throw std::invalid_argument("Error: Operator must be followed by a number.");
        }
        if (cleansedString.length() > 1) {
            value = std::stod(cleansedString.substr(1));
        } else {
             throw std::invalid_argument("Error: Malformed operator expression.");
        }
    } catch (const std::invalid_argument& ia) { // Catching potential stod error from substr
        throw std::invalid_argument("Error: Invalid number after operator for '" + cleansedString.substr(1) + "'");
    } catch (const std::out_of_range& oor) {
        throw std::out_of_range("Error: Number after operator out of range for '" + cleansedString.substr(1) + "'");
    }
    
    switch (op) {
        case '^': return std::pow(prevValue, value);
        case '*': return prevValue * value;
        case '/':
            if (value == 0) throw std::runtime_error("Error: Division by zero");
            return prevValue / value;
        case '+': return prevValue + value;
        case '-': return prevValue - value;
        default:
            throw std::invalid_argument("Error: Unknown operator or invalid expression format: " + originalInput);
    }
}

void Calc::addExpressionToHistory(const std::string& expression) {
    if (stored < max_stored_expressions) {
        storedExpressions[stored] = expression;
        stored++;
    } else {
        // Optionally, handle history full (e.g., log a message, throw exception, or overwrite old entries)
        // For now, it simply doesn't add if full.
        std::cout << "Expression history is full. Cannot add: " << expression << std::endl;
    }
}

void Calc::printHistory() { // Renamed from print
    if (stored == 0) {
        std::cout << "No expressions stored in history." << std::endl;
        return;
    }
    std::cout << "You have " << stored << " expression(s) stored (capacity: " << max_stored_expressions << "):" << std::endl;
    for (size_t i = 0; i < stored; ++i) {
        std::cout << "Expression " << i + 1 << ": ";
        std::cout << storedExpressions[i] << std::endl;
    }
}

size_t Calc::getHistoryCount() { // Renamed from getStored
    return stored;
}

// setStored(size_t newStored) method is now removed.
