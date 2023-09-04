/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_puthexlow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 09:09:43 by rmakinen          #+#    #+#             */
/*   Updated: 2023/01/04 16:27:40 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	hex_len(unsigned int n)
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

static void	ft_puthex(unsigned int nb)
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

int	print_puthexlow(unsigned int x)
{
	int		len;

	len = hex_len(x);
	ft_puthex(x);
	return (len);
}
