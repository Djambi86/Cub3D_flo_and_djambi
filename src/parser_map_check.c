/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:42:07 by dabdulka          #+#    #+#             */
/*   Updated: 2026/08/04 14:26:55 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	check_spawn(t_scene *scene, int x, int y, int *found)
{
	t_map	*map;
	char	c;

	map = &scene->map;
	c = map->grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*found)
			parse_error_free("Error\nMultiple player start positions\n",
				scene);
		map->player_x = x + 0.5;
		map->player_y = y + 0.5;
		map->player_dir = c;
		*found = 1;
	}
}

void	find_player(t_scene *scene)
{
	int	y;
	int	x;
	int	found;

	found = 0;
	y = 0;
	while (scene->map.grid[y])
	{
		x = 0;
		while (scene->map.grid[y][x])
		{
			check_spawn(scene, x, y, &found);
			x++;
		}
		y++;
	}
	if (!found)
		parse_error_free("Error\nNo player start position found\n", scene);
}

static int	cell_open(char c)
{
	return (c != '1' && c != ' ');
}

static int	neighbor_leaks(t_map *map, int x, int y)
{
	if (x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1)
		return (1);
	if (map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
		return (1);
	if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' ')
		return (1);
	return (0);
}

void	check_map_closed(t_scene *scene)
{
	t_map	*map;
	int		x;
	int		y;

	map = &scene->map;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (cell_open(map->grid[y][x]) && neighbor_leaks(map, x, y))
				parse_error_free("Error\nMap is not closed\n", scene);
			x++;
		}
		y++;
	}
}
