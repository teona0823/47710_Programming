# Programming (47710) - Assignment
## Project Goal
Implementing Tic-Tac-Toe Game With C language.

## Period
2023 Fall Semester

Nov. 15th. 2023 (Wed) ~ Dec. 5th. 2023 (Tue)

## Requirements
- Get the console size: ```GetConsoleScreenBufferInfo()```
- Change console font color: ```SetConsoleTextAttribute()```
- The input value is a value from 1 to 9, and the row and column can be known using the / and % operations.
- Draw a 3x3 board, and decide win or lose
- Update internal arrays and boards by receiving valid input
- Computer(AI) puts (randomly selects valid inputs)
- **Minimax Algorithm**
- Step-by-step AI level phase

## Functions
### 1. Select Difficulty
When you enter the game, you can select AI's difficulty ((1) Easy / (2) Normal / (3) Hard)

**(1) Easy Mode:** AI places in any positions ***randomly***, no matter where you placed.

**(2) Normal Mode:** AI does only attack and defend, if there are **two same puts in a row**.

**(3) Hard Mode:** AI is worked by Minimax Algorithm, so it's very hard to win.

### 2. Play First or Second
You can choose whether play first or play second.

### 3. Win/Lose Record
Your win/lose/draw record will be placed in the main menu. (Regardless of the difficulty)

## Minimax Algorithm
This is the most important part of the assignment.

The name of the algorithm is a product of two words: minimize and maximize. That is, minimize the payoff for the opponent, maximize the payoff for yourself. If a sequence of moves leads to a victory, its payoff is evaluated at +10 points. If it leads to a loss, the payoff is -10. If a sequence ultimately results in a draw, the payoff it brings to the table is 0.

As an example, let’s look at the near end of a game, when it’s turn for Player X to make a move:

![image](https://github.com/teona0823/47710_Programming/assets/129267777/a029ce5c-fb3b-4a0c-a6d4-8cc46fc4d5aa)

Source of the picture: <https://www.neverstopbuilding.com/blog/minimax>

Out of the three available nodes the initial state node is connected to, the one on the left yields the greatest payoff (+10 points), so this is the move to make.

Similarly, player O is trying to maximize their own payoff. Player X knows this and evaluates their opponent’s moves as well. The following picture serves as a good example of this process:

![image](https://github.com/teona0823/47710_Programming/assets/129267777/419ada86-2feb-4a9c-a5e3-4c62f7e379a6)

Source of the picture: <https://www.neverstopbuilding.com/blog/minimax>

Both top nodes are states of the board (move sequences) which bring a payoff of -10. Even though there is a two-step path to a node with a payoff of +10, there is an obvious choice Player O will make (the algorithm assumes them to be a perfect minimizer) that will yield a good outcome for them (and a bad one for Player X).

The Minimax algorithm evaluates the payoff of each available move by taking turns for the minimizer and the maximizer. The following picture is a perfect example of the evaluation process:

![image](https://github.com/teona0823/47710_Programming/assets/129267777/d4c6b8e2-8083-4e1b-ad12-8ec39750c271)

Source of the picture: <https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move>

Here, the initial state is node 1, so X has three possible moves. The payoff for node 2 is -10 (I explained why in the previous example). The payoff for node 3 is 0, because Player O is assumed to be the perfect minimizer, and therefore will not allow X to get +10. The payoff for node 4 is +10, so this is the move to make.

The Minimax Tic-Tac-Toe algorithm is impossible to beat, and when two Minimaxes play against each other, every move they make is the best response to what the opponent could possibly do (Nash equilibrium), resulting in 100% chance of a draw.
