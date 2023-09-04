/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 07:53:29 by rmakinen          #+#    #+#             */
/*   Updated: 2023/01/05 14:04:43 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_specifier(const char *str, va_list args)
{
	int	len;

	len = 0;
	str++;
	if (*str == '%')
		len += print_percentage();
	else if (*str == 'c')
		len += print_putchar(va_arg(args, int));
	else if (*str == 's')
		len += print_putstring(va_arg(args, const char *));
	else if (*str == 'i' || *str == 'd')
		len += print_putnum(va_arg(args, int));
	else if (*str == 'u')
		len += print_unsigned(va_arg(args, unsigned int));
	else if (*str == 'p')
		len = print_pointer(va_arg(args, void *));
	else if (*str == 'x')
		len += print_puthexlow(va_arg(args, unsigned int));
	else if (*str == 'X')
		len += print_puthexhi(va_arg(args, unsigned int));
	else
		len += print_putchar(*str);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	int		i;
	va_list	args;

	va_start(args, format);
	len = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			len += check_specifier(&format[i], args);
			i = i + 2;
		}
		else if (format[i] == '%' && format[i + 1] == '\0')
			i++;
		else
		{
			len += print_putchar(format[i]);
			i++;
		}
	}
	va_end(args);
	return (len);
}
