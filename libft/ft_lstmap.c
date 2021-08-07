/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 18:50:09 by rpehkone          #+#    #+#             */
/*   Updated: 2021/08/07 09:33:28 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*start;

	new = ft_lstnew(((f(lst))->content), f(lst)->content_size);
	if (!new)
		return (NULL);
	start = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = ft_lstnew(((f(lst))->content), f(lst)->content_size);
		if (!new->next)
			return (NULL);
		new = new->next;
	}
	return (start);
}
