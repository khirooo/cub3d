/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:45:49 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/03 17:33:21 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_new_line(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s == '\n')
			return (i);
		s++;
		i++;
	}
	return (-1);
}

void	ft_copy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dest[i] = src[i];
		i++;
	}
}

char	*init_buffer(size_t size, char *buffer)
{
	char	*s;
	size_t	i;

	if (buffer)
		free(buffer);
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		s[i] = '\0';
		i++;
	}
	return (s);
}

char	*ft_append(char	*dest, char	*src)
{
	char	*buffer;
	int		len_dest;
	int		len_src;

	len_dest = ft_strlen2(dest);
	len_src = ft_strlen2(src);
	if (!len_src)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (len_dest + len_src + 1));
	if (!buffer)
		return (NULL);
	ft_copy(buffer, dest, len_dest);
	ft_copy(buffer + len_dest, src, len_src);
	buffer[len_dest + len_src] = '\0';
	if (dest)
		free(dest);
	return (buffer);
}

int	ft_strlen2(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}
