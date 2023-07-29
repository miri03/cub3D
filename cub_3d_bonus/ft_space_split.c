/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:46:32 by meharit           #+#    #+#             */
/*   Updated: 2023/07/28 14:42:40 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_size(char const *s, char c, char d)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == d))
			i++;
		if (s[i])
			word++;
		while (s[i] && (s[i] != c && s[i] != d))
			i++;
	}
	return (word);
}

static char	*ft_word(char const *s, int size)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (word == NULL)
		return (NULL);
	while (size > i)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	error_free(char **result, int i)
{
	while (i >= 0)
	{
		free(result[i]);
		i--;
	}
}

static void	ft_alloc(char **result, char const *s, char c, char d)
{
	int	alloc;
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = ft_size(s, c, d);
	while (s[j] && i < size)
	{
		alloc = 0;
		while (s[j] && (s[j] == c || s[j] == d))
			j++;
		while (s[j + alloc] && (s[j + alloc] != c && s[j + alloc] != d))
			alloc++;
		result[i] = ft_word(&s[j], alloc);
		if (result[i] == NULL)
			return (error_free(result, i), free(result));
		i++;
		j += alloc;
	}
	result[i] = NULL;
}

char	**ft_space_split(char const *s, char c, char d)
{
	char	**result;
	int		size;

	if (s == NULL)
		return (NULL);
	size = ft_size(s, c, d);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);
	ft_alloc(result, s, c, d);
	return (result);
}
