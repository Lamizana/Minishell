/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsaura <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:58:33 by vsaura            #+#    #+#             */
/*   Updated: 2023/01/13 16:11:41 by vsaura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_joinfree(char *buf, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(buf, line);
	free(buf);
	return (tmp);
}

// lis la ligne et l'ajoute au buffer

static char	*ft_readlines(int fd, char *buf)
{
	int		nbread;
	char	*line;

	nbread = 1;
	if (!buf)
		buf = ft_calloc(1, 1);
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (nbread > 0)
	{
		nbread = read(fd, line, BUFFER_SIZE);
		if (nbread == -1)
		{
			free (line);
			free (buf);
			return (NULL);
		}
		line[nbread] = 0;
		buf = ft_joinfree(buf, line);
		if (ft_strchr(line, '\n'))
			break ;
	}
	free (line);
	return (buf);
}

// cree la ligne a renvoyer

static char	*ft_makeline(char *buf)
{
	char	*line;
	int		i;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] && buf[i] == '\n')
	{
		line[i] = '\0';
		i++;
	}
	return (line);
}

/* nettoie le buffer en gardant les
 * characteres de la ligne suivante */

static char	*ft_clearbuf(char *buf)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free (buf);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buf) - i + 1), sizeof(char));
	i++;
	while (buf[i])
	{
		line[j] = buf [i];
		i++;
		j++;
	}
	free (buf);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_readlines(fd, buf);
	if (!buf)
		return (NULL);
	line = ft_makeline(buf);
	buf = ft_clearbuf(buf);
	return (line);
}
