/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:40:45 by esellier          #+#    #+#             */
/*   Updated: 2024/01/19 21:45:34 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cs1;
	const unsigned char	*cs2;

	cs1 = s1;
	cs2 = s2;
	i = 0;
	while ((cs1[i] == cs2[i]) && (i + 1 < n))
		i++;
	if (((cs1[i] == cs2[i]) && (i + 1 == n)) || (n == 0))
		return (0);
	return (cs1[i] - cs2[i]);
}

/*int main ()
{
	int	r;
	int s;
	unsigned char cs1[] = "hellop";
	unsigned char cs2[] = "hello";

	r = ft_memcmp(cs1, cs2, 6);
	printf("%d\n", r);

	s = memcmp(cs1, cs2, 6);
	printf("%d", s);
	return(0);
}*/
