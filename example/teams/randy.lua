team = {
    name = "Randy",
    count = 1
}

turnActionType = {
    [0] = "None",
    [1] = "ProductionChange",
    [2] = "Strike"
}

getTurnAction = function()
    local all_actions = actions:all()
    local randomIndex = math.random(#all_actions)
    local randomOpponent = math.random(#data:opponents())
    if turnActionType[all_actions[randomIndex]["type"]] == "Strike" then
        return {index = all_actions[randomIndex]["id"], target = data:opponents()[randomOpponent]["id"]}
    end
    return {index = all_actions[randomIndex]["id"]}
end