# cub3D

A 3D raycasting engine inspired by the classic 90s first-person game *Wolfenstein 3D*, developed in C as part of the **42 School** curriculum.

The project explores fundamental computer graphics techniques, window and event management using **MiniLibX**, geometric algorithms, and real-time rendering.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Controls](#controls)
- [Map Configuration (`.cub`)](#map-configuration-cub)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Running the Program](#running-the-program)
- [Technical Highlights](#technical-highlights)

---

## Overview

cub3D renders a dynamic first-person perspective inside a grid-based maze using raycasting principles. By casting rays from the player's viewpoint onto a 2D map and calculating intersections using the Digital Differential Analysis (DDA) algorithm, the engine projects textured vertical wall slices onto the screen in real-time.

---

## Features

- **Raycasting Engine**:
  - DDA (Digital Differential Analysis) grid traversal algorithm.
  - Perpendicular wall distance calculation to eliminate fisheye distortion.
  - Texture mapping based on wall orientation (North, South, East, West).
  - Configurable floor and ceiling RGB colors.

- **Movement & Physics**:
  - Smooth multidirectional movement (forward, backward, strafe left, strafe right).
  - Smooth camera rotation via keyboard arrows or mouse movement.
  - Wall collision detection with player hitbox sliding.

- **Interactive Elements & Bonus Features**:
  - **Minimap**: Overhead radar map displaying walls, player position, and viewing direction.
  - **Doors**: Interactive doors that can be opened and closed dynamically.
  - **Animated Sprites**: In-game animated entities rendered with depth ordering.
  - **Mouse Look**: Natural first-person camera rotation tracked through mouse cursor deltas.

- **Robust Parsing & Error Handling**:
  - Complete `.cub` scene description file verification.
  - Validation ensuring maps are fully enclosed by walls (using flood fill checks).
  - Explicit error messages on invalid maps, corrupt textures, or missing parameters.

---

## Controls

| Key / Input | Action |
| :--- | :--- |
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` / `→` | Rotate camera left / right |
| `Mouse` | Look around (horizontal rotation) |
| `E` | Open / Close doors |
| `ESC` / `[X]` | Exit cleanly |

---

## Map Configuration (`.cub`)

The program takes a single configuration file ending with the `.cub` extension:

```cub
NO ./textures/Walls.xpm
SO ./textures/Walls.xpm
WE ./textures/Walls.xpm
EA ./textures/Walls.xpm
DO ./textures/door.xpm

F 50,50,50
C 135,206,235

    111111111111111111111111
    1100000000110000000A0001
    101100000111000000W00101
    100100A000000000000000A1
111111111D1100000111A0000001 
100A0000001100000110101D11111
1111011111111101110000001001
11110111111011D01110101001001
1100000011010101110000001001
100000A000000000110A0000D001
1000000000000000110101001001
1100000111010111111011110001
11111111 111011 101111010001
11111111 111111 111111111111
```

### Identifier Guide

- `NO`, `SO`, `WE`, `EA`: Paths to North, South, West, and East wall `.xpm` texture files.
- `DO`: Path to the door `.xpm` texture file.
- `F [R,G,B]`: Floor color in 0–255 RGB format.
- `C [R,G,B]`: Ceiling color in 0–255 RGB format.
- Map characters:
  - `0`: Empty walkable space
  - `1`: Solid wall
  - `N`, `S`, `E`, `W`: Player starting position and orientation
  - `D`: Interactive door
  - `A`: Animated sprite entity

---

## Getting Started

### Prerequisites

This project is built for Linux environments and requires the following packages:

- `gcc` or `clang`
- `make`
- `X11` development libraries (`libx11-dev`, `libxext-dev`, `libbsd-dev`)
- `math` library (`-lm`)
- `MiniLibX` (included or linked from `minilibix-linux`)

On Debian / Ubuntu:
```bash
sudo apt-get update
sudo apt-get install build-essential libx11-dev libxext-dev libbsd-dev
```

### Compilation

Clone the repository and run:

```bash
make
```

Available build targets:
- `make` / `make all`: Compiles the binary `cub3D`.
- `make clean`: Removes object files.
- `make fclean`: Removes object files and the `cub3D` executable.
- `make re`: Recompiles the entire project.

### Running the Program

Run the executable passing a `.cub` scene file as argument:

```bash
./cub3D map.cub
```

---

## Technical Highlights

- **Raycasting Mechanics**: For each vertical column of the window, a ray is projected through the camera plane. The DDA step incrementally checks map grid cells until a wall or boundary is encountered.
- **Perspective Correction**: Raw Euclidean distance causes a "fish-eye" curving effect on straight walls. Projecting along the camera's normal vector preserves flat, straight walls.
- **Double Buffering**: Each frame is rendered onto an off-screen image buffer in memory before being drawn to the window via `mlx_put_image_to_window`, guaranteeing flicker-free rendering.
