![Logo Starlyze](bin/starlyze-remove-bg.png)

<hr>

STARLYZE is a project of INFO0601 and INFO0604 at the University of Reims Champagne-Ardenne

![Langage c](bin/langage-c.svg)
![Ncurses](bin/ncurses.svg)
![Compiler](bin/compiler.svg)



## What is Starlyze ? 

**Starlyze** is a networked multiplayer platform game in which each player controls a character and moves him through a world containing several levels. The objective is to reach the exit before the other players by collecting the keys to pass the portals, while avoiding the enemies, traps and bombs of the opponents. 

Players start simultaneously and can only move to the right or left, up and down the ladders. Enemies also move, and there are "life" and "bomb" items scattered throughout the world. The levels also have doors, blocks, traps and portals of different colors for which players must collect keys. 

Players have 5 lives, can lose lives by falling, coming into contact with enemies or being hit by a bomb. When a player loses a life, they become invincible for 3 seconds. If a player loses all their lives, they can start over at the beginning but lose all their progress.

## Application of Starlyze 
Starlyze has 3 parts: 
  - **A world editor**: allows you to create worlds and save them in a file
  - **A game server**: allows to launch a game and to manage the clients' connections
  - **A game client**: allows to play the game

## How to compile Starlyze ?
### Requirements
  - **GCC** (version 7.3.0 or higher)
  - **Ncurses** (version 6.1 or higher)

### Compilation
To compile the project, you must first go to the project's root directory and then run the following command:

```bash
make
```
## How to use Starlyze ?
### **World Editor**
In order to create a world with different levels within it. You need to launch a terminal at the root of the ```code/``` folder.

To launch the world editor, you must run the following command:

```bash
/bin/editor name_world.world
```
- name_world.world : the name of the world you want to create

For what follows, the programs should be run in the following order:
### **Server**

To launch the server, you must run the following command:

```bash
/bin/server port
```
- port : the port on which the server will listen

***Example:*** 
```bash
/bin/server 2048
```

### **Client**

To launch the client and play of game, you must run the following command:

```bash
/bin/client address_ip port
```
- address_ip : the address of the server
- port : the port on which the server is listening

***Example:***
```bash 
/bin/client 127.0.0.1 2048
```

Once the client is launched, simply follow the instructions on the screen.

**Game control:**  
  
- **Z** : move up
- **Q** : move left
- **S** : move down
- **D** : move right
- **G** : place a bomb
- **E** : go through a door
- **N** : quit the game

## Documentation
The documentation of the project is available in the ```doc/``` folder.

This was generated with Doxygen, so you can view it by opening the file ``index.html``, which is located in ``doc/html/`` in your browser or the PDF file, which is located at the root of ```doc/```.

## Authors
  - **HADID Hocine** - @hocine280
  - **CHEMIN Pierre** - @PietroCookie