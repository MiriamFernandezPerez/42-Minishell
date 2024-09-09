/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:42:49 by esellier          #+#    #+#             */
/*   Updated: 2024/03/12 16:15:23 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*m;
	size_t	l;

	l = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= l || l == 0)
	{
		m = ft_strdup("");
		return (m);
	}
	if (len > l - start)
		len = l - start;
	m = (char *)malloc(len + 1);
	if (!m)
		return (NULL);
	ft_strlcpy(m, &s[start], len + 1);
	return (m);
}

/*int main()
{
	size_t	len = 1;
	unsigned int	start = 1;
	char const *s = "";
	char *r = ft_substr(s, start, len);
	printf("%s\n", r);
}*/