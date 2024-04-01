team = {
    name = "Rage",
    count = 1
}

turnActionType = {
    [0] = "None",
    [1] = "ProductionChange",
    [2] = "Strike"
}

getTurnAction = function()
    if turnData.turn == 2 or turnData.turn == turnData.turnsCount / 2 then
        -- 1) Provoke strikes
        local strike = actionMap:get_strike()
        if strike["index"] ~= nil then
            local opponents = turnData:get_opponents()
            table.sort(opponents, function(a, b) return a["production"] > b["production"] end)
            return { index = strike["index"], target = opponents[1]["id"] }
        end
    end
    -- 2) Max production increase
    local list = actionMap:get_incr()
    if #list > 0 then
        table.sort(list, function(a, b) return a["delta"] > b["delta"] end)
        if #list < 2 then
            return { index = list[1]["id"] }
        else
            return { index = list[2]["id"] }
        end
    end
    -- 3) Decrease production
    local decreaseActions = actionMap:get_decr()
    if #decreaseActions > 0 then
        table.sort(decreaseActions, function(a, b) return a["delta"] > b["delta"] end)
        return {index = decreaseActions[1]["id"]}
    end
end