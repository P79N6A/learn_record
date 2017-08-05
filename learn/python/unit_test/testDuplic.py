#!/usr/bin/env python
# coding=utf-8
import unittest
from duplic import Duplic

class DuplicTest(unittest.TestCase):

    def setUp(self):
        self.cal = Duplic(8, 4)

    def tearDown(self):
        pass

    def test_add(self):
        result = self.cal.add()
        self.assertEqual(result, 12)

    def test_sub(self):
        result = self.cal.sub()
        self.assertEqual(result, 4)

    def test_mul(self):
        result = self.cal.mul()
        self.assertEqual(result, 32)

    def test_div(self):
        result = self.cal.div()
        self.assertEqual(result, 3)

if __name__ == "__main__":
    unittest.main()
