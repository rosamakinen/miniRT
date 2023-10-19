/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:13:57 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/19 16:50:25 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	check_zero_vector(t_vec3 *my_vector)
{
	if (distance(*my_vector) <= TINY_VALUE)
		return (1);
	return (EXIT_SUCCESS);
}

int	get_vec3(t_vec3 *coordinate, const char *str, int *index)
{
	*index = skip_chars(" ", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	coordinate->x = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	coordinate->y = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	coordinate->z = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ", *index, str);
	return (EXIT_SUCCESS);
}

int	get_float(float *dst, const char *str, int *index)
{
	*index = skip_chars(" ", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	*dst = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	if (*dst < 0)
		return (EXIT_FAILURE);
	*index = skip_chars(" ", *index, str);
	return (EXIT_SUCCESS);
}

int	get_degrees(t_degrees *dst, const char *str, int *index)
{
	*index = skip_chars(" ", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	*dst = ft_atoi_mod(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	if (*dst < 0 || *dst > 180)
		return (EXIT_FAILURE);
	*index = skip_chars(" ", *index, str);
	return (EXIT_SUCCESS);
}

int	get_3d_normal_vector(t_vec3 *coordinate, const char *str, int *index)
{
	*index = skip_chars(" ", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	coordinate->x = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	coordinate->y = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	if (check_index_error(str, index))
		return (EXIT_FAILURE);
	coordinate->z = ft_atof(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*index = skip_chars(" ", *index, str);
	if (fabs(coordinate->x) > 1 || fabs(coordinate->y) > 1
		|| fabs(coordinate->z) > 1)
		return (EXIT_FAILURE);
	return (check_zero_vector(coordinate));
}
