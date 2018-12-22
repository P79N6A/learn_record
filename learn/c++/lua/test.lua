
function print_name(...)
    print("inLua" .. ":" .. ...);
end

function add(x, y)
    print_name("add");
    -- print("inLua [" .. debug.getinfo(1).name .. "]");
    return x + y;
end

function mul(x, y)
    print_name("mul");
    -- print("inLua [" .. debug.getinfo(1).name .. "]");
    return x * y;
end

-- will run when dofile
print("--> lua call by cpp")
print(add(1,2))
