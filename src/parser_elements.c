/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaplanc <flaplanc@students.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 18:03:33 by flaplanc          #+#    #+#             */
/*   Updated: 2026/08/04 18:03:33 by flaplanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	parse_identifier(char *line)
{
	if (!ft_strncmp(line, "NO", 2) && is_space(line[2]))
		return (TEX_NO);
	if (!ft_strncmp(line, "SO", 2) && is_space(line[2]))
		return (TEX_SO);
	if (!ft_strncmp(line, "WE", 2) && is_space(line[2]))
		return (TEX_WE);
	if (!ft_strncmp(line, "EA", 2) && is_space(line[2]))
		return (TEX_EA);
	if (line[0] == 'F' && is_space(line[1]))
		return (4);
	if (line[0] == 'C' && is_space(line[1]))
		return (5);
	return (-1);
}

static int	check_texture_path(char *path)
{
	char	*base;
	int		fd;
	int		len;

	base = ft_strrchr(path, '/');
	if (base)
		base++;
	else
		base = path;
	len = ft_strlen(base);
	if (len < 5 || ft_strncmp(base + len - 4, ".xpm", 4) != 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

void	store_texture(t_scene *scene, int side, char *line)
{
	int	i;

	i = 2;
	while (is_space(line[i]))
		i++;
	if (line[i] == '\0')
		parse_error_free("Error\nMissing texture path\n", scene);
	if (scene->has_tex[side])
		parse_error_free("Error\nDuplicate texture identifier\n", scene);
	scene->tex_path[side] = ft_strdup(line + i);
	if (!scene->tex_path[side])
		parse_error_free("Error\nMemory allocation failed\n", scene);
	scene->has_tex[side] = 1;
	trim_end(scene->tex_path[side]);
	if (!check_texture_path(scene->tex_path[side]))
		parse_error_free("Error\nInvalid or unreadable texture file\n", scene);
}

void	store_color(t_scene *scene, int is_floor, char *line)
{
	int	i;
	int	color;

	i = 1;
	while (is_space(line[i]))
		i++;
	if (line[i] == '\0')
		parse_error_free("Error\nMissing color value\n", scene);
	if ((is_floor && scene->has_floor) || (!is_floor && scene->has_ceil))
		parse_error_free("Error\nDuplicate color identifier\n", scene);
	color = parse_color(line + i);
	if (color < 0)
		parse_error_free("Error\nInvalid color format, expected R,G,B\n",
			scene);
	if (is_floor)
	{
		scene->floor_color = color;
		scene->has_floor = 1;
	}
	else
	{
		scene->ceil_color = color;
		scene->has_ceil = 1;
	}
}
