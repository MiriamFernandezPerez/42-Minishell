/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:12:03 by esellier          #+#    #+#             */
/*   Updated: 2024/01/25 17:25:41 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while ((i < len) && (haystack[i] != '\0'))
	{
		j = 0;
		while ((i + j < len) && (haystack[i + j] == needle[j]))
		{
			if (j == ft_strlen(needle) - 1)
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (0);
}

/*int	main(void)
{
	const char *haystack;
	const char *needle;
	size_t len;
	char *r;
	char *s;
	haystack = "Bonjour, comment tu t'appelles ordinateur?";
	needle = "jour";
	len = 5;

	s = ft_strnstr(haystack, needle, len);
	printf("%s\n", s);

	r = strnstr(haystack, needle, len);
	printf("%s\n", r);
}*/
