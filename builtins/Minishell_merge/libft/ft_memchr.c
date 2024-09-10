/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 18:04:03 by esellier          #+#    #+#             */
/*   Updated: 2024/01/17 18:27:25 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_char;
	unsigned char	c_char;

	s_char = (unsigned char *)s;
	c_char = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (s_char[i] == c_char)
			return ((void *)(s_char + i));
		i++;
	}
	return (0);
}

/*int	main ()
{
	const void	*r;

	r = ft_memchr("hello 42!", 0, 0);
	printf("%s\n", r);

	r = memchr("hello 42!", 0, 0);
	printf("%s", r);
	}*/
