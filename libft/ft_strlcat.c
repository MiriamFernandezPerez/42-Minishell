/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:52:27 by esellier          #+#    #+#             */
/*   Updated: 2024/01/19 21:53:04 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
//#include <stdio.h>
//#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t s)
{
	size_t	ls;
	size_t	ld;
	size_t	i;
	size_t	r;

	ls = ft_strlen(src);
	ld = 0;
	while (dst[ld] != '\0')
		ld++;
	if (ld < s)
		r = ld + ls;
	else
		r = s + ls;
	if (s == 0)
		return (r);
	i = 0;
	while ((src[i] != '\0') && (ld < s - 1))
	{
		dst[ld] = src[i];
		ld++;
		i++;
	}
	dst[ld] = '\0';
	return (r);
}

/*int main ()
{
	char	dst1[20]= "hello, ";
	char    dst2[20]= "hello, ";
	const char	src[]= "42!";
	size_t	ld;
	ld = ft_strlcat(dst1, src, 0);
	printf("%s\n",dst1);
	printf("%zu\n", ld);

	ld = strlcat(dst2, src, 0);
	printf("%s\n", dst2);
	printf("%zu\n", ld);
}*/
