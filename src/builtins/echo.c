/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Bea <Bea@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:44:30 by Bea               #+#    #+#             */
/*   Updated: 2023/06/27 17:26:07 by Bea              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	Output the args, separated by spaces, terminated with a newline. 
	The return status is 0 unless a write error occurs. 
	If -n is specified, the trailing newline is suppressed.
	
*/
