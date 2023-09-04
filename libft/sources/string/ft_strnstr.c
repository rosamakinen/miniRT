/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 07:37:00 by rmakinen          #+#    #+#             */
/*   Updated: 2022/11/16 15:08:56 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	if (needle[0] == '\0')
		return (&hay[i]);
	while (i < len && hay[i] != '\0')
	{
		j = 0;
		if (hay[i] == needle[0])
		{
			while (hay[i + j] == needle[j] && (i + j) < len \
			&& needle[j] != '\0')
				j++;
			if (needle[j] == '\0')
				return (&hay[i]);
		}
		i++;
	}
	return (0);
}
