/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 07:56:33 by rmakinen          #+#    #+#             */
/*   Updated: 2023/01/13 09:14:18 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int	ft_printf(const char *format, ...);
int	check_specifier(const char *str, va_list args);
int	print_putchar(char c);
int	print_percentage(void);
int	print_putstring(const char *str);
int	print_putnum(int a);
int	print_unsigned(int nb);
int	print_puthexlow(unsigned int x);
int	print_puthexhi(unsigned int x);
int	print_pointer(void *p);

#endif
