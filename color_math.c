/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:23:39 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/03 09:19:00 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

t_vec4	int_to_vec4(int color)
{
	t_vec4	vec_color;

	vec_color.alpha = 1.0;
	vec_color.r = (float)((color >> 16) & 0xFF);
	vec_color.g = (float)((color >> 8) & 0xFF);
	vec_color.b = (float)(color & 0xFF);
	//printf("alpha %f, red %f, green %f, blue %f\n", vec_color.alpha, vec_color.r, vec_color.g, vec_color.b);
	return (vec_color);
}

int	normalized_vec4_to_int(t_vec4 color)
{
	int32_t	red;
	int32_t	green;
	int32_t	blue;
	int32_t	alpha;

	//printf("r: %f, g: %f, b: %f\n", color.r, color.g, color.b);
	alpha = 1;
	red = (color.r * 255);
	green = (color.g * 255);
	blue = (color.b * 255);
	//printf("alpha %i, red %i, green %i, blue %i\n", alpha, red, green, blue);
	return ((alpha << 24) | (red << 16) | (green << 8) | blue);
}

void	normalize_color_vec4(t_vec4 *color)
{
	color->alpha = 1;
	color->r = color->r / 255.0;
	color->g = color->g / 255.0;
	color->b = color->b / 255.0;
}

t_vec4	clamp_vec4(t_vec4 color)
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
	else
		return (vec_color);
}

