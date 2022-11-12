/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:55:21 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/13 18:39:46 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*ptr1;
	char		*ptr2;

	ptr1 = (char *) dst;
	ptr2 = (char *) src;
	i = 0;
	if (ptr1 == NULL && ptr2 == NULL)
		return (NULL);
	while (i < n)
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	return (dst);
}
