/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:13:57 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/09/13 15:30:43 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_3d_coordindate(t_3D_coordinate *coordinate, const char *str, int *index)
{
	*index = skip_chars(" ", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	coordinate->x = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	coordinate->y = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	coordinate->z = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	return (EXIT_SUCCESS);
}

int	get_float(float *dst, const char *str, int *index)
{
	*index = skip_chars(" ", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 0, 1))
		return (EXIT_FAILURE);
	*dst = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	return (EXIT_SUCCESS);
}

int	get_color(t_color *color, const char *str, int *index)
{
	char	*num;

	num = (char *)color;
	*index = skip_chars(" ", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 0, 1))
		return (EXIT_FAILURE);
	num[2] = ft_atouint8(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 0, 1))
		return (EXIT_FAILURE);
	num[1] = ft_atouint8(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 0, 1))
		return (EXIT_FAILURE);
	num[0] = ft_atouint8(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	return (EXIT_SUCCESS);
}

int	get_degrees(t_degrees *dst, const char *str, int *index)
{
	*index = skip_chars(" ", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*dst = ft_atoi_mod(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	if (*dst < 0 || *dst > 180)
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	return (EXIT_SUCCESS);
}

int	get_3d_normal_vector(t_3D_vector *coordinate, const char *str, int *index)
{
	*index = skip_chars(" ", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	coordinate->x = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	coordinate->y = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	coordinate->z = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (fabs(coordinate->x) > 1 || fabs(coordinate->y) > 1
		|| fabs(coordinate->z) > 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
