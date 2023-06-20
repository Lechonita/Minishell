/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:33:33 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/20 09:42:32 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*last;
	t_list	*el;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst -> content));
	if (!new)
		return (NULL);
	last = new;
	lst = lst -> next;
	while (lst)
	{
		el = ft_lstnew(f(lst -> content));
		if (!el)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		last -> next = el;
		last = el;
		lst = lst -> next;
	}
	last -> next = NULL;
	return (new);
}
