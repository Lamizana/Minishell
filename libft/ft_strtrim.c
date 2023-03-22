/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:27:29 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/13 13:57:09 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* allocates with malloc and returns a copy of the string s *
 * without the characters specified in set at the beginning *
 * and end of the string.                                   */

static int	ft_chrcmp(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	size_t	len;
	char	*str;

	i = 0;
	if (!s1)
		return (0);
	len = ft_strlen(s1);
	if (!set)
		return ((char *)s1);
	while (ft_chrcmp(s1[i], set) == 0)
		i++;
	while (ft_chrcmp(s1[len - 1], set) == 0)
		len--;
	str = ft_substr(s1, i, len - i);
	return (str);
}
