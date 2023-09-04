/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_putstring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:17:40 by rmakinen          #+#    #+#             */
/*   Updated: 2023/01/04 16:02:43 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_putstring(const char *str)
{
	int	len;
	int	i;

	if (!str)
	{
		write (1, "(null)", 6);
		i = 6;
		return (i);
	}
	len = 0;
	while (*str != '\0')
	{
		print_putchar(*str);
		str++;
		len++;
	}
	return (len);
}
