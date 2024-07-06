/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 22:00:21 by esellier          #+#    #+#             */
/*   Updated: 2024/01/25 17:28:25 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

static int	ft_checkset(char const s1, char const *set)
{
	while (*set)
	{
		if (s1 == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	len_start;

	if (!s1)
		return (0);
	if ((!set) || (!*set) || (!*s1))
		return (ft_strdup(s1));
	while ((*s1) && (ft_checkset (*s1, set)))
		s1++;
	len_start = ft_strlen(s1);
	while ((len_start > 0) && ft_checkset(s1[len_start - 1], set))
		len_start--;
	return (ft_substr (s1, 0, len_start));
}

/*int main()
{
	char	*r;
	char const	*set = "   ";
	char const	*s1 = "     Hola!        ";
	r = ft_strtrim(s1, set);
	printf("%s", r);
}*/
