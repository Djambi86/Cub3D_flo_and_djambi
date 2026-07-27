/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:38:43 by dabdulka          #+#    #+#             */
/*   Updated: 2026/07/27 01:38:46 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	load_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->tex[i].img = mlx_xpm_file_to_image(data->mlx,
				data->scene.tex_path[i],
				&data->tex[i].width, &data->tex[i].height);
		if (!data->tex[i].img)
			runtime_error(data, "Error\nFailed to load a wall texture\n");
		data->tex[i].addr = mlx_get_data_addr(data->tex[i].img,
				&data->tex[i].bpp, &data->tex[i].line_len,
				&data->tex[i].endian);
		i++;
	}
}

int	get_tex_color(t_img *tex, int x, int y)
{
	char	*pixel;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}
