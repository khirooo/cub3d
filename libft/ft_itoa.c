/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 18:36:43 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/12 19:53:03 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	ft_get_length(int n)
{
	int	length;

	length = 1;
	if (n >= 0)
		length = 1;
	else
		length = 2;
	while (n / 10)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

static char	*ft_get_string(int n)
{
	int		length;
	char	*s;

	length = ft_get_length(n);
	s = (char *)malloc(length + 1);
	if (s == NULL)
		return (NULL);
	if (n < 0)
		s[0] = '-';
	s[length] = '\0';
	return (s);
}

char	*ft_itoa(int n)
{
	int		index;
	char	*s;

	s = ft_get_string(n);
	if (s == NULL)
		return (NULL);
	index = ft_get_length(n) - 1;
	if (n == 0)
		s[0] = '0';
	while (index >= 1 || (index >= 0 && n > 0))
	{
		if (n >= 0)
			s[index] = (n % 10) + 48;
		else
			s[index] = -(n % 10) + 48;
		n = n / 10;
		index--;
	}
	return (s);
}
