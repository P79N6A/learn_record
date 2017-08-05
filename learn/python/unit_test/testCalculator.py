#!/usr/bin/env python
# coding=utf-8

import sys
import unittest
## if python 3, mock is in unittest
#from unittest import mock
## if python 2, you nedd to install module mock
## pip install mock
import mock
from calculator import Calculator

def my_print(str):
    pass
    #print(str)

class CalculatorTest(unittest.TestCase):

    def setUp(self):
        my_print("setUpcall")
        self.cal = Calculator(8, 4)
        #assert 1 == 2, "test if setUp error"

    def tearDown(self):
        my_print("tearDowncall")
        self.cal = None

    def test_add(self):
        '''
        des : test add
        '''
        my_print("test add")
        result = self.cal.add()
        self.assertEqual(result, 12)
        # if use python builtin assert , it will stop run
        # assert result == 12, "add error"

    def test_add_xx(self):
        result = self.cal.add_xx()
        self.assertNotEqual(result, 12)

        self.cal.add_xx = mock.Mock(return_value=12)
        result = self.cal.add_xx()
        self.assertEqual(result, 12)

    def test_sub(self):
        my_print("test sub")
        result = self.cal.sub()
        self.assertEqual(result, 4)

    def test_mul(self):
        my_print("test mul")
        result = self.cal.mul()
        self.assertEqual(result, 32)

    def test_div(self):
        my_print("test div")
        result = self.cal.div()
        self.assertEqual(result, 2)

    @unittest.skip('just skip')
    def test_div_1(self):
        result = self.cal.div()
        self.assertEqual(result, 3)

    @unittest.skipIf(Calculator.__version__ < 5, 'not support this library')
    def test_div_2(self):
        result = self.cal.div()
        self.assertEqual(result, 2)

    @unittest.skipIf(Calculator.__version__ < 2, 'not support this library')
    def test_div_3(self):
        result = self.cal.div()
        self.assertEqual(result, 2)

    @unittest.skipUnless(sys.platform.startswith('win'),  'windows')
    def test_div_4(self):
        result = self.cal.div()
        self.assertEqual(result, 2)

    @unittest.skipUnless(sys.platform.startswith('linux'),  'linux')
    def test_div_5(self):
        result = self.cal.div()
        self.assertEqual(result, 2)

def suite1():
    suite = unittest.TestSuite()
    suite.addTest(CalculatorTest("test_add"))
    suite.addTest(CalculatorTest("test_sub"))
    return suite

def suite2():
    # 指定前缀
    suite = unittest.makeSuite(CalculatorTest, 'test')
    return suite

if __name__ == "__main__":

    ## 运行用例方法1
    #my_print("Test suit : run some testcase")
    #runner = unittest.TextTestRunner()
    #runner.run(suite1())

    ## 运行用例方法2
    #my_print("Test suit : run all testcase")
    #runner.run(suite2())

    ## 运行用例方法3
    # python ./testCalculator.py -v
    # python ./testCalculator.py -v testCalculator.test_add
    my_print("Run all testcase dircetly")
    unittest.main()

