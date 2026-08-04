/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:41:39 by dabdulka          #+#    #+#             */
/*   Updated: 2026/08/04 14:26:55 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	parse_elements(char **lines, t_scene *scene)
{
	int	i;
	int	id;

	i = 0;
	while (lines[i])
	{
		if (is_blank(lines[i]))
		{
			i++;
			continue ;
		}
		id = parse_identifier(lines[i]);
		if (id < 0)
			return (i);
		if (id <= TEX_EA)
			store_texture(scene, id, lines[i]);
		else if (id == 4)
			store_color(scene, 1, lines[i]);
		else
			store_color(scene, 0, lines[i]);
		i++;
	}
	return (-1);
}

static void	check_completeness(t_scene *scene)
{
	if (!scene->has_tex[TEX_NO] || !scene->has_tex[TEX_SO]
		|| !scene->has_tex[TEX_WE] || !scene->has_tex[TEX_EA])
		parse_error_free("Error\nMissing a wall texture identifier\n", scene);
	if (!scene->has_floor || !scene->has_ceil)
		parse_error_free("Error\nMissing floor or ceiling color\n", scene);
	if (scene->map.height == 0)
		parse_error_free("Error\nNo map found in scene file\n", scene);
}

void	parse_scene(const char *path, t_scene *scene)
{
	char	*content;
	char	**lines;
	int		map_start;

	ft_bzero(scene, sizeof(t_scene));
	content = read_file(path);
	if (!content)
		parse_error("Error\nCould not read scene file\n");
	lines = split_lines(content);
	free(content);
	if (!lines)
		parse_error("Error\nMemory allocation failed\n");
	scene->lines = lines;
	map_start = parse_elements(lines, scene);
	if (map_start < 0)
		parse_error_free("Error\nNo map found in scene file\n", scene);
	collect_map(lines, map_start, scene);
	free_split(lines);
	scene->lines = NULL;
	pad_map(scene);
	check_map_chars(scene);
	find_player(scene);
	check_map_closed(scene);
	check_completeness(scene);
}
