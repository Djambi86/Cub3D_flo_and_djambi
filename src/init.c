/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:42:50 by dabdulka          #+#    #+#             */
/*   Updated: 2026/08/04 14:26:55 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	init_data(t_data *data, t_scene *scene)
{
	ft_bzero(data, sizeof(t_data));
	data->scene = *scene;
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		parse_error_free("Error\nFailed to initialize MLX\n", &data->scene);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->win)
		runtime_error(data, "Error\nFailed to create window\n");
	data->screen.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->screen.img)
		runtime_error(data, "Error\nFailed to create screen image\n");
	data->screen.addr = mlx_get_data_addr(data->screen.img,
			&data->screen.bpp, &data->screen.line_len, &data->screen.endian);
}
