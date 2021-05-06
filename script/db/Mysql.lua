

local mysql = {}

mysql.data_type = {}

mysql.data_type.TINYINT = 1
mysql.data_type.SMALLINT = 2
mysql.data_type.MEDIUMINT = 3
mysql.data_type.INT = 4
mysql.data_type.BIGINT = 5
mysql.data_type.DECIMAL = 6

mysql.data_type.UNSIGNED_TINYINT = 7
mysql.data_type.UNSIGNED_SMALLINT = 8
mysql.data_type.UNSIGNED_MEDIUMINT = 9
mysql.data_type.UNSIGNED_INT = 10
mysql.data_type.UNSIGNED_BIGINT = 11
mysql.data_type.UNSIGNED_DECIMAL = 12

mysql.CHAR = 13
mysql.VARCHAR = 14



mysql.operator = {}

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


mysql.setting.setAutoCommint = function()

end


return mysql