
# so_long

## Description
`so_long` is a simple 2D game developed in C using the MLX42 library provided by Codam College. The objective of the game is to navigate through a maze, collect all the collectibles, and reach the exit.

## Features
- 2D graphics using MiniLibX
- Keyboard controls for movement
- Collectibles and exit points
- Basic animation engine
- Dijkstra pathfinding
- Viewport rendering

## Installation
1. Clone the repository:
	```sh
	git clone https://github.com/H-R-B-Y/So_Long.git so_long
	```
2. Navigate to the project directory:
	```sh
	cd so_long
	```
3. Clone MLX42 dependency
	```sh
	cd lib
	git clone https://github.com/codam-coding-college/MLX42
	cd ..
	```
4. Compile the project:
	```sh
	make
	```

## Usage
Run the game with the following command:
```sh
./so_long.out {map file}
```

## Controls
- `W` - Move up
- `A` - Move left
- `S` - Move down
- `D` - Move right
- `ESC` - Pause Menu / Exit upon winning
- `Arrow key` - Navigate pause menu
- `Enter` - Select for pause menu

## Other
If you want to see funny pathfinding algo go brrr use run compile with this:
```sh
make re DEBUG="debug" PRINT_DELAY="1000"
```
Then you can run `./so_long.out {map file}` and it will do the funny path finding thing :P

## License
Idk whatever MLX42 uses


