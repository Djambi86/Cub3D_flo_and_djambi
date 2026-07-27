/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:42:58 by dabdulka          #+#    #+#             */
/*   Updated: 2026/07/27 01:43:00 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_dir_ns(t_player *p, char dir)
{
	if (dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
}

static void	set_dir_ew(t_player *p, char dir)
{
	if (dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

static void	set_direction(t_player *p, char dir)
{
	if (dir == 'N' || dir == 'S')
		set_dir_ns(p, dir);
	else
		set_dir_ew(p, dir);
}

void	init_player(t_data *data)
{
	data->player.x = data->scene.map.player_x;
	data->player.y = data->scene.map.player_y;
	set_direction(&data->player, data->scene.map.player_dir);
}
