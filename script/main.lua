---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by jaime.
--- DateTime: 2021/2/19 下午11:06
---
local s = "sss"

function test(s1)

end

function main()
    print(collectgarbage("count"))
    local t1 = "qwertyuiopasdfghjklzxcvbnm1234567890123411"
    t1 = 's' .. t1
    print(collectgarbage("count"))
    return t1
end