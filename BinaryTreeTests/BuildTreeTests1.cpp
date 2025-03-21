#include "gtest/gtest.h"
#include "..\BinaryTree\BinaryTree.h"

class TreeTest : public ::testing::Test {
protected:
    Tree tree;

    bool areTreesEqual(const std::shared_ptr<TreeNode>& node1, const std::shared_ptr<TreeNode>& node2) {
        if (node1 == nullptr && node2 == nullptr) return true;
        if (node1 == nullptr || node2 == nullptr) return false;
        return node1->value == node2->value &&
            areTreesEqual(node1->left, node2->left) &&
            areTreesEqual(node1->right, node2->right);
    }
};

// Test case for a simple expression.
TEST_F(TreeTest, SimpleExpression) {
    std::string expression = "3+5";
    tree.buildTree(expression);
    std::shared_ptr<TreeNode> expectedRoot = std::make_shared<TreeNode>("+");

    expectedRoot->left = std::make_shared<TreeNode>("3");
    expectedRoot->right = std::make_shared<TreeNode>("5");

    EXPECT_TRUE(areTreesEqual(tree.root, expectedRoot));
}

// Test case for an expression with multiple operators.
TEST_F(TreeTest, MultipleOperators) {
    std::string expression = "3+5*2";
    tree.buildTree(expression);

    std::shared_ptr<TreeNode> expectedRoot = std::make_shared<TreeNode>("+");
    expectedRoot->left = std::make_shared<TreeNode>("3");
    expectedRoot->right = std::make_shared<TreeNode>("*");
    expectedRoot->right->left = std::make_shared<TreeNode>("5");
    expectedRoot->right->right = std::make_shared<TreeNode>("2");

    EXPECT_TRUE(areTreesEqual(tree.root, expectedRoot));
}

// Test case for parentheses handling.
TEST_F(TreeTest, ParenthesesExpression) {
    std::string expression = "(3+5)*2";
    tree.buildTree(expression);

    std::shared_ptr<TreeNode> expectedRoot = std::make_shared<TreeNode>("*");
    expectedRoot->left = std::make_shared<TreeNode>("+");
    expectedRoot->left->left = std::make_shared<TreeNode>("3");
    expectedRoot->left->right = std::make_shared<TreeNode>("5");
    expectedRoot->right = std::make_shared<TreeNode>("2");

    EXPECT_TRUE(areTreesEqual(tree.root, expectedRoot));
}

// Test case for handling negative numbers.
TEST_F(TreeTest, ComplexExpressionWithNegative) {
    std::string expression = "4-3-2-1+67"; 
    tree.buildTree(expression);

    // Build the expected tree
    std::shared_ptr<TreeNode> expectedRoot = std::make_shared<TreeNode>("+");
    expectedRoot->left = std::make_shared<TreeNode>("-");
    expectedRoot->right = std::make_shared<TreeNode>("67");

    expectedRoot->left->left = std::make_shared<TreeNode>("-");
    expectedRoot->left->right = std::make_shared<TreeNode>("1");

    expectedRoot->left->left->left = std::make_shared<TreeNode>("-");
    expectedRoot->left->left->right = std::make_shared<TreeNode>("2");

    expectedRoot->left->left->left->left = std::make_shared<TreeNode>("4");
    expectedRoot->left->left->left->right = std::make_shared<TreeNode>("3");

    EXPECT_TRUE(areTreesEqual(tree.root, expectedRoot));
}
