/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:48:27 by bebigel           #+#    #+#             */
/*   Updated: 2023/06/12 17:56:19 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <stdarg.h>	// va_start, va_arg, va_end, va_copy
# include <stdint.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/* ******************************************** */
/*                                              */
/*			functions from <ctype.h>			*/
/*                                              */
/* ******************************************** */
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);

/* ******************************************** */
/*                                              */
/*			functions from <stdlib.h>			*/
/*                                              */
/* ******************************************** */
/*Allocates the requested memory and returns a pointer to it*/
void		*ft_calloc(size_t nmemb, size_t size);

/*Converts the string pointed to, by the argument str to an integer*/
long int	ft_atoi(const char *nptr);

	/*	functions from <strings.h>	*/
/*Compares the first n bytes of str1 and str2*/
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/*Copies n characters from src to dest*/
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, void *src, size_t n);

/*Searches for the first occurrence of the character c (unsigned char) in the 
first n bytes of the string pointed to, by the argument str*/
void		*ft_memchr(const void *s, int c, size_t n);

/*Copies the character c (unsigned char) to the first n characters of the 
string pointed to, by the argument str*/
void		*ft_memset(void *s, int c, size_t n);

/*erases the data in the n bytes of the memory starting at the location pointed
to by s, by writing zeros (bytes containing '\0') to that area*/
void		ft_bzero(void *s, size_t n);

/* ******************************************** */
/*                                              */
/*			functions from <string.h>			*/
/*                                              */
/* ******************************************** */
/*appends the NUL-term string src to the end of dst. It will append at most
size - strlen(dst) - 1 bytes, NUL-terminating the result*/
size_t		ft_strlcat(char *dest, const char *src, size_t size);

/*copies up to size-1 char from the NULterm src to dst, NUL-terminating result*/
size_t		ft_strlcpy(char *dest, const char *src, size_t size);

/*Searches for the first occurrence of the character c (unsigned char) in the 
string pointed to, by the argument str*/
char		*ft_strchr(const char *s, int c);

/*Computes the length of the string str (not including the null character)*/
int			ft_strlen(const char *s);

/*This function returns a pointer to a null-term byte string, which is a 
duplicate of the string pointed to by s*/
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *src, size_t n);

/*locates the first occurrence of the null-term string little in the string big,
where not more than len characters are searched*/
char		*ft_strnstr(const char *big, const char *little, size_t len);

/*Compares at most the first n bytes of str1 and str2*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/*Find the last occurrence of a character (c) in a string*/
char		*ft_strrchr(const char *s, int c);

/* ******************************************** */
/*                                              */
/*			Additional functions				*/
/*                                              */
/* ******************************************** */
/* Allocates and returns a substring from the original string. This new string 
starts at the input index. Returns NULL if allocation fails */
char		*ft_substr(char const *s, unsigned int start, size_t len);

/*Allocates and returns a duplicate string each character of which has been 
modified by the input function (which takes as argument each character of the 
input string and its index). Returns NULL if the allocation fails*/
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*Allocates and returns a duplicate string each character of which has been 
modified by the input function (which takes as argument the input string and 
its index). Returns NULL if the allocation fails*/
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

/*Allocates and returns a copy of the input string without the set's characters
at the beginning and at the end. Returns NULL if allocation fails*/
char		*ft_strtrim(char const *s1, char const *set);

/*Allocates and returns a new string resulting from the concatenation of two 
strings. Returns NULL if allocation fails*/
char		*ft_strjoin(char const *s1, char const *s2);

/*Writes a string on the input file descriptor followed by a newline*/
void		ft_putendl_fd(char *s, int fd);

/*Writes a character on the input file descriptor*/
void		ft_putchar_fd(char c, int fd);

/*Writes a string on the input file descriptor*/
void		ft_putstr_fd(char *s, int fd);

/*Writes a integer on the input file descriptor*/
void		ft_putnbr_fd(int n, int fd);

/*Allocates and returns a string representing the input integer. Negative nbers
are supported. Returns NULL if allocation fails*/
char		*ft_itoa(int n);

/*Allocates and returns an array of strings obtained by separating the input 
string with the input character used as the delimiter. The resulting array is 
terminated with a NULL pointer. Returns NULL if allocation fails*/
char		**ft_split(char *s, char c);

/* ******************************************** */
/*                                              */
/*			Linked lists functions				*/
/*                                              */
/* ******************************************** */
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstadd_back(t_list **lst, t_list *new);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstsize(t_list *lst);

/* ******************************************** */
/*                                              */
/*					ft_printf					*/
/*                                              */
/* ******************************************** */
	/*	ft_printf fonctions	*/
int			ft_printf(const char *fmt, ...);
int			ft_conv(va_list args, char c);
int			ft_ptr(uintptr_t nb);
int			ft_hexa(unsigned int nb, char c);
int			ft_nbr(int nb, char c);

	/*	counting fonctions	*/
int			ft_count(int nb, int base);
int			ft_countus(unsigned int nb, int base);
int			ft_countp(uintptr_t nb, int base);
int			ft_countchar(char c);
int			ft_countstr(char *s);

	/*	writing fonctions	*/
void		ft_putnbr_base(int nbr, char *base);
void		ft_putnbr_baseus(unsigned int nbr, char *base);
void		ft_putnbr_basep(uintptr_t nbr, char *base);

	/*	annexes	*/
void		ft_putchar(char c);

#endif
