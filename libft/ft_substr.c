/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 12:47:16 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/13 23:31:03 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		len_s;
	char		*sub_s;
	int			maxsize_sub;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	maxsize_sub = len_s - start + 1;
	if (maxsize_sub <= 0)
		len = 0;
	if ((len + 1) <= (size_t)maxsize_sub)
		maxsize_sub = len + 1;
	sub_s = (char *) malloc(maxsize_sub);
	if (sub_s == NULL)
		return (NULL);
	ft_strlcpy(sub_s, s + start, maxsize_sub);
	return (sub_s);
}
