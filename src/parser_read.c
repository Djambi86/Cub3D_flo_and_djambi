/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:41:54 by dabdulka          #+#    #+#             */
/*   Updated: 2026/07/27 01:41:55 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*append_chunk(char *content, char *buf)
{
	char	*tmp;

	tmp = content;
	content = ft_strjoin(tmp, buf);
	free(tmp);
	return (content);
}

char	*read_file(const char *path)
{
	int		fd;
	char	*content;
	char	buf[BUF_SIZE + 1];
	ssize_t	bytes;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = ft_strdup("");
	bytes = read(fd, buf, BUF_SIZE);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		content = append_chunk(content, buf);
		bytes = read(fd, buf, BUF_SIZE);
	}
	close(fd);
	if (bytes < 0)
	{
		free(content);
		return (NULL);
	}
	return (content);
}
