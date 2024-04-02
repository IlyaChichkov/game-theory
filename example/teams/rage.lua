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
    if data.turn == 2 or data.turn == data.turnsCount / 2 then
        -- 1) Provoke strikes
        local strike = actions:strike()
        if strike["id"] ~= nil then
            local opponents = data:opponents()
            table.sort(opponents, function(a, b) return a["production"] > b["production"] end)
            return { index = strike["id"], target = opponents[1]["id"] }
        end
    end
    -- 2) Max production increase
    local list = actions:increase()
    if #list > 0 then
        table.sort(list, function(a, b) return a["delta"] > b["delta"] end)
        if #list < 2 then
            return { index = list[1]["id"] }
        else
            return { index = list[2]["id"] }
        end
    end
    -- 3) Decrease production
    local decreaseActions = actions:decrease()
    if #decreaseActions > 0 then
        table.sort(decreaseActions, function(a, b) return a["delta"] > b["delta"] end)
        return {index = decreaseActions[1]["id"]}
    end
end