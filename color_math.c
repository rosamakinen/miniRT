/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:23:39 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/25 11:11:42 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

int	normalized_vec4_to_int(t_vec4 color)
{
	int32_t	red;
	int32_t	green;
	int32_t	blue;
	int32_t	alpha;

	alpha = 1;
	red = color.r * 255;
	green = color.g * 255 ;
	blue = color.b * 255;
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

void	normalize_argb(t_vec4 *color)
{
	color->alpha = 1;
	color->r = color->r / 255.0;
	color->g = color->g / 255.0;
	color->b = color->b / 255.0;
}

t_vec4	int_to_normalized_vec4(int color)
{
	t_vec4	vec_color;

	vec_color.alpha = 1;
	vec_color.r = ((color >> 16) & 0xFF) / 255.0f;
	vec_color.g = ((color >> 8) & 0xFF) / 255.0f;
	vec_color.b = (color & 0xFF) / 255.0f;

	return (vec_color);
}

t_vec4	multiply_vec4_value(t_vec4 color, float value)
{
	t_vec4	temp_color;

	temp_color.alpha = 1;
	temp_color.r = color.r * value;
	temp_color.g = color.g * value;
	temp_color.b = color.b * value;

	return (temp_color);
}
