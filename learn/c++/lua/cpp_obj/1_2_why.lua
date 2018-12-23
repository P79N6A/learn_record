
function fun(table, ...)
    print(table)
    print(...)
    return "return by __index()"
end

-- ltable = setmetatable({}, {})
-- lmetatable = getmetatable(ltable)
ltable = {}
print(ltable)
lmetatable = {__index = fun}
setmetatable(ltable, lmetatable)

ltable["yy"] = "yy"
print(ltable["yy"])
print(ltable["xx"])

-- __index包含一个函数的话，Lua就会调用那个函数，table和键会作为参数传递给函数。
-- __index 元方法查看表中元素是否存在，如果不存在，返回结果为 nil；如果存在则由 __index 返回结果。
--
--
---- lua 类
--
print('--- lua class')


BaseClass = {name = "BaseClass_name"}

function BaseClass:new(o)
    o = o or {} -- new table

    -- 这里，新表就会以 Baseclass 为元表(父类)
    setmetatable(o, self)
    self.__index = self -- 元表的__index

    print(o.name) -- 通过元表读取到
    return o
end

function BaseClass:getName()
    return self.name
end

obj = BaseClass:new(nil)
-- obj is a new table  obj.metatable = BaseClass
print(obj:getName())
BaseClass.name = "new name"
print(obj:getName())
obj.name = "setobjname"
print(obj:getName())
BaseClass.name = "new name2"
print(obj:getName())
