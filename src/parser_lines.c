/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:42:13 by dabdulka          #+#    #+#             */
/*   Updated: 2026/07/27 01:42:16 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	count_lines(const char *content)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

static char	*extract_line(const char *content, int start, int end)
{
	char	*line;
	int		i;

	while (end > start && content[end - 1] == '\r')
		end--;
	line = malloc(end - start + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		line[i] = content[start + i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	fill_lines(char **lines, char *content)
{
	int	i;
	int	start;
	int	n;

	i = 0;
	start = 0;
	n = 0;
	while (1)
	{
		if (content[i] == '\n' || content[i] == '\0')
		{
			lines[n] = extract_line(content, start, i);
			if (!lines[n++])
				return (0);
			start = i + 1;
			if (content[i] == '\0')
				return (1);
		}
		i++;
	}
}

char	**split_lines(char *content)
{
	char	**lines;

	lines = ft_calloc(count_lines(content) + 1, sizeof(char *));
	if (!lines)
		return (NULL);
	if (!fill_lines(lines, content))
	{
		free_split(lines);
		return (NULL);
	}
	return (lines);
}
