/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:16:17 by vsaura            #+#    #+#             */
/*   Updated: 2022/10/13 14:26:32 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* copies n bytes from src to dst */

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst;
	unsigned const char	*srce;

	dst = dest;
	srce = src;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		dst[i] = srce[i];
		i++;
	}
	return ((void *)dst);
}
