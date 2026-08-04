/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:43:03 by dabdulka          #+#    #+#             */
/*   Updated: 2026/08/04 14:26:55 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		clean_exit(data, EXIT_SUCCESS);
	if (keycode == KEY_W)
		data->keys.w = 1;
	if (keycode == KEY_A)
		data->keys.a = 1;
	if (keycode == KEY_S)
		data->keys.s = 1;
	if (keycode == KEY_D)
		data->keys.d = 1;
	if (keycode == KEY_LEFT)
		data->keys.left = 1;
	if (keycode == KEY_RIGHT)
		data->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 0;
	if (keycode == KEY_A)
		data->keys.a = 0;
	if (keycode == KEY_S)
		data->keys.s = 0;
	if (keycode == KEY_D)
		data->keys.d = 0;
	if (keycode == KEY_LEFT)
		data->keys.left = 0;
	if (keycode == KEY_RIGHT)
		data->keys.right = 0;
	return (0);
}

int	close_window(t_data *data)
{
	clean_exit(data, EXIT_SUCCESS);
	return (0);
}

int	game_loop(t_data *data)
{
	handle_movement(data);
	render_frame(data);
	return (0);
}
