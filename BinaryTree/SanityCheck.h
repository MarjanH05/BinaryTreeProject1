#pragma once
#include <iostream>

class SanityCheck {
private:
    static int CurrentDepth;
    enum { MaxDepth = 500 }; 

public:
    SanityCheck() {
        CurrentDepth++;
        if (CurrentDepth > MaxDepth) {
            throw std::runtime_error("Reached recursion limit");
        }
    }

    ~SanityCheck() {
        CurrentDepth--;
    }
};
