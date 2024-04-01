team = {
    name = "Bull",
    count = 3
}

turnActionType = {
    [0] = "None",
    [1] = "ProductionChange",
    [2] = "Strike"
}

getTurnAction = function()
    -- 1) Max production increase
    local list = actionMap:get_incr()
    if #list > 0 then
        table.sort(list, function(a, b) return a["delta"] > b["delta"] end)
        return { index = list[1]["id"] }
    end
    -- 2) Provoke strikes
    local strike = actionMap:get_strike()
    if strike["index"] ~= nil then
        local opponents = turnData:get_opponents()
        table.sort(opponents, function(a, b) return a["production"] > b["production"] end)
        return { index = strike["index"], target = opponents[1]["id"] }
    end
    -- 3) Other
    local decreaseActions = actionMap:get_decr()
    if #decreaseActions > 0 then
        table.sort(decreaseActions, function(a, b) return a["delta"] > b["delta"] end)
        return {index = decreaseActions[1]["id"]}
    end
end