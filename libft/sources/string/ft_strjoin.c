/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 07:23:03 by rmakinen          #+#    #+#             */
/*   Updated: 2022/11/17 08:13:26 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

static void	ft_addstring(char *new, char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	n_size;

	if (s1 == 0 || s2 == 0)
		return (0);
	n_size = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)ft_calloc(n_size + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_addstring(new, s1, s2);
	return (new);
}
