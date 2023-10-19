/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_putnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 08:33:17 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/19 16:21:33 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	print_putnum(int a)
{
	int		len;
	char	*str;

	str = ft_itoa(a);
	print_putstring(str);
	len = ft_strlen(str);
	free(str);
	return (len);
}
