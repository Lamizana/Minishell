/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:57:20 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/10 16:43:44 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* scans the first n bytes of s for the first *
 * occurence of c and returns a pointer to    *
 * matching byte                              */

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	size_t			slen;
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	c = (unsigned char)c;
	c = c % 256;
	slen = ft_strlen(s);
	i = 0;
	if (n == 0)
		return (NULL);
	if (c == '\0')
		return (s2 + slen);
	while (i < n)
	{
		if (*s2 == c)
			return (s2);
		s2++;
		i++;
	}
	return (NULL);
}
