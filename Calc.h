#ifndef RHYMECALC_CALC_H
#define RHYMECALC_CALC_H

#include <string>
#include <vector> // Good to include if we consider flexible history later

class Calc {
public:
    Calc(int max_expressions); // Parameter name more descriptive
    Calc(const Calc &rhs);
    ~Calc();
    const Calc &operator=(const Calc &rhs);
    double process(std::string userInput, double prevValue);
    void printHistory(); // Renamed for clarity
    void addExpressionToHistory(const std::string& expression);
    size_t getHistoryCount(); // Renamed for clarity

    // setStored might be removed or re-evaluated later if history is dynamic.
    // For now, it's less critical than making storedExpressions private.
    // Let's keep getStored (as getHistoryCount) and remove setStored for now to enforce internal management of 'stored'.
    // void setStored(size_t newStored); // Removing for now

private:
    std::string* storedExpressions;
    size_t stored; // Number of expressions currently stored
    size_t max_stored_expressions; // Capacity
};

#endif //RHYMECALC_CALC_H
