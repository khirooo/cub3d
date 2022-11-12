/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:55:37 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/11 18:36:32 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c2;

	c2 = c;
	while (*s && *s != c2)
	{
		s++;
	}
	if (c2 != '\0' && *s == '\0')
		return (NULL);
	return ((char *)s);
}
