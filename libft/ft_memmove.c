/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:15:28 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/10 15:00:11 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* copies n bytes from src to dst *
 * the memory areas may overlap   *
 * the bytes in src are first     *
 * copied in a tmp array          *
 * and then from the tmp array to *
 * dest                           */

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dst;
	const char	*srce;

	dst = dest;
	srce = src;
	if (dest == NULL && src == NULL)
		return (0);
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			dst[i - 1] = srce[i - 1];
			i--;
		}
	}
	else
		dst = ft_memcpy(dest, src, n);
	return (dst);
}
