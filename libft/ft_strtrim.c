/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:57:11 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/13 23:27:51 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static	int	ft_is_in(char const c, char const *set)
{
	int	bol;

	bol = 0;
	while (*set && !bol)
	{
		if (c == *set)
			bol = 1;
		set++;
	}
	return (bol);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int			left_count;
	int			right_count;
	int			i;
	char		*strim;

	if (!s1)
		return (NULL);
	i = 0;
	while (i < (int)ft_strlen(s1) && ft_is_in(s1[i], set))
	{
		i++;
	}
	left_count = i;
	if (left_count == (int)ft_strlen(s1))
		return ((char *)ft_calloc(1, 1));
	right_count = 0;
	i = ft_strlen(s1) - 1;
	while (i >= 0 && ft_is_in(s1[i], set))
	{
		right_count++;
		i--;
	}
	strim = ft_substr(s1, left_count, ft_strlen(s1) - left_count - right_count);
	return (strim);
}
