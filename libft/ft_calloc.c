/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:54:50 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/16 02:26:02 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	double	i;
	void	*ptr;

	i = (double)count * (double)size;
	if (i > SIZE_MAX)
		return (NULL);
	if (count == 0 || size == 0)
		return (malloc(0));
	ptr = (void *)malloc(i);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (size_t)i);
	return (ptr);
}
