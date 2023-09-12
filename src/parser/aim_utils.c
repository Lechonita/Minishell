/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aim_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrouillo <jrouillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:20:03 by jrouillo          #+#    #+#             */
/*   Updated: 2023/09/12 11:52:21 by jrouillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

char	*join_space(char *s1, char *s2, char *to_add)
{
	char	*tmp;
	char	*str;

	tmp = free_strjoin(s1, to_add);
	str = ft_strjoin(tmp, s2);
	free(tmp);
	return (str);
}

int	last_is_dollar(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i + 1])
		i++;
	if (str[i] == '$')
		return (1);
	return (0);
}

// void	check_pipe(t_token *tok)
// {
// 	t_token	*tmp;
// 	int		flag;

// 	if (!tok)
// 		return ;
// 	tmp = tok;
// 	flag = 0;
// 	while (tmp)
// 	{
// 		if (flag == 1 && tmp->value[0] == '|')
// 			flag = 2;
// 		if (flag == 0 && tmp->value[0] == '|')
// 			flag = 1;
// 		if (tmp->value[0] == '|' && tmp->value[1] == '|')
// 		{
// 			flag = 2;
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (flag == 1)
// 		ft_error(2, W_SINGLE_PIPE);
// 	else if (flag == 2)
// 		ft_error(2, W_DOUBLE_PIPE);
// }
