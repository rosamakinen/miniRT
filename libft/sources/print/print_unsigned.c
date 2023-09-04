/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 08:09:01 by rmakinen          #+#    #+#             */
/*   Updated: 2023/01/04 16:24:00 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	n_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n < 0)
		len++;
	if (n == 0)
		return (1);
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*check_num(long num, int i, char *str)
{
	if (num == 0)
	{
		str[0] = 48;
		return (str);
	}
	while (num)
	{
		str[i - 1] = (num % 10) + 48;
		num = num / 10;
		i--;
	}
	return (str);
}

static char	*ft_uitoa(int n)
{
	char			*str;
	int				i;
	unsigned int	num;

	i = n_len(n);
	num = n;
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	check_num(num, i, str);
	return (str);
}

int	print_unsigned(int nb)
{
	int		len;
	char	*str;

	str = ft_uitoa(nb);
	len = print_putstring(str);
	free(str);
	return (len);
}
