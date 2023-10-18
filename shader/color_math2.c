/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:16:08 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/18 10:43:38 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec4	vec4_multiply_float(t_vec4 color, float value)
{
	t_vec4	temp_color;

	temp_color.alpha = 1;
	temp_color.r = color.r * value;
	temp_color.g = color.g * value;
	temp_color.b = color.b * value;
	temp_color = vec4_clamp(temp_color);
	return (temp_color);
}

t_vec4	vec4_multiply(t_vec4 color, t_vec4 multiplier)
{
	t_vec4	temp_color;

	temp_color.alpha = 1;
	temp_color.r = color.r * multiplier.r;
	temp_color.g = color.g * multiplier.g;
	temp_color.b = color.b * multiplier.b;
	temp_color = vec4_clamp(temp_color);
	return (temp_color);
}

t_vec4	vec4_add(t_vec4 color, t_vec4 added)
{
	t_vec4	temp_color;

	temp_color.alpha = 1;
	temp_color.r = color.r + added.r;
	temp_color.g = color.g + added.g;
	temp_color.b = color.b + added.b;
	temp_color = vec4_clamp(temp_color);
	return (temp_color);
}

t_vec4	vec4_add_float(t_vec4 color, float value)
{
	t_vec4	temp_color;

	temp_color.alpha = 1;
	temp_color.r = color.r + value;
	temp_color.g = color.g + value;
	temp_color.b = color.b + value;
	temp_color = vec4_clamp(temp_color);
	return (temp_color);
}
