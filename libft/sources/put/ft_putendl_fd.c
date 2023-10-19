/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 07:20:47 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/19 16:22:02 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s == 0)
		return ;
	while (*s != '\0')
	{
		write (fd, s, 1);
		s++;
	}
	write (fd, "\n", 1);
}
