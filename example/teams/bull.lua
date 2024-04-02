team = {
    name = "Bull",
    count = 2
}

turnActionType = {
    [0] = "None",
    [1] = "ProductionChange",
    [2] = "Strike"
}

getTurnAction = function()
    -- 1) Max production increase
    local list = actions:increase()
    if #list > 0 then
        table.sort(list, function(a, b) return a["delta"] > b["delta"] end)
        return { index = list[1]["id"] }
    end
    -- 2) Provoke strikes
    local strike = actions:strike()
    if next(strike) ~= nil then
        local opponents = data:opponents()
        table.sort(opponents, function(a, b) return a["production"] > b["production"] end)
        return { index = strike["id"], target = opponents[1]["id"] }
    end
    -- 3) Other
    local decreaseActions = actions:decrease()
    if #decreaseActions > 0 then
        table.sort(decreaseActions, function(a, b) return a["delta"] > b["delta"] end)
        return {index = decreaseActions[1]["id"]}
    end
end