/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:40:59 by dabdulka          #+#    #+#             */
/*   Updated: 2026/07/27 01:41:03 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

static int	get_tex_x(t_col *c)
{
	int	tex_x;

	tex_x = (int)(get_wall_x(c->data, c->ray)
			* c->data->tex[c->tex_idx].width);
	if ((c->ray->side == 0 && c->ray->dir_x < 0)
		|| (c->ray->side == 1 && c->ray->dir_y > 0))
		tex_x = c->data->tex[c->tex_idx].width - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_slice(t_col *c, int start, int end, int line_h)
{
	int		y;
	int		tex_x;
	double	tex_pos;
	double	tex_step;

	tex_x = get_tex_x(c);
	tex_step = (double)c->data->tex[c->tex_idx].height / line_h;
	y = start;
	tex_pos = 0;
	if (y < 0)
	{
		tex_pos = -y * tex_step;
		y = 0;
	}
	while (y < end && y < WIN_HEIGHT)
	{
		put_pixel(&c->data->screen, c->x, y,
			get_tex_color(&c->data->tex[c->tex_idx], tex_x, (int)tex_pos));
		tex_pos += tex_step;
		y++;
	}
}

void	draw_column(t_data *data, int x, t_ray *ray)
{
	t_col	c;
	int		line_h;
	int		start;
	int		end;

	c.data = data;
	c.ray = ray;
	c.x = x;
	c.tex_idx = select_texture(ray);
	line_h = (int)(WIN_HEIGHT / ray->perp_dist);
	if (line_h < 1)
		line_h = 1;
	start = WIN_HEIGHT / 2 - line_h / 2;
	end = WIN_HEIGHT / 2 + line_h / 2;
	draw_ceiling(&c, start);
	draw_wall_slice(&c, start, end, line_h);
	draw_floor(&c, end);
}

void	render_frame(t_data *data)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(data, &ray, x);
		perform_dda(data, &ray);
		draw_column(data, x, &ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->screen.img, 0, 0);
}
