/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:55:33 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/11 17:38:18 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char		c2;
	size_t				i;
	char				*ptr;

	ptr = (char *) b;
	c2 = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		ptr[i] = c2;
		i++;
	}
	return (b);
}
