/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:13:57 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/09/14 07:42:40 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

//these functions undenibly look scary and intimidating but they do a similar
// logic. They both skip certain characters using the skip_chars() func
// after skipping, they check if the next incoming input looks like a valid
// number input. If it does, they grab the float and continue forward.
// I had to pass pointers to index and do a lot of referencing and derefrencing
// to allow the parser to keep up with the current parsing index :c

//	if (is_digit_mod(str[*index], 1, 1))
//		return (EXIT_FAILURE);
// ^ these checks are to prevent the input from being for example +-10.0,3,4
int	get_3d_coordindate(t_vec3 *coordinate, const char *str, int *index)
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

	num = (char *)color; // this a bit tricky but it basically allows us to use one int to store color and brightness.
	//Because of endianes an int is 4 bytes where casted to an char array
	// arr[0]= B value, arr[1]= G value, arr[2] = R value, arr[3] = Brightness
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

int	skip_chars(const char *skippable, int index, const char *str)
{
	int	i;
	int	j;
	int	found;

	i = index;
	while (str[i])
	{
		j = 0;
		found = 0;
		while (skippable[j])
		{
			if (str[i] == skippable[j])
				found = 1;
			j++;
		}
		if (!found)
			return (i);
		i++;
	}
	return (i);
}

int	get_degrees(t_degrees *dst, const char *str, int *index)
{

	*index = skip_chars(" ", *index, str);
	if (!str[*index] || str[*index] == '\n' || !is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	*dst = ft_atoi_mod(str, index);
	if (is_digit_mod(str[*index], 1, 1))
		return (EXIT_FAILURE);
	if (*dst < 0  || *dst > 180) //ratio must be between [0-180] inclusive
		return (EXIT_FAILURE);
	*index = skip_chars(" ,", *index, str);
	return (EXIT_SUCCESS);
}



int	get_3d_normal_vector(t_vec3 *coordinate, const char *str, int *index)
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
	if (fabs(coordinate->x) > 1 || fabs(coordinate->y) > 1 || fabs(coordinate->z) > 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
