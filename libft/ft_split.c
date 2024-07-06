/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:22:24 by esellier          #+#    #+#             */
/*   Updated: 2024/03/12 16:50:13 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	if ((*s) && (*s != c))
		count++;
	while (*s)
	{
		if ((*s == c) && (*(s + 1) != c) && (*(s + 1)))
			count++;
		s++;
	}
	return (count);
}

static size_t	ft_string_len(const char *s, char c)
{
	int	i;

	i = 0;
	while ((s[i] != '\0') && (s[i] != c))
		i++;
	return (i);
}

static void	ft_free(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static char	**ft_strings_array(char **array, char const *s, char c)
{
	size_t	len_word;
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			len_word = ft_string_len(s, c);
			array[i] = ft_substr(s, 0, len_word);
			if (!array[i])
			{
				ft_free(array);
				return (NULL);
			}
			s = s + len_word;
			i++;
		}
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	return (ft_strings_array(array, s, c));
}

/*int	main (void)
{
	char		**r;
	const char	*s = "Bonjour, un croissant s'il vous plait.";
	char		c = ' ';

	r = ft_split(s, c);
	while (*r)
	{
		printf("%s\n", *r);
		r++;
	}
	return (0);
}*/