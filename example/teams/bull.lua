team = {
    name = "Bull",
    count = 3
}

turnActionType = {
    [0] = "None",
    [1] = "ProductionChange",
    [2] = "Strike"
}

getTurnAction = function(turnData)
    -- 1) Max production increase
    local increaseActions = {}
    for i = 1, turnData["this"]["actions_count"] do
        if turnActionType[turnData["this"]["actions"][i]["type"]] == "ProductionChange" and turnData["this"]["actions"][i]["delta"] > 0 then
            table.insert(increaseActions, turnData["this"]["actions"][i])
            print(turnActionType[turnData["this"]["actions"][i]["delta"]])
        end
    end
    if #increaseActions > 0 then
        table.sort(increaseActions, function(a, b) return a["delta"] > b["delta"] end)
        return {index = increaseActions[1]["id"]}
    end
    -- 2) Provoke strikes
    local strikeActions = {}
    for i = 1, turnData["this"]["actions_count"] do
        if turnActionType[turnData["this"]["actions"][i]["type"]] == "Strike" then
            table.insert(strikeActions, turnData["this"]["actions"][i])
        end
    end
    if #strikeActions > 0 then
        local opponents = turnData["opponents"]
        table.sort(opponents, function(a, b) return a["production"] > b["production"] end)
        return {index = strikeActions[1]["id"], target = opponents[1]["id"]}
    end
    -- 3) Other
    local decreaseActions = turnData["this"]["actions"]
    if #decreaseActions > 0 then
        table.sort(decreaseActions, function(a, b) return a["delta"] < b["delta"] end)
        return {index = decreaseActions[1]["id"]}
    end
end