/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:13:34 by bebigel           #+#    #+#             */
/*   Updated: 2023/04/14 14:25:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	countwd(char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

size_t	lenwrd(char *s, char c)
{
	size_t	wordlen;

	wordlen = 0;
	while (s[wordlen] != '\0' && s[wordlen] != c)
		++wordlen;
	return (wordlen);
}

char	*get_word(char **s, char c)
{
	size_t	wordlen;
	char	*word;

	while (**s == c)
		++(*s);
	wordlen = lenwrd(*s, c);
	word = (char *)malloc((wordlen + 1) * sizeof(char));
	if (word != NULL)
		ft_strlcpy(word, *s, wordlen + 1);
	*s += wordlen;
	return (word);
}

void	free_str(char **tab)
{
	size_t	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	size_t	nbwrd;
	size_t	i;

	if (!s)
		return (NULL);
	nbwrd = countwd(s, c);
	tab = (char **)malloc(sizeof(char *) * (nbwrd + 1));
	if (tab != NULL)
	{
		i = 0;
		tab[nbwrd] = NULL;
		while (i < nbwrd)
		{
			tab[i] = get_word(&s, c);
			if (tab[i] == NULL)
			{
				free_str(tab);
				tab = NULL;
				break ;
			}
			i++;
		}
	}
	return (tab);
}
