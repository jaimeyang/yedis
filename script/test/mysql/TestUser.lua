
-- require 'test'
local mysql = require '..script.db.Mysql'
require '..script.algorithm.Algorithm'
-- 定义表名
local user = {}
-- 列的设计 key 是字段名 value 是数据类型
user.name = 'user'
user.columns = {
    id = 'INT NOT NULL AUTO_INCREMENT',
    user_name = 'VARCHAR(20) NOT NULL',
    pwd = 'VARCHAR(20) NOT NULL'
}
-- 主键
user.primary_keys = {
    'id',    
}
-- 外键
user.foreign_key = {} 
-- 索引
user.indexs = {
    [1] = {name = 'pwd',cols = 'pwd',type = 'UNIQUE'},
    [2] = {name = 'id_user',cols = 'id,user_name'}
}

user.engine = 'INNODB'

user.default_char_set = 'utf8mb4'
-- COLLATE会影响到ORDER BY语句的顺序，会影响到WHERE条件中大于小于号筛选出来的结果
-- 凡是涉及到字符类型比较或排序的地方，都会和COLLATE有关
user.default_collate = 'utf8mb4_general_ci'

user.create = function()
    mysql.operator:create(user)
end

-- 操作
user.findUserById = function(id)
   
end

user.insertUser = function(user_name,pwd) 
    user.user_name = user_name
    user.pwd = pwd
    mysql.operator:insert(user)
end

function TestConnect()
    print("connect begin")
    mysql.connect()
end

function TestCrate()
    print('create')
    user.create()
end

function TestInsert()
    user.insertUser('jaime2','145789')
end

function Test()
    TestConnect()
    -- TestCrate()
    TestInsert()
end




