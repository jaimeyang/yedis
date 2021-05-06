

local mysql = require "Mysql.lua"
-- 定义表名
local user = {}
-- 列的设计 key 是字段名 value 是数据类型
user.column = {
    id = {
        type = mysql.data_type.INT, 
        default = 0,
        auto_increament = true,
        len = 10,
        primary = false,
        unique = false,},
    user_name = {
        type = mysql.data_type.CHAR, 
        len = 20}    
}
-- 索引
user.indexs = {
    {'id'},
    {'id','user_name'}
}

-- 操作
user.findUserById = function(id)

end