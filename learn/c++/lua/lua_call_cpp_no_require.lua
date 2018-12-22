

print("lua call, 2 args")
sum, count = mylualib.c_add(1, 1);
print("sum is " .. sum)
print("argc is " .. count)

