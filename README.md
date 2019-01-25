# Semester Project
---

## Topic
My semester project topic is simulation of Conway's Game of Life. There is grid 20x20 with cells. Cells can be in one of two states dead or alive (0, 1 respectively). Every cell has 8 logical neighbours except border cells. 
## Rules
There are four rules:
1. Any alive cell with fewer than two alive neighbours dies, as if by underpopulation.
2. Any alive cell with two or three alive neighbours lives on to the next generation.
3. Any alive cell with more than three alive neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three alive neighbours becomes a alive cell, as if by reproduction.

## How to launch?
1. Copy Repository
```sh
git clone https://github.com/fiedosiukr/semester-project
```
2. Open project in Visual Studio and compile

## User input
User can insert his own data changing file ```data.txt```. In file there is 20x20 grid, 0 and 1 corespond dead and alive cell respectively. User can also delete file, if program doesn't find file ```data.txt``` cells will be randomly generated.
