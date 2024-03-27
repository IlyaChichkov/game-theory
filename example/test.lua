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
    printLn("> compute...")
    printLn(turnData["this"]["name"])
    printLn(turnData["this"]["funds"])
    printLn(turnData["this"]["production"])

    printLn("actions_count:")
    printLn(turnData["this"]["actions_count"])
    actionIndex = math.random(turnData["this"]["actions_count"]) - 1
    if turnActionType[turnData["this"]["actions"][actionIndex]["type"]] == "Strike" then
        printLn("yes")
    else
        printLn("no")
    end

    return actionIndex
end