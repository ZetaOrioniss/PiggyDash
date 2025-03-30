# Piggy Dash

This is a simple dice game where players take turns rolling a die to accumulate points. The first player to reach **100 points** wins the game. The game supports both **human players** and **AI bots**.

## How to Play

1. Players take turns rolling a **6-sided die**.
2. If a player rolls a **1**, they lose all points accumulated in that round and their turn ends.
3. Players can **choose to bank** their points at any time, adding them to their total score and ending their turn.
4. The first player to reach **100 points** wins the game.
5. Bots make decisions automatically based on probability.

## Installation & Execution

- On Linux (Debian)
``` sh
apt install gcc
git clone https://github.com/ZetaOrioniss/PiggyDash.git
cd PiggyDash
```

### Prerequisites
- **C Compiler** (GCC recommended)
- **Linux/Mac** (or Windows with WSL)

### Compilation
To compile the game, run:
```sh
gcc -o piggy piggy.c && chmod +x piggy
```

### Run the Game
Execute the compiled program:
```sh
./piggy
```

## Features
- **Supports up to 10 players** (both humans and bots).
- **Turn-based gameplay** with real-time interaction.
- **AI Bots** make decisions.
- **Colorful terminal output** for better visibility.

## Author
NEDJAM ***Ylan***

