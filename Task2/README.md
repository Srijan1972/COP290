# COP290 Task 2 - A 2 player game based in the IIT Delhi Campus

This game will run only on a Linux machine (Tested only on Ubuntu)

## Dependencies

- make- Installed using `sudo apt install make`
- SDL2- Installed using `sudo apt install libsdl2-dev`
- SDL2-image- Installed using `sudo apt install libsdl2-image-dev`

## Running Instructions

- The command `make` compiles all the files into an executable `duel`.
- The command `./duel` runs the game.

```bash
make
./duel
```

The command `make clean` deletes the executable and then `make` can be run again to recompile the game.

## Playing Instructions

- Characters are moved using arrow keys.
- When in range, characters can attack each other using the spacebar.
- When in range of the heart, some health will regenerate if the h key is pressed.
- On game ending a msg is displayed telling the player if they won.

## Acknowledgements

- Disney for providing the Duel of the Fates audio.
- https://deepnight.net/tool/rpg-map/ to make the map.
- https://forums.rpgmakerweb.com/index.php?threads%2Fmodern-citizen-sprites.117685%2F for the character sprites.
- https://www.freepik.com/free-photo/3d-abstract-background-with-futuristic-particles_8419977.htm#page=2&query=game%20background&position=49&from_view=keyword for the backgrounds of the start and end screen.
- https://opengameart.org/content/heart-pixel-art for the heart icon
