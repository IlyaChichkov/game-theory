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

## Build & Run

```bash
git clone git@github.com:IlyaChichkov/game-theory.git
```

```bash
mkdir build
cd build
cmake ..
```

```bash
cp -r ../example/teams ./
./game_theory
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

## Examples

[Example lua scripts](./example/)