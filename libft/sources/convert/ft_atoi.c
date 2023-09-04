/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:58:55 by rmakinen          #+#    #+#             */
/*   Updated: 2023/03/27 11:12:00 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	i;
	long	symbol;
	long	result;

	i = 0;
	symbol = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\f' || \
	str[i] == '\r' || str[i] == '\n' || str[i] == ' ' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		symbol = -symbol;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (result * symbol > 2147483647)
			return (-1);
		if (result * symbol < -2147483648)
			return (-1);
		else
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return ((int)result * (int)symbol);
}
