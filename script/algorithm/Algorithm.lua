


function mergeTable(indexs,values)
    local tb = {}
    for k,v in ipairs(indexs) do
        tb[k] = values[v]
    end
    return tb
end