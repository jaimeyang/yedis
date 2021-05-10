

local mysql = {}

mysql.data_type = {}

mysql.data_type.TINYINT = 'TINYINT'
mysql.data_type.SMALLINT = 'SMALLINT'
mysql.data_type.MEDIUMINT = 'MEDIUMINT'
mysql.data_type.INT = 'INT'
mysql.data_type.BIGINT = 'BIGINT'
mysql.data_type.DECIMAL = 'DECIMAL'


mysql.CHAR = 13
mysql.VARCHAR = 14


local obj = nil

mysql.connect = function()
    obj = Mysql()
    obj:connect("192.168.1.113","yedis","123456","yedis",3306)
end

mysql.operator = {}

mysql.create = function(tb) 
    
    local str = "CREATE TABLE IF NOT EXISTS " .. tb.name .. ' ('
    for i,v in pairs(tb.column) do
        str = str .. ' ' .. i .. ' ' .. v .. ','
    end
    -- 主键
    str = str .. ' PRIMARY KEY ('
    local pri_len = #tb.primary_key
    for i,v in ipairs(tb.primary_key) do
        if i < pri_len then
            str = str .. v .. ', '
        else            
            str = str .. v .. ')' .. ''
        end
        
    end
    str = str .. ')'
   
   if tb.default_char_set ~= nil then
        str = str .. 'DEFAULT CHARSET=' .. tb.default_char_set .. ' '

        if tb.default_collate ~= nil then
            str = str .. 'COLLATE=' .. tb.default_collate .. ' '
        end
    end


    tb.engine = tb.engine == nil and 'INNODB' or tb.engine
    str = str .. 'ENGINE= ' .. tb.engine .. ';'
    
    print('create str',str)
    obj:create(str)
    -- create index    
    if tb.indexs ~= nil then
        local c_index_str = 'CREATE %s INDEX %s ON %s (%s)'
        for i,v in ipairs(tb.indexs) do
            print('i',i)
            v.type = v.type ~= nil and v.type or ''            
            local sql_str = string.format(c_index_str,v.type,v.name,tb.name,v.cols)
            print('create index ',sql_str)
            obj:createIndex(sql_str)
        end
    end
end

mysql.operator.select = function(operator, ...)

    return operator
end

mysql.operator.update = function(...)

end

mysql.operator.insert = function()

end

mysql.operator.del = function()
end

mysql.operator.from = function(tb_name) 

end

mysql.operator.where = function(codition)

end


mysql.operator.mand = function(key,value)

end

mysql.operator.mor = function(key,value)

end

mysql.operator.orderby = function()

end

mysql.operator.groupby = function()

end

mysql.operator.limit = function()

end

mysql.operator.like = function()

end

mysql.operator.excute = function()

end

mysql.operator.raw = function()

end

mysql.operator.startTransition = function()

end

mysql.operator.commit = function()

end

mysql.operator.rollback = function()

end


-- mysql.setting.setAutoCommint = function()

-- end


return mysql