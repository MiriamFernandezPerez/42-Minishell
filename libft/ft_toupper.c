/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 18:39:13 by esellier          #+#    #+#             */
/*   Updated: 2024/01/16 15:28:50 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>

int	ft_toupper(int c)
{
	if ((c >= 97) && (c <= 122))
		return (c - 32);
	else
		return (c);
}

/*int	main ()
{
	int	t;
	int	c = 'e';
	t = ft_toupper(c);
	printf("%c\n", t);

	t = toupper (c);
	printf("%c", t);
}*/
