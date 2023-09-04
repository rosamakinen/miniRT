/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:17:08 by rmakinen          #+#    #+#             */
/*   Updated: 2022/11/26 14:40:00 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (s[counter] != '\0')
	{
		counter++;
	}
	return (counter);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		j;
	size_t	n_size;

	if (s1 == 0 || s2 == 0)
		return (0);
	n_size = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(n_size + 1 * sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		new[i++] = s2[j++];
	new[i] = '\0';
	return (new);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		((char *)s)[i] = '\0';
			i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	if (count == 0 || size == 0)
	{
		p = malloc(1);
		if (p == 0)
			return (0);
		return (p);
	}
	if (count * size / size != count)
		return (0);
	p = malloc(count * size);
	if (p == 0)
		return (0);
	ft_bzero (p, count * size);
	return (p);
}
