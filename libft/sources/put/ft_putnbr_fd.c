/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 07:19:59 by rmakinen          #+#    #+#             */
/*   Updated: 2022/11/15 08:08:24 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb < -2147483648 || nb > 2147483647)
		return ;
	if (nb == -2147483648)
	{
		nb = 147483648;
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
	}
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		ft_putchar_fd(nb + 48, fd);
	}
}
