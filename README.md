# Game of Life (C++)

This project is an implementation of **Conway’s Game of Life** using C++.  
It simulates a grid-based universe of cells that evolve over discrete generations according to simple rules of survival, death, and reproduction.  

## Overview
The universe consists of a **20x20 grid** of square cells.  
Each cell can be in one of two states:
- **Alive (L / `*`)**
- **Dead (D / empty space)**

The user can initialize which cells start alive by entering their grid indices.  
The simulation then progresses through generations, updating the state of the grid based on the rules of the Game of Life.  

## Rules
1. Any live cell with **fewer than 2 live neighbors** dies (underpopulation).  
2. Any live cell with **2 or 3 live neighbors** survives.  
3. Any live cell with **more than 3 live neighbors** dies (overpopulation).  
4. Any dead cell with **exactly 3 live neighbors** becomes alive (reproduction).  

## Key Features
- **Interactive initialization**: Users select the initial alive cells by grid number (0–399).  
- **Dynamic simulation**: Users can specify how many generations to run.  
- **Text-based visualization**:  
  - Alive cells are shown as `*`.  
  - Dead cells are shown as empty spaces.  
- **Reset option**: Users can restart the game multiple times within one session.  
- **Input validation**: Handles incorrect or out-of-range inputs gracefully.  

## Purpose
This project was built as part of a programming assignment to practice:
- **C++ fundamentals** (loops, conditionals, vectors).  
- **Object-Oriented Programming** (classes, encapsulation, modularity).  
- Designing simulations with **dynamic updates** and **user interaction**.  

The program demonstrates how a simple set of rules can create complex and evolving patterns across generations.  
