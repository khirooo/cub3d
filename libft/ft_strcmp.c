/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 18:12:41 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/03 18:12:52 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_strcmp(const char *s1, const char *s2)
{
	int		i;
	int		m;
	char	*tmp;

	i = 0;
	m = 0;
	tmp = (char *)s2;
	while (*s1 && *s2 && (*s1 == *s2 || *s1 + 32 == *s2 || *s1 == *s2 + 32))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
