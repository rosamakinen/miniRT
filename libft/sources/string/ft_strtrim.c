/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 07:25:10 by rmakinen          #+#    #+#             */
/*   Updated: 2022/11/16 16:46:49 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static int	ft_search(char const *set, char const c)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*copy;
	size_t	end;
	size_t	start;
	int		i;

	if (s1 == 0)
		return (0);
	start = 0;
	while (s1[start] && ft_search(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_search(set, s1[end - 1]))
		end--;
	copy = (char *)malloc(sizeof(char) * (end - start + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (start < end)
		copy[i++] = s1[start++];
	copy[i] = '\0';
	return (copy);
}
