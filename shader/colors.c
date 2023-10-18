/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 06:24:44 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/18 11:10:34 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	init_color(t_vec4 *color)
{
	color->alpha = 1.0;
	color->r = 0.0;
	color->g = 0.0;
	color->b = 0.0;
}

t_vec4	get_light_values(t_scene *img, t_hit *hit)
{
	t_vec4	light_color;

	img->hit_data.brightness = get_brightness(img, hit);
	light_color = int_to_vec4(img->light_sources.color);
	vec4_normalize_color(&light_color);
	light_color = vec4_multiply_float(light_color, img->hit_data.brightness);
	return (light_color);
}

t_vec4	get_pixel_color(t_scene *img, t_hit *hit)
{
	t_vec4	color;
	t_vec4	light_color;

	get_object_basecolor(img);
	init_color(&color);
	init_color(&light_color);
	if (img->hit_data.is_in_shadow == 1)
	{
		color = add_ambient_value(img);
		return (color);
	}
	light_color = get_light_values(img, hit);
	img->hit_data.color = vec4_multiply(img->hit_data.color, light_color);
	color = vec4_add(img->hit_data.color, add_ambient_value(img));
	return (color);
}
