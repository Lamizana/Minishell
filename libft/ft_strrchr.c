/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:09:50 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/13 14:30:52 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* returns a pointer to the last *
 * occurence of c in s           */

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	c = c % 256;
	while (s[i] != '\0')
		i++;
	if (s[i] == c)
		return ((char *)&s[i]);
	while (i != 0)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i--;
	}
	if (c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}
