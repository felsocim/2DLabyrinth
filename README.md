# 2DLabyrinth

Vintage labyrinth game for Linux

## About

This game was developed within our Development techniques courses at the University of Strasbourg. The goal is simple. Manage to get out of the labyrinth before getting destroyed by the monster. Life potions and armors can help to defeat the monster and win the game.

2DLabyrinth has two versions. A full-featured 2D graphical version and a pure textual version playable in a terminal window.

## Build sources

Before compiling the sources (using GCC, Clang or a compatible C compiler), ensure that SDL and Cairo libraries are installed on your system if you intend to build the graphical version of the game.

The libraries can be installed by executing the following command (Debian-based Linux distributions only):

```sudo apt install libsdl* libcairo*```

When the installation finishes, just fire the `make` command from the project's root directory.

If you prefer to compile only one of the two versions, specify the build target as argument to the `make` command as follows:

- `make 2DLabCLI` for the textual version
- `make 2DLabGUI` for the graphical version

## Run

The compilation produces two executable files in the project's root directory:

1. **2DLabCLI** representing the textual version which can be run from a terminal
2. **2DLabGUI** representing the graphical version which can be run by double clicking on the binary file

## Controls

To move in the labyrinth, use the following keys:

- textual version: **Z** (up), **S** (down), **Q** (left) and **D** (right)
- graphical version: just use arrow keys

Note that in the textual version, the gamer's position is denoted by the letter **J** (from the French translation *joueur*) and the monster's position is denoted by the letter **M**. **#** represents wall, **S** a sword, **C** a schield, **-** a trap (costs 1 life), **+** a life potion (gives 1 life) and **O** the exit from the labyrinth.

## Screenshots

### Graphical version

![Screenshot of the graphical version](guiscreen.png)

### Textual version

![Screenshot of the textual version](cliscreen.png)

## Creating custom labyrinths

The game constructs the labyrinth based on the contents of the file named **grille.txt** located in the data directory in project's root. Its format is simple.

The two numbers in the first line indicate the size of the labyrinth (`width height`). Then, in the second line is stored initial position of the gamer (`x-axis y-axis`).

Finally, numbers in the other lines describe every single square of the labyrinth. Each number means a different type of square. See their description in the following table:

| Type code | Type description      |
| --------- | --------------------- |
| 0         | Empty square          |
| 1         | Wall                  |
| 2         | Trap (-1 life)        |
| 3         | Life potion (+1 life) |
| 6         | Shield                |
| 7         | Sword                 |
| 8         | Exit suqare           |

In order to use a custom labyrinth, backup the original file and then replace it with yours (keeping the same name and location).

## Documentation

To generate Doxygen-like documentation for the sources, fire the following command:

```doxygen Doxyfile```

Produced HTML documentation will be stored in **doc** folder in the project's root.

## Authors

[Marek Felsoci](mailto:marek.felsoci@etu.unistra.fr) and Thomas Millot, students at the [University of Strasbourg](http://www.unistra.fr).

## License

Our work is licensed under the terms of the GNU General Public Licence vserion 2. See the [LICENSE](LICENSE) file for the full license text.
