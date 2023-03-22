/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:52:49 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/13 18:06:21 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* returns a new string by extracting len characters from s *
 * starting from start. the memory for the new string is    *
 * obtained with malloc.                                    */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if (start >= i || len <= 0)
	{
		str = ft_strdup("");
		return (str);
	}
	if (i < (start + len))
		str = malloc(sizeof(char) * (i - start + 1));
	else
		str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (i < (start + len))
		ft_strlcpy(str, (s + start), (i - start + 1));
	else
		ft_strlcpy(str, (s + start), (len + 1));
	return (str);
}
