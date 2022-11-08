/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:33:36 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/03 17:30:49 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_clean(char	*buffer, int break_index)
{
	char	*clean_buffer;

	clean_buffer = (char *)malloc(sizeof(char) * (break_index + 2));
	if (!clean_buffer)
	{
		free(buffer);
		return (NULL);
	}
	clean_buffer[break_index + 1] = '\0';
	ft_copy(clean_buffer, buffer, break_index + 1);
	free(buffer);
	return (clean_buffer);
}

int	dumb_norm_code(int nb_bytes, char **buffer, char **line, int fd)
{
	*buffer = init_buffer(BUFFER_SIZE, *buffer);
	nb_bytes = read(fd, *buffer, BUFFER_SIZE);
	if (!nb_bytes || nb_bytes == -1)
	{
		free(*buffer);
		*buffer = NULL;
		if (nb_bytes == -1)
		{
			if (*line)
				free(*line);
			return (0);
		}
		if (!nb_bytes)
		{
			if (*line && !**line)
			{
				free(*line);
				return (0);
			}
			return (-1);
		}
	}
	*line = ft_append(*line, *buffer);
	return (1);
}

char	*ft_get_line(int fd, char *rest)
{
	char	*line;
	char	*buffer;
	int		x;

	line = NULL;
	buffer = NULL;
	line = ft_append(line, rest);
	if (ft_new_line(rest) != -1)
	{
		free(rest);
		return (line);
	}
	free(rest);
	while (ft_new_line(buffer) == -1)
	{
		x = dumb_norm_code(x, &buffer, &line, fd);
		if (x == 0)
			return (NULL);
		else if (x == -1)
			break ;
	}
	if (ft_new_line(buffer) != -1)
		free(buffer);
	return (line);
}

char	*ft_get_rest(char	**line)
{
	char	*rest;
	int		i;
	int		len;

	len = ft_strlen2(*line);
	i = ft_new_line(*line);
	if (i == -1 || i == len - 1)
		return (NULL);
	rest = (char *)malloc(sizeof(char) * (len - i));
	if (!rest)
		return (NULL);
	rest[len - i - 1] = '\0';
	ft_copy(rest, (*line) + i + 1, len - i - 1);
	*line = ft_clean(*line, i);
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest = NULL;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	line = ft_get_line(fd, rest);
	rest = ft_get_rest(&line);
	return (line);
}
