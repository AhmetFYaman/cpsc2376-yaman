#include "pch.h"
#include "CppUnitTest.h"
#include "C:\Users\hello\Desktop\programming2\Practice\practice03\practice03.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace practice03test
{
    TEST_CLASS(practice03test)
    {
    public:
        // Expanded test cases for sumRange
        TEST_METHOD(TestSumRange_NormalCase)
        {
            int result = MathUtils::sumRange(1, 5); // 1 + 2 + 3 + 4 + 5 = 15
            Assert::AreEqual(15, result);
        }

        TEST_METHOD(TestSumRange_SingleValue)
        {
            int result = MathUtils::sumRange(3, 3); // Only 3
            Assert::AreEqual(3, result);
        }

        TEST_METHOD(TestSumRange_NegativeRange)
        {
            int result = MathUtils::sumRange(-3, 2); // -3 + -2 + -1 + 0 + 1 + 2 = -3
            Assert::AreEqual(-3, result);
        }

        TEST_METHOD(TestSumRange_StartGreaterThanEnd)
        {
            // Test when start > end (should return 0 or handle appropriately)
            int result = MathUtils::sumRange(5, 1);
            Assert::AreEqual(0, result); // Assuming the function returns 0 for invalid ranges
        }

        TEST_METHOD(TestSumRange_ZeroRange)
        {
            // Test a range including zero
            int result = MathUtils::sumRange(-2, 2); // -2 + -1 + 0 + 1 + 2 = 0
            Assert::AreEqual(0, result);
        }

        // Expanded test cases for containsNegative
        TEST_METHOD(TestContainsNegative_NoNegatives)
        {
            std::vector<int> numbers = { 1, 2, 3, 4 };
            bool result = MathUtils::containsNegative(numbers);
            Assert::IsFalse(result);
        }

        TEST_METHOD(TestContainsNegative_WithNegatives)
        {
            std::vector<int> numbers = { 1, -2, 3, 4 };
            bool result = MathUtils::containsNegative(numbers);
            Assert::IsTrue(result);
        }

        TEST_METHOD(TestContainsNegative_AllNegatives)
        {
            std::vector<int> numbers = { -1, -2, -3, -4 };
            bool result = MathUtils::containsNegative(numbers);
            Assert::IsTrue(result);
        }

        TEST_METHOD(TestContainsNegative_EmptyVector)
        {
            std::vector<int> numbers = {};
            bool result = MathUtils::containsNegative(numbers);
            Assert::IsFalse(result);
        }

        TEST_METHOD(TestContainsNegative_SingleNegative)
        {
            std::vector<int> numbers = { 5 };
            bool result = MathUtils::containsNegative(numbers);
            Assert::IsFalse(result);
        }

        // Expanded test cases for findMax
        TEST_METHOD(TestFindMax_NormalCase)
        {
            std::vector<int> numbers = { 1, 3, 2, 5, 4 };
            int result = MathUtils::findMax(numbers);
            Assert::AreEqual(5, result);
        }

        TEST_METHOD(TestFindMax_NegativeNumbers)
        {
            std::vector<int> numbers = { -1, -3, -2, -5, -4 };
            int result = MathUtils::findMax(numbers);
            Assert::AreEqual(-1, result); // -1 is the largest
        }

        TEST_METHOD(TestFindMax_EmptyVector)
        {
            std::vector<int> numbers = {};
            auto func = [&]() { MathUtils::findMax(numbers); };
            Assert::ExpectException<std::invalid_argument>(func);
        }

        TEST_METHOD(TestFindMax_SingleValue)
        {
            std::vector<int> numbers = { 7 };
            int result = MathUtils::findMax(numbers);
            Assert::AreEqual(7, result);
        }

        TEST_METHOD(TestFindMax_MixedNumbers)
        {
            std::vector<int> numbers = { -1, 0, 3, -5, 2 };
            int result = MathUtils::findMax(numbers);
            Assert::AreEqual(3, result);
        }

        TEST_METHOD(TestFindMax_DuplicateMax)
        {
            std::vector<int> numbers = { 1, 5, 3, 5, 2 };
            int result = MathUtils::findMax(numbers);
            Assert::AreEqual(5, result);
        }
    };
}