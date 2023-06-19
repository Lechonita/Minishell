/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:14:30 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/19 13:10:59 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*el;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		el = (*lst)-> next;
		ft_lstdelone((*lst), del);
		(*lst) = el;
	}
}
