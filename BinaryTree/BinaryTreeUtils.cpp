#include "BinaryTreeUtils.h"
#include <regex>

int BinaryTreeUtils::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

std::vector<std::string> BinaryTreeUtils::tokenize(const std::string& expression) {
    std::string sanitizedExpression = expression;

    sanitizedExpression.erase(std::remove_if(sanitizedExpression.begin(), sanitizedExpression.end(), ::isspace), sanitizedExpression.end());

    //must be kept updated if I add new things that are allowed i.e sin 
    std::regex invalid_chars("[^\\d+\\-*/^().]");
    if (std::regex_search(sanitizedExpression, invalid_chars)) {
        throw std::invalid_argument("Invalid characters in expression.");
    }

    std::regex token_regex("(\\d*\\.\\d+|\\d+|[-+*/^()])");
    std::vector<std::string> tokens;
    auto begin = std::sregex_iterator(expression.begin(), expression.end(), token_regex);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        tokens.push_back(it->str());
    }

    return tokens;
}

void BinaryTreeUtils::processOperator(std::stack<std::shared_ptr<TreeNode>>& values,
    std::stack<std::shared_ptr<TreeNode>>& operators) {
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

void BinaryTreeUtils::removeEqualsSign(std::string& expression) {
    expression.erase(std::remove(expression.begin(), expression.end(), '='), expression.end());
}
