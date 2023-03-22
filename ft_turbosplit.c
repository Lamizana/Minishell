/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_turbosplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 14:03:34 by vsaura            #+#    #+#             */
/*   Updated: 2023/03/03 11:30:34 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	skip_quotes(char *s, int i)
{
	if (s[i] == 39)
	{
		i++;
		while (s[i] != 39)
		{
			if (s[i] == '\0')
				return (-1);
			i++;
		}
	}
	else if (s[i] == 34)
	{
		i++;
		while (s[i] != 34)
		{
			if (s[i] == '\0')
				return (-1);
			i++;
		}
	}
	return (i);
}

static int	turbocount(char *s, char c)
{
	int		ct;
	int		i;

	i = 0;
	ct = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] != c && s[i])
			ct++;
		while (s[i] && s[i] != c)
		{
			i = skip_quotes(s, i);
			if (i == -1)
				return (-1);
			i++;
		}
		if (s[i])
			i++;
	}
	return (ct);
}

char	**ft_turbosplit(char *s, char c, int i, int j)
{
	char	**tab;
	int		max;

	max = turbocount(s, c);
	if (max == -1)
		return (NULL);
	tab = ft_calloc(sizeof(char *), (max + 1));
	if (!tab)
		return (NULL);
	while (j < max)
	{
		while (*s == c && *s != '\0')
			s++;
		i = 0;
		while (s[i] && s[i] != c)
		{
			i = skip_quotes(s, i);
			i++;
		}
		tab[j] = ft_substr(s, 0, i);
		s += i;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
