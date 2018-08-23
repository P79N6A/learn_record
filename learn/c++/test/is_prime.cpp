/*************************************************************************
> File Name: is_prime.cpp
> Author: orientlu
> Mail: lcdsdream@126.com
> Created Time: Thu 23 Aug 2018 11:21:53 AM CST
************************************************************************/
#include<iostream>

namespace lala {
    class Prime {
        // A prime number is an integer greater than 1 that has no
        // divisors smaller than itself other than 1
        public:
        Prime () {};
        static void printPrime(int val);
        static bool isPrime(int val);
        static bool isDivisable(int val, int divs);
        ~Prime() {};
    };

    void Prime::printPrime(int val)
    {
        int count = 0;
        printf("prime 2~%d >> \n", val);
        for (int i = 0; i <= val; ++i) {
            if (isPrime(i)) {
                printf("%d ", i);
                if ((++count % 10) == 0) {
                    printf("\n");
                }
            }
        }
        if (count % 10 != 0)
            printf("\n");
    }

    bool Prime::isPrime(int val)
    {
        bool rnt = false;
        if (val >= 2 && !isDivisable(val, 2)) {
            rnt = true;
        }
        return rnt;
    }

    bool Prime::isDivisable(int val, int divs)
    {
        if (val <= divs) {
            return false;
        } else if (val % divs == 0) {
            return true;
        } else {
            return isDivisable(val, divs + 1);
        }
    }

};

int main(int argc, char *argv[])
{
    lala::Prime::printPrime(0);
    lala::Prime::printPrime(1);
    lala::Prime::printPrime(2);
    lala::Prime::printPrime(101);
    return 0;
}
