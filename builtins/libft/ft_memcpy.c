/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:27:30 by esellier          #+#    #+#             */
/*   Updated: 2024/01/17 15:54:39 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <string.h>
//#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	if (!src && !dest)
		return (dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*int main ()
{
	unsigned char	dest[30] = "42!"; 
	unsigned char   dest2[30] = "42!";
	unsigned char	src[] = "Hello";
	unsigned char   src2[] = "Hello";

	printf("%s\n", ft_memcpy(dest, src, 2));
	printf("%s", memcpy(dest2, src2, 2));
	return (0);
}*/
