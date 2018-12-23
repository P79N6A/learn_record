local Student = require "student"

s1 = Student.create()
s1:set("orientlu_1");
print(s1:get())

s1 = Student.create()
s1:set("orientlu_2");
print(s1:get())
