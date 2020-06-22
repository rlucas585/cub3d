# cub3d

This project was completed as part of the curriculum at Codam - it is a
raycasting program, that can serve as a basis for a simplistic 80s style
FPS.

## Installation

This project was developed on Mac with Darwin 18.7.0. Two libraries exist to
streamline the use of X11:

- minilibx: For systems without Swift.
- minilibx\_mms\_20191207\_beta: For systems with Swift installed.

To compile the project on a system with Swift:

```
make
```

To compile on a system without Swift:

```
make noswift
```

For this project, I also implemented threading to increase the rendering speed,
as an extension to the base project. To compile the project with threading
enabled:

```
make bonus
```

## Run Program

To run the program, the executable must be run and a valid map supplied as
an argument. Maps are contained in the maps/ directory.

```
./cub3d maps/map8.cub
```

Several maps are invalid to show error handling of the program. These maps
are located in the maps/invalid/ directory.


#### Remove Object files/Executable

To remove all object files:

```
make clean
```

To remove object files, libraries and the executable:

```
make fclean
```

To remove and recompile the project:

```
make re
```
