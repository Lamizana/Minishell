/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:53:15 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/05 19:50:42 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* returns a pointer to a new string wich is *
 * a duplicate of s. the memory for the new  *
 * string obtained with malloc               */

char	*ft_strdup(const char *str)
{
	char	*dup;
	int		i;
	int		strlen;

	i = 0;
	strlen = ft_strlen(str);
	dup = malloc(strlen * sizeof(char) + 1);
	if (dup == NULL)
		return (0);
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
