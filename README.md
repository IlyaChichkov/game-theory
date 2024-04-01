# Production | Economy game

## Overview

An implementation of small educational turn-based economy game where teams each turn 
select card from starting limited deck. By default, the game consists of 14 moves and
the same number of cards, respectively. Teams vary their earnings according to the unit
price tables and production expenses.

## Default deck

**x2** `Increase production: +10`

**x2** `Increase production: +20`

**x2** `Increase production: +30`

**x1** `Increase production: +50`

**x1** `Production unchanged`

**x2** `Decrease production: -10`

**x2** `Decrease production: -20`

**x2** `Provoke strike`

## API

**actionMap**

```lua
-- Get increase production cards
actionMap:get_incr()
--> returns table:
{
    [0] = {
    "id" = action_id
    "delta" = production_delta
    },
    [1] = ...
}

-- Get decrease production cards
actionMap:get_decr() 
--> returns table:
{
    [0] = {
    "id" = action_id
    "delta" = production_delta
    },
    [1] = ...
}

-- Get strike cards
actionMap:get_strike()
--> returns table:
{
    [0] = {
    "id" = action_id
    },
    [1] = ...
}

-- Get all cards
actionMap:get_all()
--> returns table:
{
    [0] = {
    "id" = action_id
    "type" = card_type -- [0]: None; [1]: Change production; [2]: Provoke strike
    },
    [1] = ...
}

actionMap:get_prod_change(int value)

```

## Examples

[Example lua scripts](./example/)