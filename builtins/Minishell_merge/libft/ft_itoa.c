/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:14:01 by esellier          #+#    #+#             */
/*   Updated: 2024/01/24 23:28:11 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

static int	ft_intlen(int n)
{
	int		i;
	long	lgn;

	lgn = n;
	if (lgn == 0)
		return (2);
	i = 1;
	if (lgn < 0)
	{
		i++;
		lgn = lgn * -1;
	}
	while (lgn != 0)
	{
		lgn = (lgn / 10);
		i++;
	}
	return (i);
}

static char	*ft_transform(int n, char *c)
{
	int		j;
	long	lgn;

	lgn = n;
	j = ft_intlen(n);
	c[j - 1] = '\0';
	if (lgn < 0)
	{
		c[0] = '-';
		lgn = lgn * -1;
	}
	while (lgn > 0)
	{
		c[j - 2] = (lgn % 10) + '0';
		lgn = lgn / 10;
		j--;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char	*c;
	int		len;
	long	lgn;

	lgn = n;
	len = ft_intlen(n);
	c = malloc((len) * sizeof(char));
	if (!c)
		return (NULL);
	if (lgn == 0)
	{
		c[0] = '0';
		c[1] = '\0';
		return (c);
	}
	c = ft_transform(n, c);
	return (c);
}

/*int main ()
{
	char	*r;
	int	n = 0;

	r = ft_itoa(n);
	printf("%s", r);
}*/
