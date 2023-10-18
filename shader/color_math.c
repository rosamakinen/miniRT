/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:23:39 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/18 10:43:30 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec4	int_to_vec4(int color)
{
	t_vec4	vec_color;

	vec_color.alpha = 1.0;
	vec_color.r = (float)((color >> 16) & 0xFF);
	vec_color.g = (float)((color >> 8) & 0xFF);
	vec_color.b = (float)(color & 0xFF);
	return (vec_color);
}

int	vec4_normalized_to_int(t_vec4 color)
{
	int32_t	red;
	int32_t	green;
	int32_t	blue;
	int32_t	alpha;

	alpha = 1;
	red = (color.r * 255);
	green = (color.g * 255);
	blue = (color.b * 255);
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

void	vec4_normalize_color(t_vec4 *color)
{
	color->alpha = 1;
	color->r = color->r / 255.0;
	color->g = color->g / 255.0;
	color->b = color->b / 255.0;
}

t_vec4	vec4_clamp(t_vec4 color)
{
	t_vec4	temp_color;

	temp_color.alpha = 1;
	temp_color.r = clamp_color(color.r);
	temp_color.g = clamp_color(color.g);
	temp_color.b = clamp_color(color.b);
	return (temp_color);
}

float	clamp_color(float vec_color)
{
	if (vec_color > 1)
		return (1.0);
	else if (vec_color < 0)
		return (0.0);
	return (vec_color);
}
