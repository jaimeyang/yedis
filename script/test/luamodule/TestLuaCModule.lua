

function test()
    t = TestModule()
    ret = t:test(1,2)
    print(ret)
    t = nil
    collectgarbage('collect')
end


test()