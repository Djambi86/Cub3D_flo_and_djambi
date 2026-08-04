*This project has been created as part of the 42 curriculum by dabdulka, flaplanc.*

# cub3D

## Description

cub3D is a first-person raycasting engine inspired by Wolfenstein 3D,
built from scratch in C using the miniLibX graphics library. Given a
`.cub` scene file describing a maze, wall textures, and floor/ceiling
colors, the program parses the scene, then renders a real-time,
first-person 3D view of the maze using ray-casting (a simplified,
2D-map-based precursor to full 3D rendering).

The goal of the project is to explore ray-casting mathematics, basic
graphics-window programming, and rigorous C project structure (parsing,
error handling, memory management) rather than to build a fully-featured
game engine.

**Mandatory part features:**
- Strict `.cub` scene parser (textures, floor/ceiling colors, map),
  with full error detection and explicit `Error\n` messages.
- Map validation: allowed character set, single player spawn, and a
  closed/surrounded-by-walls check (flood fill).
- Real-time ray-casting renderer (DDA algorithm) with walls textured
  differently depending on which side (North/South/East/West) is hit.
- Solid floor and ceiling colors, configurable per scene.
- Smooth window management (minimizing, focus changes, etc. via miniLibX).
- Player movement (`W`/`A`/`S`/`D`) and look/rotate (arrow keys).
- Clean exit on `ESC` or on clicking the window's close button, with all
  allocated memory and miniLibX resources properly released.

## Instructions

### Compilation

```sh
make        # builds the cub3D binary (also builds libft and miniLibX)
make clean  # removes object files
make fclean # removes object files and the binary
make re     # fclean + all
```

The Makefile builds `libft` and `miniLibX` from their vendored sources
under `includes/Libft` and `includes/mlx`, so no system-wide miniLibX
installation is required (only its usual system dependencies:
`libx11-dev`, `libxext-dev`, `libbsd-dev`).

### Running

```sh
./cub3D maps/valid.cub
```

The program takes exactly one argument: the path to a `.cub` scene file.

**Controls:**
| Key            | Action                    |
|----------------|---------------------------|
| `W` / `A` / `S` / `D` | Move forward/left/back/right |
| `←` / `→`      | Look/turn left or right   |
| `Esc`          | Quit                      |
| Window close (✕) | Quit                    |

### Scene file format (`.cub`)

```
NO ./textures/no.xpm
SO ./textures/so.xpm
WE ./textures/we.xpm
EA ./textures/ea.xpm

F 220,100,0
C 80,150,220

111111111111111
100000000000001
101110111011101
100010001000101
111010101011101
100000101000001
101111101110111
1000000N0000001
111111111111111
```

- `NO`/`SO`/`WE`/`EA`: paths to the North/South/West/East wall textures
  (`.xpm` files).
- `F` / `C`: floor and ceiling colors as `R,G,B` (each `0-255`).
- The map is always the last element in the file, uses `0` (empty),
  `1` (wall) and one of `N`/`S`/`E`/`W` (player start position and
  facing direction), and must be entirely enclosed by walls.

Any malformed scene file causes the program to print `Error\n` followed
by an explanatory message and exit with a non-zero status.

## Resources

- [Lode's Computer Graphics Tutorial – Raycasting](https://lodev.org/cgtutor/raycasting.html) —
  the classic reference for the DDA ray-casting algorithm used here.
- [42's miniLibX documentation / sources](https://github.com/42Paris/minilibx-linux)
- [Wolfenstein 3D on Wikipedia](https://en.wikipedia.org/wiki/Wolfenstein_3D) —
  historical context for the project.
- Many different youtube videos