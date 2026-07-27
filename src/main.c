/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:42:44 by dabdulka          #+#    #+#             */
/*   Updated: 2026/07/27 01:42:46 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_extension(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len < 5 || ft_strncmp(arg + len - 4, ".cub", 4) != 0)
		parse_error("Error\nArgument must be a .cub file\n");
}

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, EVENT_KEYDOWN, MASK_KEYDOWN, key_press, data);
	mlx_hook(data->win, EVENT_KEYUP, MASK_KEYUP, key_release, data);
	mlx_hook(data->win, EVENT_DESTROY, MASK_DESTROY, close_window, data);
	mlx_loop_hook(data->mlx, game_loop, data);
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	t_data	data;

	if (argc != 2)
		parse_error("Error\nUsage: ./cub3D <map.cub>\n");
	check_extension(argv[1]);
	parse_scene(argv[1], &scene);
	init_data(&data, &scene);
	init_window(&data);
	load_textures(&data);
	init_player(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	return (EXIT_SUCCESS);
}
