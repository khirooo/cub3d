/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:55:17 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/13 23:44:42 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (n == 0)
		return (0);
	ptr1 = (unsigned char *) s1;
	ptr2 = (unsigned char *) s2;
	while (--n && *ptr1 == *ptr2)
	{
		ptr1++;
		ptr2++;
	}
	return (*ptr1 - *ptr2);
}
