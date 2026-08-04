/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colors_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flaplanc <flaplanc@students.42vienna.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 18:03:26 by flaplanc          #+#    #+#             */
/*   Updated: 2026/08/04 18:03:26 by flaplanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static char	*extract_field(const char *s, int start, int end)
{
	char	*res;
	int		i;

	res = malloc(end - start + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

static int	count_commas(const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
			count++;
		i++;
	}
	return (count);
}

char	**split_commas(const char *s)
{
	char	**res;
	int		count;
	int		i;
	int		start;
	int		j;

	count = count_commas(s) + 1;
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
	start = 0;
	j = 0;
	while (j < count)
	{
		i = start;
		while (s[i] && s[i] != ',')
			i++;
		res[j] = extract_field(s, start, i);
		if (!res[j])
			return (free_split(res), NULL);
		start = i + 1;
		j++;
	}
	return (res);
}
