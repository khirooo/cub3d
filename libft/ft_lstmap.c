/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 19:45:13 by kfergani          #+#    #+#             */
/*   Updated: 2022/04/16 00:31:24 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp;
	t_list	*ptr;

	if (!lst || !f)
		return (NULL);
	ptr = lst;
	new_lst = ft_lstnew(f(lst ->content));
	if (!new_lst)
		return (NULL);
	lst = lst ->next;
	while (lst)
	{
		tmp = ft_lstnew(f(lst ->content));
		if (!tmp)
		{
			ft_lstclear(&new_lst, del);
			ft_lstclear(&ptr, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, tmp);
		lst = lst->next;
	}
	return (new_lst);
}
