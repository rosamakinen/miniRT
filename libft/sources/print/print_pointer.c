/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:00:46 by rmakinen          #+#    #+#             */
/*   Updated: 2023/01/05 10:39:32 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_len(unsigned long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= 16)
	{
		n = n / 16;
		len++;
	}
	return (len + 1);
}

static void	ft_puthex(unsigned long long nb)
{
	if (nb >= 16)
	{
		ft_puthex(nb / 16);
		ft_puthex(nb % 16);
	}
	else
	{
		if (nb <= 9)
		{
			ft_putchar_fd((nb + '0'), 1);
		}
		else
		{
			ft_putchar_fd((nb - 10 + 'a'), 1);
		}
	}
}

int	print_pointer(void *p)
{
	int	len;

	write(1, "0x", 2);
	len = hex_len((unsigned long long)p);
	ft_puthex((unsigned long long)p);
	return (len + 2);
}
