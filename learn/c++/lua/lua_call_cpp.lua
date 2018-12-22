
-- excute open_mylualib(L)
local mylualib = require "mylualib"

print("lua call, 2 args")
sum, count = mylualib.c_add(1, 2);
print("sum is " .. sum)
print("argc is " .. count)

print("\n")
print("lua call ,3 args")
sum, count = mylualib.c_add(1, 2, 3);
print("sum is " .. sum)
print("argc is " .. count)

sum, count = mylualib.c_add(1, 2, "3");
print("\n")
print("sum is " .. sum)
print("argc is " .. count)

sum, count = mylualib.c_add(1, 2, "x");
print("\n")
print("sum is " .. sum)
print("argc is " .. count)

