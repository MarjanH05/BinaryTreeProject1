#include "BinaryTreeUtils.h"
#include <regex>

int BinaryTreeUtils::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

std::vector<std::string> BinaryTreeUtils::tokenize(const std::string& expression) {
    std::regex token_regex("(-?\\d*\\.\\d+|-?\\d+|[-+*/^()])"); //possible negative , followed by the tokens
    std::vector<std::string> tokens;
    auto begin = std::sregex_iterator(expression.begin(), expression.end(), token_regex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        tokens.push_back(it->str());
    }

    return tokens;
}

void BinaryTreeUtils::processOperator(std::stack<std::shared_ptr<TreeNode>>& values, std::stack<std::shared_ptr<TreeNode>>& operators) {
    auto op = operators.top();
    operators.pop();

    auto right = values.top();
    values.pop();
    auto left = values.top();
    values.pop();

    op->left = left;
    op->right = right;

    values.push(op);
}

bool BinaryTreeUtils::isNegativeNumber(const std::vector<std::string>& tokens, size_t index) {
    return tokens[index] == "-" &&
        (index == 0 || tokens[index - 1] == "(" ||
            tokens[index - 1] == "+" || tokens[index - 1] == "-" ||
            tokens[index - 1] == "*" || tokens[index - 1] == "/" ||
            tokens[index - 1] == "^");
}