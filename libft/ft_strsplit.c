/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 22:58:39 by satkins           #+#    #+#             */
/*   Updated: 2016/07/19 23:00:46 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		word_count(const char *s, char c)
{
	int			i;

	i = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
			i++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (i);
}

static size_t	word_len(char const *s, char c)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static char		*next_word(char const *s, char c)
{
	while (*s != '\0' && *s == c)
		s++;
	return ((char *)s);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**array;
	int			count;
	size_t		curr_len;
	char		*curr;
	int			i;

	i = -1;
	if (!s)
		return (NULL);
	count = word_count(s, c);
	curr = next_word(s, c);
	curr_len = 0;
	array = (char **)malloc(sizeof(char *) * (1 + count));
	if (!array)
		return (NULL);
	while (++i < count)
	{
		curr = next_word(&curr[curr_len], c);
		curr_len = word_len(curr, c);
		array[i] = (char *)malloc(sizeof(char) * (1 + curr_len));
		ft_strncpy(array[i], curr, curr_len);
		array[i][curr_len] = '\0';
	}
	array[i] = NULL;
	return (array);
}
