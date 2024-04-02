# Production | Economy game

## Overview

- [Description](#description)
    - [Default deck](#default-deck)
- [Build & Run](#build--run)
- [Examples & API](#examples--api)

## Description

An implementation of small educational turn-based economy game where teams each turn
select card from starting limited deck. By default, the game consists of 14 moves and
the same number of cards, respectively. Teams vary their earnings according to the unit
price tables and production expenses.

This program allows to create custom scripts with lua language and run game matches,
comparing effectiveness of different economy strategies.

## Default deck

| **x2** `Increase production: +10` |   **x2** `Decrease production: -10`    |
|---|------------------------------------|
|**x2** `Increase production: +20` |  **x1** `Production unchanged` |
| **x2** `Increase production: +30` | **x2** `Decrease production: -20` |
| **x1** `Increase production: +50` |  **x2** `Provoke strike` |

## Build & Run

Clone repository:

```bash
git clone git@github.com:IlyaChichkov/game-theory.git
```

Build with CMake:

```bash
mkdir build
cd build
cmake ..
```

Copy default teams folder and run the program:

```bash
cp -r ../example/teams ./
./game_theory
```

## Examples & API

[Making custom team](./example/)

[Team examples](./example/teams)
