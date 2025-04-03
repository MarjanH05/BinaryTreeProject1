#include "gtest/gtest.h"
#include "..\BinaryTree\DllLoader.h" 

class EvaluateTreeTest : public ::testing::Test {
protected:
    EvaluatorLoader loader;

    void SetUp() override {
        loader = LoadCalculationDll();
        LoaderStatus status = loader.getStatus();
        ASSERT_EQ(status, LoaderStatus::Succeeded) << "Failed to initialize DLL: "
            << (status == LoaderStatus::DllNotFound ? "DLL not found" : "Function pointers not found");
    }

    std::shared_ptr<TreeNode> CreateDeepTree(int operatorDepth) {
        if (operatorDepth < 1) {
            return nullptr;
        }

        auto root = std::make_shared<TreeNode>("+");
        root->left = std::make_shared<TreeNode>("1");
        root->right = std::make_shared<TreeNode>("1");

        for (int i = operatorDepth - 1; i >= 1; --i) {
            auto parent = std::make_shared<TreeNode>("+");
            parent->left = root;
            parent->right = std::make_shared<TreeNode>("1");
            root = parent;
        }

        return root;
    }
};

TEST_F(EvaluateTreeTest, SimpleEvaluation) {
    auto root = std::make_shared<TreeNode>("+");
    root->left = std::make_shared<TreeNode>("3");
    root->right = std::make_shared<TreeNode>("5");

    IEvaluator* evaluator = loader.create();
    double result = evaluator->Evaluate(root);
    loader.destroy(evaluator);

    EXPECT_DOUBLE_EQ(result, 8.0);
}

TEST_F(EvaluateTreeTest, MultipleOperatorsEvaluation) {
    auto root = std::make_shared<TreeNode>("+");
    root->left = std::make_shared<TreeNode>("3");
    root->right = std::make_shared<TreeNode>("*");
    root->right->left = std::make_shared<TreeNode>("5");
    root->right->right = std::make_shared<TreeNode>("2");

    IEvaluator* evaluator = loader.create();
    double result = evaluator->Evaluate(root);
    loader.destroy(evaluator);

    EXPECT_DOUBLE_EQ(result, 13.0); // 3 + (5 * 2)
}

TEST_F(EvaluateTreeTest, BracketsEvaluation) {
    auto root = std::make_shared<TreeNode>("*");
    root->left = std::make_shared<TreeNode>("+");
    root->left->left = std::make_shared<TreeNode>("3");
    root->left->right = std::make_shared<TreeNode>("5");
    root->right = std::make_shared<TreeNode>("2");

    IEvaluator* evaluator = loader.create();
    double result = evaluator->Evaluate(root);
    loader.destroy(evaluator);

    EXPECT_DOUBLE_EQ(result, 16.0); // (3 + 5) * 2
}

TEST_F(EvaluateTreeTest, NegativeNumberEvaluation) {
    auto root = std::make_shared<TreeNode>("+");
    root->left = std::make_shared<TreeNode>("-3");
    root->right = std::make_shared<TreeNode>("5");

    IEvaluator* evaluator = loader.create();
    double result = evaluator->Evaluate(root);
    loader.destroy(evaluator);

    EXPECT_DOUBLE_EQ(result, 2.0); // (-3 + 5)
}

TEST_F(EvaluateTreeTest, ExponentiationEvaluation) {
    auto root = std::make_shared<TreeNode>("^");
    root->left = std::make_shared<TreeNode>("2");
    root->right = std::make_shared<TreeNode>("3");

    IEvaluator* evaluator = loader.create();
    double result = evaluator->Evaluate(root);
    loader.destroy(evaluator);

    EXPECT_DOUBLE_EQ(result, 8.0); // 2^3
}

TEST_F(EvaluateTreeTest, DecimalEvaluation) {
    auto root = std::make_shared<TreeNode>("/");
    root->left = std::make_shared<TreeNode>("6.3");
    root->right = std::make_shared<TreeNode>("2.1");

    IEvaluator* evaluator = loader.create();
    double result = evaluator->Evaluate(root);
    loader.destroy(evaluator);

    EXPECT_DOUBLE_EQ(result, 3.0); // 6.3 / 2.1
}

TEST_F(EvaluateTreeTest, RecursionDepthExceeded) {
    auto root = CreateDeepTree(500);
    IEvaluator * evaluator = loader.create();
    EXPECT_THROW(evaluator->Evaluate(root), std::runtime_error);  // 1 + 1 + ... (500 times)
} 

TEST_F(EvaluateTreeTest, WeirdEvaluation) {
    auto root = std::make_shared<TreeNode>("+");
    root->left = std::make_shared<TreeNode>("-");
    root->right = std::make_shared<TreeNode>("67");
    root->left->left = std::make_shared<TreeNode>("-");
    root->left->right = std::make_shared<TreeNode>("1");
    root->left->left->left = std::make_shared<TreeNode>("-");
    root->left->left->right = std::make_shared<TreeNode>("2");
    root->left->left->left->left = std::make_shared<TreeNode>("4");
    root->left->left->left->right = std::make_shared<TreeNode>("3");

    IEvaluator* evaluator = loader.create();
    double result = evaluator->Evaluate(root);
    loader.destroy(evaluator);

    EXPECT_DOUBLE_EQ(result, 65.0);  // 4 - 3 - 2 - 1 + 67
}