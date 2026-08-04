/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:42:27 by dabdulka          #+#    #+#             */
/*   Updated: 2026/08/04 14:26:55 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	valid_number(char *str)
{
	long	value;
	int		len;

	if (!str)
		return (0);
	while (is_space(*str))
		str++;
	len = 0;
	value = 0;
	while (ft_isdigit(str[len]))
	{
		if (value <= 100000)
			value = value * 10 + (str[len] - '0');
		len++;
	}
	if (len == 0)
		return (0);
	str += len;
	while (is_space(*str))
		str++;
	if (*str != '\0')
		return (0);
	return (value <= 255);
}

static int	values_valid(char **parts)
{
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (0);
	if (!valid_number(parts[0]) || !valid_number(parts[1])
		|| !valid_number(parts[2]))
		return (0);
	return (1);
}

int	parse_color(char *value)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	parts = split_commas(value);
	if (!values_valid(parts))
	{
		free_split(parts);
		return (-1);
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_split(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}
