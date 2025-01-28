#pragma once
#include <iostream>

class SanityCheck {
private:
    static int CurrentDepth;
    static const int MaxDepth = 500;

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

int SanityCheck::CurrentDepth = 0;