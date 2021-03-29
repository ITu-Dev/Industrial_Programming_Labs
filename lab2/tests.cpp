#include "pch.h"
#include "CppUnitTest.h"
#include "../IP_Lab2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
    TEST_CLASS(UnitTest){
        public :

            TEST_METHOD(TEST1){
                Assert::IsTrue(Execution(0, 0, 0, 0, 0, 0) == "5");
}

TEST_METHOD(TEST2)
{
    Assert::IsTrue(Execution(1, 1, 3, 1, 4, 2) == "2 " + std::to_string(-1.0) + " " + std::to_string(5.0));
}

TEST_METHOD(TEST3)
{
    Assert::IsTrue(Execution(0, 0, 0, 2, 0, 4) == "4 " + std::to_string(2.0));
}

TEST_METHOD(TEST4)
{
    Assert::IsTrue(Execution(0, 6, 0, 0, 24, 0) == "4 " + std::to_string(4.0));
}

TEST_METHOD(TEST6)
{
    Assert::IsTrue(Execution(0, 0, 0.5, 0, 0, 5) == "3 " + std::to_string(10.0));
}

TEST_METHOD(TEST7)
{
    Assert::IsTrue(Execution(-2, 0, 0, 0, -4, 0) == "3 " + std::to_string(2.0));
}

TEST_METHOD(TEST9)
{
    Assert::IsTrue(Execution(0, 0, 0, 0, 10, 5) == "0");
}

TEST_METHOD(TEST10)
{
    Assert::IsTrue(Execution(0, 10, 0, 20, 0, 0) == "4 " + std::to_string(0.0));
}

TEST_METHOD(TEST11)
{
    Assert::IsTrue(Execution(0, 3, 0, 6, 9, 18) == "4 " + std::to_string(3.0));
}

TEST_METHOD(TEST12)
{
    Assert::IsTrue(Execution(11, 0, 12, 0, 0, 0) == "3 " + std::to_string(0.0));
}

TEST_METHOD(TEST13)
{
    Assert::IsTrue(Execution(40, 0, 0, 0, 4, 0) == "3 " + std::to_string(0.1));
}

TEST_METHOD(TEST14)
{
    Assert::IsTrue(Execution(4, 0, 8, 0, 6, 12) == "3 " + std::to_string(1.5));
}

TEST_METHOD(TEST15)
{
    Assert::IsTrue(Execution(0.5, 0, 5, 10, 0, 0) == "2 " + std::to_string(0.0) + " " + std::to_string(0.0));
}

TEST_METHOD(TEST16)
{
    Assert::IsTrue(Execution(7, 7, 14, 0, 0, 0) == "2 " + std::to_string(0.0) + " " + std::to_string(0.0));
}

TEST_METHOD(TEST17)
{
    Assert::IsTrue(Execution(0, 4, 4, 0, 0, 0) == "2 " + std::to_string(0.0) + " " + std::to_string(0.0));
}

TEST_METHOD(TEST18)
{
    Assert::IsTrue(Execution(1, 0, 0, 5, 0, 0) == "2 " + std::to_string(0.0) + " " + std::to_string(0.0));
}

TEST_METHOD(TEST19)
{
    Assert::IsTrue(Execution(5, 7, 10, 14, 12, 24) == "1 " + std::to_string(-5.0 / 7) + " " + std::to_string(12.0 / 7));
}
TEST_METHOD(TEST20)
{
    Assert::IsTrue(Execution(0.2, 0.2, 0.2, 0.5, 0, 0) == "2 " + std::to_string(0.0) + " " + std::to_string(0.0));
}
}
;
}