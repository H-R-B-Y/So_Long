
## Pre-Game

Before the game starts things need to be processed.
The map has strict rules:
	- There Must be 1 Exit and 1 Player starting position.		(Text Parsing)
	- There Must be at least 1 collectible.						(Text Parsing)
	- Must be a rectangle.										(Text Parsing)
	- Must be surrounded by walls.								(Text Parsing)
	- MUST be a path to all collectibles and the exit			(A*)
	- Parser must work for all maps that follow these rules.	

If any misconfiguration of any kind is encountered in the file, the program must
exit in a clean way, and return "Error\n" followed by an explicit error message of
your choice.

Key concepts above are path finding, text parsing.

Ideas:
	- While parsing the map check that all textual rules apply (walls / count of unique objects)
	- Once map is parsed we can use A* or Backtracking of some sort to find a possible path.
	- A count of collectibles will need to be retained for win condition.
	- Cleanup will need to be retained for win condition.

## Game

The Player has to collect all collectibles from the map and
leave through the exit with the least number of steps.

The number of moves needs to be printed to the console.

Obviously the player cannot go through walls, and collectibles need to be "collected" (not preserved once collected.)

Has to be a 2D view.

Player can move in 4 directions (Up, Down, Left, Right) with WASD or with ZQSD.

Ideas:
	- The map graphics and player graphics always needs to be drawn (this can be handled in once loop)
	- A seperate list of images can be used to store the collectibles as they will not always need to be drawn.
		Perhaps a linked list that collapses when collected.
	- A key-press event handler to handle the key presses.
	- The parsed map from step 1 can be retained to keep check for Walls/Collectibles/Exit during movement.

## Post Game

Each Section will need to keep track of what it has created.

Linked lists are probably best here, use them to keep track of what needs to be deleted when the game exits.

The game's win condition is to collect all the objects and get to the exit, this is a win.

## Bonus

- Patrolling enemies (death conditions)
- Sprite Animation.
- Movement Count displayed in game (instead of shell) (MANDATORY IMO)
- (Self-Insert) Scoreboard Displayed on exit condition.

