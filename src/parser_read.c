/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabdulka <dabdulka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 01:41:54 by dabdulka          #+#    #+#             */
/*   Updated: 2026/08/04 14:56:15 by dabdulka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static char	*append_chunk(char *content, char *buf)
{
	char	*tmp;

	tmp = content;
	content = ft_strjoin(tmp, buf);
	free(tmp);
	return (content);
}

static char	*read_loop(int fd, char *content)
{
	char	buf[BUF_SIZE + 1];
	ssize_t	bytes;

	bytes = read(fd, buf, BUF_SIZE);
	while (bytes > 0)
	{
		buf[bytes] = '\0';
		content = append_chunk(content, buf);
		if (!content)
			break ;
		bytes = read(fd, buf, BUF_SIZE);
	}
	if (!content || bytes < 0)
	{
		free(content);
		return (NULL);
	}
	return (content);
}

char	*read_file(const char *path)
{
	int		fd;
	char	*content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = ft_strdup("");
	if (!content)
	{
		close(fd);
		return (NULL);
	}
	content = read_loop(fd, content);
	close(fd);
	return (content);
}
