local Student = require "student"

s1 = Student.create()
Student.set(s1,"orientlu_1");
print(Student.get(s1))

s1 = Student.create()
Student.set(s1,"orientlu_2");
print(Student.get(s1))
