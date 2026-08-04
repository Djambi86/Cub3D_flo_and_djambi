/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaplanc <flaplanc@students.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 18:03:54 by flaplanc          #+#    #+#             */
/*   Updated: 2026/08/04 18:03:54 by flaplanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	map_line_count(char **lines, int start, t_scene *scene)
{
	int	count;
	int	i;

	count = 0;
	i = start;
	while (lines[i])
	{
		if (!is_blank(lines[i]))
			count = i - start + 1;
		i++;
	}
	if (count == 0)
		parse_error_free("Error\nEmpty map\n", scene);
	i = start;
	while (i < start + count)
	{
		if (is_blank(lines[i]))
			parse_error_free("Error\nEmpty line inside the map\n", scene);
		i++;
	}
	return (count);
}

void	collect_map(char **lines, int start, t_scene *scene)
{
	int	count;
	int	i;

	count = map_line_count(lines, start, scene);
	scene->map.grid = ft_calloc(count + 1, sizeof(char *));
	if (!scene->map.grid)
		parse_error_free("Error\nMemory allocation failed\n", scene);
	scene->map.height = count;
	i = 0;
	while (i < count)
	{
		scene->map.grid[i] = ft_strdup(lines[start + i]);
		if (!scene->map.grid[i])
			parse_error_free("Error\nMemory allocation failed\n", scene);
		i++;
	}
}

static char	*pad_row(char *row, int width, t_scene *scene)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(row);
	res = malloc(width + 1);
	if (!res)
		parse_error_free("Error\nMemory allocation failed\n", scene);
	i = 0;
	while (i < len)
	{
		res[i] = row[i];
		i++;
	}
	while (i < width)
		res[i++] = ' ';
	res[width] = '\0';
	return (res);
}

void	check_map_chars(t_scene *scene)
{
	t_map	*map;
	int		y;
	int		x;

	map = &scene->map;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (!is_map_char(map->grid[y][x]))
				parse_error_free("Error\nInvalid character in map\n", scene);
			x++;
		}
		y++;
	}
}

void	pad_map(t_scene *scene)
{
	t_map	*map;
	int		i;
	int		len;
	int		max;
	char	*padded;

	map = &scene->map;
	max = 0;
	i = 0;
	while (map->grid[i])
	{
		len = ft_strlen(map->grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	map->width = max;
	i = 0;
	while (map->grid[i])
	{
		padded = pad_row(map->grid[i], max, scene);
		free(map->grid[i]);
		map->grid[i] = padded;
		i++;
	}
}
