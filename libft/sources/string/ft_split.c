/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 07:44:15 by rmakinen          #+#    #+#             */
/*   Updated: 2023/03/27 10:36:57 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static size_t	word_length(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s != c)
		{
			len++;
			s++;
		}
		else
			return (len);
	}
	return (len);
}

static	char	*ft_strcopy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	while (i < len)
	{
		if (i < slen)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		i++;
	}
	return (dst);
}

static char	**add_word(char **s_array, const char *s, char c, size_t array_pos)
{
	size_t	count;
	size_t	p;

	p = 0;
	while (p < array_pos && s_array)
	{
		while (*s != '\0' && *s == c)
			s++;
		count = word_length(&*s, c);
		s_array[p] = malloc(sizeof(**s_array) * (count + 1));
		if (!s_array[p])
		{
			while (p-- > 0)
				free (s_array[p]);
			free (s_array);
			return (NULL);
		}
		ft_strcopy(s_array[p], &(*s), count);
		s_array[p][count] = '\0';
		while (*s != '\0' && *s != c)
			s++;
		p++;
	}
	s_array[p] = NULL;
	return (s_array);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**s_array;
	int		i;

	i = 0;
	if (!s)
		return (0);
	count = word_count(s, c);
	s_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!(s_array))
		return (NULL);
	s_array = add_word(s_array, s, c, count);
	return (s_array);
}
