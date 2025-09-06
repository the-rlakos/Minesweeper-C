# Minesweeper-C (Console)

A small console **Minesweeper** in **C** (9×9 grid, 10 mines). The goal is to reveal all non-mine cells. You lose if you reveal a mine.

## How it Works (High Level)
1. The board uses 2D arrays for **mines**, **adjacent counts**, **revealed flags**, and **flag markers**.
2. Mines are placed **after your first reveal**, guaranteeing that first click is safe.
3. `compute_adj()` counts the mines around each cell.
4. Revealing a `0` triggers a recursive **flood fill** to reveal neighbors.
5. The main loop reads commands (`r x y`, `f x y`, `q`), updates the board, and checks win/lose conditions.

## Controls
- `r x y` → reveal cell **(x, y)**
- `f x y` → flag/unflag cell **(x, y)**
- `q`     → quit

Coordinates start at **0** (e.g., `r 3 4`).

## File Structure
```
Minesweeper-C/
└─ main.c
```

## Build & Run
```bash
gcc -o minesweeper main.c
./minesweeper
```

## Next Steps (Optional)
- Add different board sizes and mine counts.
- Track a timer and best scores.
- Use `ncurses` for a nicer terminal UI.
