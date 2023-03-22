/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 12:09:43 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/13 18:33:52 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/* returns an int less than, equal to or greater than zero *
 * if the first n bytes of s1 is found to be less than,    *
 * equal to or greater than the first n bytes of s2        */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
