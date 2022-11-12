/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 13:42:32 by kfergani          #+#    #+#             */
/*   Updated: 2022/11/03 19:51:54 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*result;

	if (!s1)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = (char *)malloc(len_s1 + len_s2 + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, len_s1 + 1);
	ft_strlcpy(result + len_s1, s2, len_s2 + 1);
	return (result);
}

char	*ft_strjoin2(char *s1, char *s2, int flag)
{
	char			*dst;

	if (s1 == 0 || s2 == 0)
		return (0);
	dst = malloc(sizeof(*dst) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == 0)
	{
		if (flag)
			free(s1);
		return (0);
	}
	ft_memcpy(dst, s1, ft_strlen(s1));
	ft_memcpy(dst + ft_strlen(s1), s2, ft_strlen(s2));
	dst[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	if (flag)
		free(s1);
	return (dst);
}

char	*ft_strjoin_withnull(char *s1, char *s2, int flag)
{
	char			*dst;

	if (s2 == NULL)
		return (ft_strdup(s1));
	if (s1 == NULL)
		return (ft_strdup(s2));
	dst = malloc(sizeof(*dst) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == 0)
	{
		if (flag)
			free(s1);
		return (0);
	}
	ft_memcpy(dst, s1, ft_strlen(s1));
	ft_memcpy(dst + ft_strlen(s1), s2, ft_strlen(s2));
	dst[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	if (flag)
		free(s1);
	return (dst);
}
