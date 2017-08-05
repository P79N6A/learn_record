#!/usr/bin/env python
# coding=utf-8

import unittest
from testDuplic import DuplicTest
from testCalculator import CalculatorTest

def allTestSuit():
    suite_class = [
        DuplicTest,
        CalculatorTest,
    ]
    suite_list = []
    for suite in suite_class:
        suite_list.append(unittest.TestLoader().loadTestsFromTestCase(suite))

    # 去重
    func = lambda x,y:x if y in x else x + [y]
    suite_list = reduce(func, [[],], suite_list)
    return unittest.TestSuite(suite_list)

if __name__ == "__main__":
    unittest.main(defaultTest = 'allTestSuit')
