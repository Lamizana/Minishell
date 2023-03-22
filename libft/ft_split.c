/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:03:34 by vsaura            #+#    #+#             */
/*   Updated: 2022/12/12 16:49:20 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* allocates with malloc and returns an array of strings  *
 * obtained by separating the string s with the separator * 
 * c as a separator. the array is then NULL terminated.   */

static size_t	wordcount(char const *s, char c)
{
	size_t	ct;
	int		i;

	i = 0;
	ct = 0;
	if (!s[i])
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			ct++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (ct);
}

static int	lencheck(char const *s, char c)
{
	int	len;

	if (!ft_strchr(s, c))
		len = ft_strlen(s);
	else
		len = ft_strchr(s, c) - s;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		len;
	int		i;

	if (!s)
		return (0);
	i = 0;
	tab = ft_calloc(sizeof(char *), (wordcount(s, c) + 1));
	if (!tab)
		return (NULL);
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != '\0')
		{
			len = lencheck(s, c);
			tab[i] = ft_substr(s, 0, len);
			i++;
			s += len;
		}
	}
	tab[i] = NULL;
	return (tab);
}
