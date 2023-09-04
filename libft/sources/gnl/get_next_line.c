/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:17:13 by rmakinen          #+#    #+#             */
/*   Updated: 2022/11/26 14:51:05 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

static char	*gnl_join(char *safe, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(safe, buffer);
	free(safe);
	return (temp);
}

static char	*clean_the_storage(char *safe)
{
	char	*temp;
	size_t	start;
	size_t	end;
	int		i;

	start = 0;
	while (safe[start] && safe[start] != '\n')
		start++;
	if (!safe[start])
	{
		free(safe);
		return (NULL);
	}
	end = ft_strlen(safe);
	temp = ft_calloc((end - start + 1), sizeof(char));
	if (!temp)
		return (NULL);
	start++;
	i = 0;
	while (safe[start])
		temp[i++] = safe[start++];
	free(safe);
	return (temp);
}

static char	*save_the_line(char *safe)
{
	char	*new;
	int		len;

	len = 0;
	if (!safe[len])
		return (NULL);
	while (safe[len] && safe[len] != '\n')
		len++;
	new = ft_calloc((len + 2), sizeof(char));
	if (!new)
		return (NULL);
	len = 0;
	while (safe[len] && safe[len] != '\n')
	{
		new[len] = safe[len];
		len++;
	}
	if (safe[len] && safe[len] == '\n')
		new[len++] = '\n';
	return (new);
}

static char	*search_for_line(char *safe, int fd)
{
	int		bytes_read;
	char	*buffer;

	if (!safe)
	{
		safe = malloc(1);
		safe[0] = '\0';
	}
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		safe = gnl_join(safe, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (safe);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*safe;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	safe = search_for_line(safe, fd);
	if (!safe)
		return (NULL);
	line = save_the_line(safe);
	safe = clean_the_storage(safe);
	return (line);
}
