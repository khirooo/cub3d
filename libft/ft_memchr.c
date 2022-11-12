/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:28:03 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/13 18:42:26 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	c2;

	c2 = (unsigned char)c;
	ptr = (unsigned char *) s;
	if (n == 0)
		return (NULL);
	while (--n && *ptr != c2)
	{
		ptr++;
	}
	if (c2 != *ptr)
		return (NULL);
	return (ptr);
}
