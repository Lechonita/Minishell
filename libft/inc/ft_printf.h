/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:17:56 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/19 13:03:39 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h> //strlen
# include <stdarg.h> // va_start, va_arg, va_end, va_copy

	/*	ft_printf fonctions	*/
int		ft_printf(const char *fmt, ...);
int		ft_conv(va_list args, char c);
int		ft_ptr(uintptr_t nb);
int		ft_hexa(unsigned int nb, char c);
int		ft_nbr(int nb, char c);

	/*	counting fonctions	*/
int		ft_count(int nb, int base);
int		ft_countus(unsigned int nb, int base);
int		ft_countp(uintptr_t nb, int base);
int		ft_countchar(char c);
int		ft_countstr(char *s);

	/*	writing fonctions	*/
void	ft_putnbr_base(int nbr, char *base);
void	ft_putnbr_baseus(unsigned int nbr, char *base);
void	ft_putnbr_basep(uintptr_t nbr, char *base);

	/*	annexes	*/
void	ft_putchar(char c);

#endif