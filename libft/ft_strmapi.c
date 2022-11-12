/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:59:25 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/13 23:25:04 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s_copy;
	int		i;

	if (!s)
		return (NULL);
	s_copy = (char *) malloc(ft_strlen(s) + 1);
	if (s_copy == NULL)
		return (NULL);
	s_copy[ft_strlen(s)] = '\0';
	i = 0;
	while (s[i])
	{
		s_copy[i] = f(i, s[i]);
		i++;
	}
	return (s_copy);
}
