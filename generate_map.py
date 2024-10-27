#!/usr/bin/python3

import argparse
import random
import sys
from collections import deque

def generate_map(width, height, surrounded, has_player, has_exit, path_required, wall_density, coin_density):
	# Initialize the map with empty spaces
	map_data = [['0' for _ in range(width)] for _ in range(height)]
	
	# Surround map with walls if the "surrounded" rule is True
	if surrounded:
		for i in range(height):
			map_data[i][0] = '#'
			map_data[i][width - 1] = '#'
		for j in range(width):
			map_data[0][j] = '#'
			map_data[height - 1][j] = '#'
	
	# Place player and exit randomly
	player_pos = place_object(map_data, 'P') if has_player else None
	exit_pos = place_object(map_data, 'E') if has_exit else None

	# Add random internal walls
	add_random_walls(map_data, wall_density, avoid=[player_pos, exit_pos])

	# Add random coins based on density
	add_random_coins(map_data, coin_density, avoid=[player_pos, exit_pos])

	# Ensure there is a path from player to all coins and the exit if required
	if path_required and not validate_path(map_data, player_pos, find_positions(map_data, 'C') + [exit_pos]):
		return None
	
	return map_data

def place_object(map_data, obj):
	while True:
		x, y = random.randint(1, len(map_data) - 2), random.randint(1, len(map_data[0]) - 2)
		if map_data[x][y] == '0':
			map_data[x][y] = obj
			return (x, y)

def add_random_walls(map_data, wall_density, avoid):
	height = len(map_data)
	width = len(map_data[0])
	for i in range(1, height - 1):
		for j in range(1, width - 1):
			if random.random() < wall_density and map_data[i][j] == '0' and (i, j) not in avoid:
				map_data[i][j] = '#'

def add_random_coins(map_data, coin_density, avoid):
	height = len(map_data)
	width = len(map_data[0])
	for i in range(1, height - 1):
		for j in range(1, width - 1):
			if random.random() < coin_density and map_data[i][j] == '0' and (i, j) not in avoid:
				map_data[i][j] = 'C'

def find_positions(map_data, obj):
	return [(i, j) for i in range(len(map_data)) for j in range(len(map_data[0])) if map_data[i][j] == obj]

def validate_path(map_data, start, targets):
	visited = set()
	queue = deque([start])
	
	while queue:
		x, y = queue.popleft()
		if (x, y) in visited:
			continue
		visited.add((x, y))
		if (x, y) in targets:
			targets.remove((x, y))
			if not targets:
				return True
		for dx, dy in [(-1,0), (1,0), (0,-1), (0,1)]:
			nx, ny = x + dx, y + dy
			if map_data[nx][ny] in ('0', 'C', 'E') and (nx, ny) not in visited:
				queue.append((nx, ny))
				
	return not targets

def print_map(map_data):
	for row in map_data:
		print("".join(row))

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="Generate a game map.")
	parser.add_argument("--width", type=int, help="Map width")
	parser.add_argument("--height", type=int, help="Map height")
	parser.add_argument("--surrounded", type=bool, default=True, help="Map surrounded by walls")
	parser.add_argument("--has_player", type=bool, default=True, help="Map contains exactly one player")
	parser.add_argument("--has_exit", type=bool, default=True, help="Map contains exactly one exit")
	parser.add_argument("--path_required", type=bool, default=True, help="Path required from player to all coins and the exit")
	parser.add_argument("--wall_density", type=float, default=0.1, help="Density of random internal walls (0.0 - 1.0)")
	parser.add_argument("--coin_density", type=float, default=0.1, help="Density of coins (0.0 - 1.0)")
	
	args = parser.parse_args()

	# Set random width and height if not specified
	width = args.width if args.width else random.randint(5, 15)
	height = args.height if args.height else random.randint(5, 15)

	# Generate and print map
	i = 0
	map_data = generate_map(width, height, args.surrounded, args.has_player, args.has_exit, args.path_required, args.wall_density, args.coin_density)
	while map_data is None:
		map_data = generate_map(width, height, args.surrounded, args.has_player, args.has_exit, args.path_required, args.wall_density, args.coin_density)
		i += 1
		if i == 1000:
			print("Failed to generate a valid map.")
			sys.exit(1)
	print_map(map_data)
