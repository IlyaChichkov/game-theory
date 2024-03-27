team = {
    name = "Randy",
    count = 1
}

turnActionType = {
    [0] = "None",
    [1] = "ProductionChange",
    [2] = "Strike"
}

turnData = {}

getTurnAction = function(turnData)
    actionIndex = math.random(turnData["this"]["actions_count"])
    if turnActionType[turnData["this"]["actions"][actionIndex]["type"]] == "Strike" then
        return {index = actionIndex, target = turnData["opponents"][1]["id"]}
    end
    return {index = actionIndex}
end