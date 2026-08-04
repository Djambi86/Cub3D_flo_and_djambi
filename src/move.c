/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:42:36 by dabdulka          #+#    #+#             */
/*   Updated: 2026/08/04 14:26:55 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	is_wall(t_map *map, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (mx < 0 || mx >= map->width || my < 0 || my >= map->height)
		return (1);
	return (map->grid[my][mx] == '1' || map->grid[my][mx] == ' ');
}

int	can_move(t_data *data, double new_x, double new_y)
{
	t_map	*map;

	map = &data->scene.map;
	if (is_wall(map, new_x - WALL_MARGIN, new_y - WALL_MARGIN))
		return (0);
	if (is_wall(map, new_x + WALL_MARGIN, new_y - WALL_MARGIN))
		return (0);
	if (is_wall(map, new_x - WALL_MARGIN, new_y + WALL_MARGIN))
		return (0);
	if (is_wall(map, new_x + WALL_MARGIN, new_y + WALL_MARGIN))
		return (0);
	return (1);
}

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = old_dir_x * cos(angle)
		- data->player.dir_y * sin(angle);
	data->player.dir_y = old_dir_x * sin(angle)
		+ data->player.dir_y * cos(angle);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = old_plane_x * cos(angle)
		- data->player.plane_y * sin(angle);
	data->player.plane_y = old_plane_x * sin(angle)
		+ data->player.plane_y * cos(angle);
}

static void	compute_target(t_data *data, double *nx, double *ny)
{
	t_player	*p;

	p = &data->player;
	*nx = p->x;
	*ny = p->y;
	if (data->keys.w)
	{
		*nx += p->dir_x * MOVE_SPEED;
		*ny += p->dir_y * MOVE_SPEED;
	}
	if (data->keys.s)
	{
		*nx -= p->dir_x * MOVE_SPEED;
		*ny -= p->dir_y * MOVE_SPEED;
	}
	if (data->keys.d)
	{
		*nx += p->plane_x * MOVE_SPEED;
		*ny += p->plane_y * MOVE_SPEED;
	}
	if (data->keys.a)
	{
		*nx -= p->plane_x * MOVE_SPEED;
		*ny -= p->plane_y * MOVE_SPEED;
	}
}

void	handle_movement(t_data *data)
{
	double	nx;
	double	ny;

	compute_target(data, &nx, &ny);
	if (can_move(data, nx, data->player.y))
		data->player.x = nx;
	if (can_move(data, data->player.x, ny))
		data->player.y = ny;
	if (data->keys.left)
		rotate_player(data, -ROT_SPEED);
	if (data->keys.right)
		rotate_player(data, ROT_SPEED);
}
