

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

function mysql.operator:create(tb)
    local sql_str = 'CREATE TABLE IF NOT EXISTS %s (' .. 
        '%s' .. 
        'PRIMARY KEY (%s)' ..
        ') ENGINE=%s DEFAULT CHARSET=%s COLLATE=%s'
    
    local columns = ''
    for k,v in pairsByKeys(tb.columns) do
        columns = columns .. ' ' .. k .. ' ' .. v .. ','
    end

    local pk = ''
    for k,v in pairsByKeys(tb.primary_keys) do
        pk = pk .. v .. ','
    end
    pk = string.sub(pk,1,-2)
    if tb.engine == nil then
        print('egine is nil,default is innodb')
        tb.engine = 'INNODB'
    end
    
    if tb.default_char_set == nil or tb.default_collate == nil then
        print('default_char_set or default_collate is nil')
        return
    end
    sql_str = string.format(sql_str,tb.name,columns,pk,tb.engine,tb.default_char_set,tb.default_collate)
    print('sql_str:',sql_str)
    obj:create(sql_str)
    self:createIndex(tb.name,tb.indexs)
end
-- create index   
function mysql.operator:createIndex(tb_name,tb_index)
     print('createIndex name \n')
     local c_index_str = 'CREATE %s INDEX %s ON %s (%s);'
     for i,v in pairsByKeys(tb_index) do
         print('i',i)
         v.type = v.type ~= nil and v.type or ''            
         local sql_str = string.format(c_index_str,v.type,v.name,tb_name,v.cols)
         obj:createIndex(sql_str)
     end
end

mysql.operator.select = function(self)

    return operator
end

mysql.operator.update = function(...)

end

function mysql.operator:insert(tb)
    local sql_str = 'INSERT INTO %s (%s) VALUES (%s);'
    
    local name = ''
    local value = ''
    for k,v in pairsByKeys(tb.columns) do
        if tb[k] ~= nil then
            name = name .. k .. ','
            value = value .. '\'' .. tb[k] .. '\'' .. ','
        end        
    end
    name = string.sub(name,1,-2)
    value = string.sub(value,1,-2)
    sql_str = string.format(sql_str,tb.name,name,value)
    print('insert: ',sql_str)
    obj:query(sql_str)
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