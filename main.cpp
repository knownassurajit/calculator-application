#include <iostream>
#include <string>
#include <limits>
#include "Calc.h" // Assumes Calc.h is updated

int main() {
    int sentinal = 0;
    do {
        std::cout << "Please enter the maximum number of expressions you would like to store: " << std::endl;
        int values; // This is max_expressions for Calc constructor
        std::cin >> values;

        if (std::cin.fail() || values < 1) {
            std::cout << "Error: Number of stored expressions must be positive and valid." << std::endl;
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            sentinal = 1; 
            std::cout << "Press 1 to try again, any other value to quit" << std::endl;
            std::cin >> sentinal;
            if (std::cin.fail()) { 
                 std::cout << "Invalid input. Exiting." << std::endl;
                 std::cin.clear();
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                 sentinal = 0; 
            }
            if (sentinal != 1) continue; 
            else continue; 
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        Calc calc1(values); // Pass 'values' as max_expressions

        // Loop for the number of expression sequences to store
        // The original loop 'for (size_t count = 0; count < values; ++count)' meant we would fill all slots.
        // The new interactive loop lets user decide when they are 'done' with a sequence.
        // We will loop until history is full or user quits.

        while(calc1.getHistoryCount() < values) {
            double answer = 0.0; // Initialize answer for the current expression sequence

            std::cout << "\n--- New Expression Sequence (Storing " 
                      << (calc1.getHistoryCount() + 1) << " of " << values 
                      << ") ---" << std::endl;

            while (true) { // Loop for current expression, allowing multiple operations
                std::string userString;
                std::cout << "Current value: " << answer << std::endl;
                std::cout << "Enter expression (e.g., +5, *2, sin(30), sqrt(16), or 'done' to finish this sequence, 'quit' to exit calculator):" << std::endl;
                
                std::getline(std::cin, userString);

                if (userString == "quit") {
                    sentinal = 0; 
                    goto end_calculator_session; 
                }
                if (userString.empty()) {
                    continue;
                }
                if (userString == "done") {
                    // Store the final answer of the sequence.
                    // The current `Calc::addExpressionToHistory` expects a string.
                    // We are storing the string representation of the final calculated answer.
                    calc1.addExpressionToHistory(std::to_string(answer)); 
                    std::cout << "Expression sequence finished. Stored result: " << answer << std::endl;
                    break; // Exit while(true) loop for this expression sequence, on to the next sequence if space
                }

                try {
                    answer = calc1.process(userString, answer);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Invalid input: " << e.what() << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Runtime error: " << e.what() << std::endl;
                } catch (const std::exception& e) { 
                    std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
                }
            }
            // If user typed 'done', and history is now full, break from outer while loop
            if (calc1.getHistoryCount() >= values) {
                 std::cout << "All " << values << " expression slots are filled." << std::endl;
                 break; 
            }
        }
    
    end_calculator_session:; 

        if (calc1.getHistoryCount() > 0) {
             calc1.printHistory(); // Use new method name
        } else {
            std::cout << "No expressions were stored." << std::endl;
        }

        if (sentinal != 0) { 
            std::cout << "Press 1 to start a new calculator session, any other value to quit" << std::endl;
            std::cin >> sentinal;
            if (std::cin.fail()) {
                 std::cout << "Invalid input. Exiting." << std::endl;
                 std::cin.clear();
                 sentinal = 0; 
            }
            // Important: consume the newline after reading sentinel for the next do-while iteration if it happens
            if (sentinal == 1) { // only if we are continuing
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            }
        }

    } while (sentinal == 1);

    std::cout << "Calculator finished." << std::endl;
    return 0;
}
