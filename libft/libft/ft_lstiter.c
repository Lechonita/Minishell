/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:14:33 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/19 13:11:06 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*el;

	el = lst;
	if (!lst)
		return ;
	while (el != NULL)
	{
		(*f)(el -> content);
		el = el -> next;
	}
}
