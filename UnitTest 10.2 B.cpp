#include "pch.h"
#include "CppUnitTest.h"
#include "../Project 10.2 B/student .h"
#include "../Project 10.2 B/student .cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest102B
{
    TEST_CLASS(UnitTest102B)
    {
    public:
        TEST_METHOD(TestBinSearch)
        {
            const int N = 3;
            Student s[N] = {
                { "Petrenko", 1, CS, 4, 4, { 4 } },   // avg = 4.00
                { "Sydorenko", 2, INF, 5, 4, { 4 } }, // avg = 4.33
                { "Ivanenko", 2, ME, 5, 4, { 4 } }    // avg = 4.33
            };

            int actualFound = BinSearch(s, N, "Ivanenko", 2, 4.33);
            Assert::AreEqual(2, actualFound);

            int actualNotFound = BinSearch(s, N, "Kovalenko", 3, 5.0);
            Assert::AreEqual(-1, actualNotFound);
        }
    };
}