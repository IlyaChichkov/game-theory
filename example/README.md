## Making custom team script

Each team script requires **team** table and **getTurnAction** function

```lua
team = {
    name = "team-name",
    count = 2 -- The number of these teams during a match 
}

getTurnAction = function()
    return {}
end
```

The **getTurnAction** function should return table, that values depend on
the type of returning action.

```lua
return { index = Selected_Action["id"], target = index = Selected_Opponent["id"] }
```

```lua
return { index = Selected_Action["id"] }
```

## API

**actions**

```lua
-- Get increase production cards
actions:increase()
--> returns table:
{
    [0] = {
    "id" = action_id
    "delta" = production_delta
    },
    [1] = ...
}

-- Get decrease production cards
actions:decrease() 
--> returns table:
{
    [0] = {
    "id" = action_id
    "delta" = production_delta
    },
    [1] = ...
}

-- Get strike cards
actions:strike()
--> returns table:
{
    [0] = {
    "id" = action_id
    },
    [1] = ...
}

-- Get all cards
actions:all()
--> returns table:
{
    [0] = {
    "id" = action_id
    "type" = card_type -- [0]: None; [1]: Change production; [2]: Provoke strike
    "delta" = production_delta ([warning!] only if type == 1)
    },
    [1] = ...
}

actions:change_production(int value)
--> returns table:
{
    "id" = action_id
    "delta" = production_delta
}
-- [NOTE] return empty table if action wasn't found

```

**data**

```lua

data.id (integer)
--> current team id

data.turn (integer)
--> current turn

data.turnsCount (integer)
--> total amound of turns during the match

-- Get match opponents
data:opponents()
--> returns table:
{
    [0] = {
    "id" = opponent_id
    "production" = opponent_production
    "funds" = opponent_funds
    },
    [1] = ...
}
```