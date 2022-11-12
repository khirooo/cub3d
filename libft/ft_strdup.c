/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:55:41 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/12 19:10:44 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;

	dst = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, src, ft_strlen(src) + 1);
	return (dst);
}
