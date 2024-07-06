/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:06:57 by esellier          #+#    #+#             */
/*   Updated: 2024/01/19 21:53:56 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t s)
{
	size_t	i;

	i = 0;
	if (!dst)
		return (ft_strlen(src));
	if (s > 0)
	{
		while ((src[i] != '\0') && (i + 1 < s))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

/*int main ()
{
	size_t	r;
	size_t	s;
	char dst[25] = "hello";
	const char src[] = "42!";

	r = ft_strlcpy(dst, src, 0);
	printf("%zu\n", r);

	s = strlcpy(dst, src, 0);
	printf("%zu", s);
	return(0);
}*/
