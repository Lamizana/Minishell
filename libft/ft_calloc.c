/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:57:47 by vsaura            #+#    #+#             */
/*   Updated: 2023/01/13 16:27:14 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* allocates memory for an array of nmemb elements of size   *
 * bytes each and returns a pointer to the allocated memory. *  
 * The memory is set to zero.                                *
 * if nmemb or size is 0 calloc returns NULL.                *
 * if the multiplication of nmemb by size would result in    *
 * an int overflow, calloc returns an error.                 */

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (nmemb == 0 || size == 0)
	{
		arr = malloc(0);
		return (arr);
	}
	if (nmemb * size == 1 && size != 1)
		return (0);
	if ((nmemb * size) / nmemb != size)
		return (0);
	arr = malloc(size * nmemb);
	if (!arr)
		return (NULL);
	ft_memset(arr, 0, size * nmemb);
	return (arr);
}
