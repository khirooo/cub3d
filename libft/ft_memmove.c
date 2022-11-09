/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:55:28 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/13 18:40:12 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int		i;
	char	*ptr1;
	char	*ptr2;

	ptr1 = (char *) dst;
	ptr2 = (char *) src;
	i = n;
	if (ptr1 == NULL && ptr2 == NULL)
		return (NULL);
	if (ptr2 < ptr1)
	{
		while (--i >= 0)
		{
			ptr1[i] = ptr2[i];
		}
	}
	else
	{
		ft_memcpy(ptr1, ptr2, n);
	}
	return (dst);
}
