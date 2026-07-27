/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:41:09 by dabdulka          #+#    #+#             */
/*   Updated: 2026/07/27 01:41:11 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_ceiling(t_col *c, int start)
{
	int	y;

	y = 0;
	if (start > WIN_HEIGHT)
		start = WIN_HEIGHT;
	while (y < start)
	{
		put_pixel(&c->data->screen, c->x, y, c->data->scene.ceil_color);
		y++;
	}
}

void	draw_floor(t_col *c, int end)
{
	int	y;

	y = end;
	if (y < 0)
		y = 0;
	while (y < WIN_HEIGHT)
	{
		put_pixel(&c->data->screen, c->x, y, c->data->scene.floor_color);
		y++;
	}
}
