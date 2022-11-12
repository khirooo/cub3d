/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:23:03 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/15 18:41:38 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_count_subs(char const *s, char c)
{
	int	cmp2;

	cmp2 = 0;
	while (*s)
	{
		while (*s && *s == c)
		{
			s++;
		}
		if (*s)
			cmp2++;
		while (*s && *s != c)
		{
			s++;
		}
	}
	return (cmp2);
}

static char	*ft_next_sub(char const **s, char c)
{
	int		cmp1;
	char	*sub_s;
	char	*ptr;

	while (**s && **s == c)
	{
		(*s)++;
	}
	sub_s = NULL;
	ptr = (char *)*s;
	cmp1 = 0;
	while (**s && **s != c)
	{
		cmp1++;
		(*s)++;
	}
	if (cmp1 != 0)
		sub_s = ft_substr(ptr, 0, cmp1);
	return (sub_s);
}

static void	free_backtrack(char **array, int i)
{
	while (i-- >= 0)
		free(array[i]);
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char		**array;
	int			i;
	int			cmp;

	if (!s)
		return (NULL);
	cmp = ft_count_subs(s, c);
	array = (char **) malloc((cmp + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array[cmp] = NULL;
	i = 0;
	while (i < cmp)
	{
		array[i] = ft_next_sub(&s, c);
		if (array[i] != NULL)
			i++;
		else
		{
			free_backtrack(array, i);
			return (NULL);
		}
	}
	return (array);
}
