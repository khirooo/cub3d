/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:55:45 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/12 18:06:17 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;

	len_dst = ft_strlen(dst);
	if (dstsize == 0)
		return (ft_strlen(src));
	i = len_dst;
	j = 0;
	if (dstsize > (len_dst + (ft_strlen(src))) + 1)
		dstsize = (len_dst + (ft_strlen(src)) + 1);
	while ((int)(dstsize - len_dst - 1) >= 0 && j < (dstsize - len_dst - 1)
		&& j < ft_strlen(src))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (len_dst <= dstsize)
	{
		dst[i] = '\0';
		return (len_dst + ft_strlen(src));
	}
	return (dstsize + ft_strlen(src));
}
