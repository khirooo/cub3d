/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:55:53 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/12 16:06:30 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (dstsize != 0)
	{
		i = 0;
		while (i < dstsize - 1 && i < len)
		{
			dst[i] = src[i];
			i++;
		}
			dst[i] = '\0';
	}
	return (len);
}
