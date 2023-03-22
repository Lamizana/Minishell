/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 17:53:08 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/06 15:36:13 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* appends src to the end of dest, NUL terminating the *
 * result, then returns the length of dest + the       *
 * lenght of src                                       */

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if ((dst == NULL || src == NULL) && size == 0)
		return (0);
	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (size == 0 || i >= size)
		return (size + j);
	j = 0;
	while (src[j] && (i + j) < size - 1)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	j = ft_strlen(src);
	return (i + j);
}
