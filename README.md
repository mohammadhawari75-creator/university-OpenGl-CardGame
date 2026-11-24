# Card Game - Homework 2026

Built on the Lecture 4 project (L2 - L4 only). Same structure as Lecture 4: one main file, and every class
is written in its own .cpp file that is included in the main file (like `#include "PolygonWithTexture.cpp"`).

## Keys
- `1` camera from the top, cards lie on the table
- `2` player camera, cards stand up
- `G` a random card goes from the deck to the play zone (nothing happens after the 5 cards)
- `ESC` quit

## Files
```
GLProject/
  CardGameMain.cpp        main, camera states, keys, G logic, texture loading
  PolygonWithTexture.cpp  from Lecture 4 (only an include guard added at the top and bottom)
  CubeWithTexture.cpp     a box made of 6 PolygonWithTexture faces
  Card.cpp                one card + its animations
  Room.cpp                floor, ceiling, walls
  Table.cpp               table + 3 zones
  Clock.cpp               decor 1 (grandfather clock, static)
  Bookshelf.cpp           decor 2
  Chest.cpp               decor 3
  Poster.cpp              split poster with a missing corner
  shaders/                L4.vs and L4.fs from Lecture 4 (texture * color, no lighting)
  textures/
```

## Notes
- Include guards (`#ifndef ... #define ... #endif`) in every class file: several classes include
  `PolygonWithTexture.cpp` and the main file includes all of them, so without the guard a class would be defined twice.
- Card animation: `position = start + (target - start) * t`, plus `sin(t * pi) * 0.4` on y so it goes up and down.
  Standing up = rotate around the bottom edge: translate to the edge, rotate, translate back.
- Camera states use the `Camera` class from Lecture 4 (set Position, Yaw, Pitch).
- `loadTexture()` is the texture code from Lecture 4's Main.cpp, put in a function because we load 15 images.
- Poster: 2 pieces drawn with `GL_TRIANGLE_FAN` starting from the middle of each piece. Texture coordinates come
  from the position on the full poster, so the picture continues across the tear. The right piece is rotated a
  little around its tape.
- Texture coordinates bigger than 1 on the floor / walls make the texture repeat (`GL_REPEAT`).
