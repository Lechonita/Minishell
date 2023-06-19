/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:30:01 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/19 13:10:56 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*first;

	if (!*lst || !lst)
	{
		*lst = new;
		return ;
	}
	first = *lst;
	new -> next = first;
	*lst = new;
}
