#!/usr/bin/env python2
# coding=utf-8

import unittest
import os,sys
from testDuplic import DuplicTest
from testCalculator import CalculatorTest
# for this gay , please use python2
from HTMLTestRunner import HTMLTestRunner

def allTestSuit():
    suite_class = [
        DuplicTest,
        CalculatorTest,
    ]
    suite_list = []
    for suite in suite_class:
        suite_list.append(unittest.TestLoader().loadTestsFromTestCase(suite))

    return unittest.TestSuite(suite_list)

if __name__ == "__main__":
    #unittest.main(defaultTest = 'allTestSuit')
    report_file = "html_report.html"
    fp = open(report_file, 'wb')
    runner = HTMLTestRunner(stream=fp, title='test title', description='this is a test')
    runner.run(allTestSuit())
    fp.close()

