/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:50:24 by esellier          #+#    #+#             */
/*   Updated: 2024/01/25 16:41:36 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int	i;
	int	r;
	int	m;

	i = 0;
	m = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 45)
	{
		m = -1;
		i++;
	}
	if (str[i] == 43 && m != -1)
	{
		i++;
	}
	r = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		r = r * 10 + (str[i] - '0');
		i++;
	}
	return (m * r);
}

/*int main()
{
	int r;
	int s;
	char str[] = " -2147483565844787648";

	s = ft_atoi(str);
	printf("%d\n", s);

	r = atoi(str);
	printf("%d\n", r);
}*/
