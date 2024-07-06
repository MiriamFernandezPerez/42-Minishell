/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 22:52:25 by esellier          #+#    #+#             */
/*   Updated: 2024/01/19 15:16:21 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <string.h>
//#include <stdio.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*s;
	unsigned char		*d;

	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	if (src == dst)
		return (dst);
	if (src > dst)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	if (src < dst)
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	return (dst);
}

/*int	main ()
{
	char	dst[60] = "24555";
	char	src[30] = "abc";
	char	dst_lib[60] = "24555";
	char	*m = ft_memmove(dst, src, 40);
	printf("%s\n", m);
	char 	*lib = memmove(dst_lib, src, 40);
	printf("%s", lib);
	return (0);
}*/
