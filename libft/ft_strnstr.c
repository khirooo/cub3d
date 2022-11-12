/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:56:04 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/15 18:39:44 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *haystack, const char *needlem, size_t len)
{
	size_t		len_needl;

	if (*needlem && len == 0)
		return (NULL);
	len_needl = ft_strlen((char *)needlem);
	if (*needlem == '\0')
		return ((char *)haystack);
	while (*haystack && (len - 1)
		&& ft_strncmp(haystack, needlem, len_needl) != 0 && len >= len_needl)
	{
		haystack++;
		len = len - 1;
	}
	if (len >= len_needl && ft_strncmp(haystack, needlem, len_needl) == 0)
		return ((char *)haystack);
	return (NULL);
}
