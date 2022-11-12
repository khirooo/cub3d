/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 01:11:43 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/15 23:48:01 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	else
	{
		if ((*lst) == NULL)
		{
			*lst = new;
			new ->next = NULL;
		}
		else
		{
			new ->next = (*lst);
			*lst = new;
		}
	}
}
