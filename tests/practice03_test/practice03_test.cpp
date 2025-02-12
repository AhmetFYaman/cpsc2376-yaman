#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\hello\Desktop\programming2\Practice\practice03\practice03.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace practice03test
{
    TEST_CLASS(practice03test)
    {
    public:
        // Test cases for sumRange
        TEST_METHOD(TestSumRange_NormalCase)
        {
            // Test a normal range
            int result = MathUtils::sumRange(1, 5); // 1 + 2 + 3 + 4 + 5 = 15
            Assert::AreEqual(15, result);
        }

        TEST_METHOD(TestSumRange_SingleValue)
        {
            // Test a range with a single value
            int result = MathUtils::sumRange(3, 3); // Only 3
            Assert::AreEqual(3, result);
        }

        TEST_METHOD(TestSumRange_NegativeRange)
        {
            // Test a range with negative numbers
            int result = MathUtils::sumRange(-3, 2); // -3 + -2 + -1 + 0 + 1 + 2 = -3
            Assert::AreEqual(-3, result);
        }

        // Test cases for containsNegative
        TEST_METHOD(TestContainsNegative_NoNegatives)
        {
            // Test a vector with no negative numbers
            std::vector<int> numbers = { 1, 2, 3, 4 };
            bool result = MathUtils::containsNegative(numbers);
            Assert::IsFalse(result);
        }

        TEST_METHOD(TestContainsNegative_WithNegatives)
        {
            // Test a vector with negative numbers
            std::vector<int> numbers = { 1, -2, 3, 4 };
            bool result = MathUtils::containsNegative(numbers);
            Assert::IsTrue(result);
        }

        TEST_METHOD(TestContainsNegative_EmptyVector)
        {
            // Test an empty vector
            std::vector<int> numbers = {};
            bool result = MathUtils::containsNegative(numbers);
            Assert::IsFalse(result);
        }

        // Test cases for findMax
        TEST_METHOD(TestFindMax_NormalCase)
        {
            // Test a vector with positive numbers
            std::vector<int> numbers = { 1, 3, 2, 5, 4 };
            int result = MathUtils::findMax(numbers);
            Assert::AreEqual(5, result);
        }

        TEST_METHOD(TestFindMax_NegativeNumbers)
        {
            // Test a vector with negative numbers
            std::vector<int> numbers = { -1, -3, -2, -5, -4 };
            int result = MathUtils::findMax(numbers);
            Assert::AreEqual(-1, result); // -1 is the largest
        }

        TEST_METHOD(TestFindMax_EmptyVector)
        {
            // Test an empty vector (should throw an exception)
            std::vector<int> numbers = {};
            auto func = [&]() { MathUtils::findMax(numbers); };
            Assert::ExpectException<std::invalid_argument>(func);
        }
    };
}