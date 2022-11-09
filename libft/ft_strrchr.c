/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:56:08 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/13 18:58:55 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*tmp;
	unsigned char	c2;

	tmp = NULL;
	c2 = (char)c;
	while (*s)
	{
		if (*s == c2)
			tmp = s;
		s++;
	}
	if (c2 == '\0')
		return ((char *)s);
	if (tmp && *tmp != c2)
		return (NULL);
	return ((char *)tmp);
}
