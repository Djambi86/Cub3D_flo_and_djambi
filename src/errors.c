/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:43:09 by dabdulka          #+#    #+#             */
/*   Updated: 2026/08/04 14:26:55 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	parse_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	parse_error_free(const char *msg, t_scene *scene)
{
	free_scene(scene);
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

void	runtime_error(t_data *data, const char *msg)
{
	write(2, msg, ft_strlen(msg));
	clean_exit(data, EXIT_FAILURE);
}
