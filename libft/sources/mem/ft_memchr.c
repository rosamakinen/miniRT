/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:26:42 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/19 16:20:30 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	if (i < n)
	{
		while (i < n)
		{
			if (((unsigned char *)s)[i] == (unsigned char) c)
			{
				ptr = &((unsigned char *)s)[i];
				return (ptr);
			}
			i++;
		}
	}
	return (0);
}
