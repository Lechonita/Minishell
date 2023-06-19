/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:12:52 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/19 13:11:19 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*first;

	size = 0;
	first = lst;
	while (first)
	{
		size++;
		first = first -> next;
	}
	return (size);
}
