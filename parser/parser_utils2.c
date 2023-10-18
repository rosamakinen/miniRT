/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:32:50 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/18 12:39:46 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	get_color(t_color *color, const char *str, int *index)
{
	char	*num;

	num = (char *)color;
	*index = skip_chars(" ", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	num[2] = ft_atouint8(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	num[1] = ft_atouint8(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	num[0] = ft_atouint8(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ", *index, str);
	return (EXIT_SUCCESS);
}

int	check_index_error(const char *str, int *index)
{
	if (!str[*index])
		return (EXIT_FAILURE);
	else if (str[*index] == '\n')
		return (EXIT_FAILURE);
	else if (!is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
