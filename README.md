![alt text](bin/starlyze-remove-bg.png)

<hr>

<h4 align="center">STARLYZE is a project of INFO0601 and INFO0604 at the University of Reims Champagne-Ardenne</h4>

<p align="center">
  <img src="bin/langage-c.svg">
  <img src="bin/ncurses.svg">
  <img src="bin/compiler.svg">
</p>

## What is Starlyze ? 

**Starlyze** is a networked multiplayer platform game in which each player controls a character and moves him through a world containing several levels. The objective is to reach the exit before the other players by collecting the keys to pass the portals, while avoiding the enemies, traps and bombs of the opponents. 

Players start simultaneously and can only move to the right or left, up and down the ladders. Enemies also move, and there are "life" and "bomb" items scattered throughout the world. The levels also have doors, blocks, traps and portals of different colors for which players must collect keys. 

Players have 5 lives, can lose lives by falling, coming into contact with enemies or being hit by a bomb. When a player loses a life, they become invincible for 3 seconds. If a player loses all their lives, they can start over at the beginning but lose all their progress.

## Application of Starlyze 

Starlyze has 3 parts: 

  - **A world editor**: allows you to create worlds and save them in a file
  - **A game server**: allows to launch a game and to manage the clients' connections
  - **A game client**: allows to play the game

## How to use Starlyze ?

// TODO

## How to compile Starlyze ?

### Requirements

  - **GCC** (version 7.3.0 or higher)
  - **Ncurses** (version 6.1 or higher)

### Compilation

To compile the project, you must first go to the project's root directory and then run the following command:

```bash
make
```

## Authors
  - **HADID Hocine** - @hocine280
  - **CHEMIN Pierre** - @PietroCookie