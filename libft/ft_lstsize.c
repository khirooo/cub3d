/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 01:16:49 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/14 01:19:24 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	int		cmpt;
	t_list	*ptr;

	cmpt = 0;
	ptr = lst;
	while (ptr)
	{
		cmpt++;
		ptr = ptr->next;
	}
	return (cmpt);
}
