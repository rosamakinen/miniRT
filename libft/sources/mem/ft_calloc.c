/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 08:13:46 by rmakinen          #+#    #+#             */
/*   Updated: 2023/01/12 12:35:50 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
