/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:26:03 by esellier          #+#    #+#             */
/*   Updated: 2024/01/26 15:48:20 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t s)
{
	unsigned int	i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	cs1 = (unsigned char *) s1;
	cs2 = (unsigned char *) s2;
	i = 0;
	if (s == 0)
		return (0);
	while ((i < s - 1) && (cs1[i] != '\0') && (cs1[i] == cs2[i]))
		i++;
	if (cs1[i] < cs2[i])
		return (-1);
	if (cs1[i] > cs2[i])
		return (1);
	return (0);
}

/*int	main ()
{
	int	r;
	int r1;

	r = ft_strncmp("Gest", "Hola", 6);
	printf("%i\n", r);

	r1 = strncmp("tola", "aeist", 6);
	printf("%i", r1);
}*/
