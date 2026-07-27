/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:42:07 by dabdulka          #+#    #+#             */
/*   Updated: 2026/07/27 01:42:09 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static int	visit_neighbor(t_flood *f, int x, int y)
{
	if (y < 0 || y >= f->map->height || x < 0 || x >= f->map->width)
		return (1);
	if (f->map->grid[y][x] == ' ')
		return (1);
	if (f->map->grid[y][x] == '1')
		return (0);
	if (f->visited[y * f->map->width + x])
		return (0);
	f->visited[y * f->map->width + x] = 1;
	f->stack[(*f->top)++] = x;
	f->stack[(*f->top)++] = y;
	return (0);
}

static int	flood_fill(t_flood *f)
{
	int	x;
	int	y;

	while (*f->top > 0)
	{
		y = f->stack[--(*f->top)];
		x = f->stack[--(*f->top)];
		if (visit_neighbor(f, x - 1, y) || visit_neighbor(f, x + 1, y)
			|| visit_neighbor(f, x, y - 1) || visit_neighbor(f, x, y + 1))
			return (1);
	}
	return (0);
}

void	check_map_closed(t_scene *scene)
{
	t_flood	f;
	int		size;
	int		top;
	int		failed;

	f.map = &scene->map;
	size = f.map->width * f.map->height;
	f.visited = ft_calloc(size, sizeof(int));
	f.stack = malloc(sizeof(int) * size * 2);
	if (!f.visited || !f.stack)
	{
		free(f.visited);
		free(f.stack);
		parse_error_free("Error\nMemory allocation failed\n", scene);
	}
	top = 2;
	f.top = &top;
	f.stack[0] = (int)f.map->player_x;
	f.stack[1] = (int)f.map->player_y;
	f.visited[f.stack[1] * f.map->width + f.stack[0]] = 1;
	failed = flood_fill(&f);
	free(f.visited);
	free(f.stack);
	if (failed)
		parse_error_free("Error\nMap is not closed\n", scene);
}
