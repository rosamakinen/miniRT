/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 06:24:44 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/16 12:35:28 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

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
	t_vec4	final_light;
	int		i;

	i = 0;
	init_color(&final_light);
	img->hit_data.brightness = get_brightness(img,  hit);
	light_color = int_to_vec4(img->light_sources.color);
	normalize_color_vec4(&light_color);
	light_color = multiply_vec4_float(light_color, img->hit_data.brightness);
	final_light = add_vec4(final_light, light_color);
	return (final_light);
}

t_vec4	get_pixel_color(t_scene *img, t_hit *hit)
{
	t_vec4	color;
	t_vec4	light_color;

	get_object_basecolor(img);
	init_color(&color);
	if (img->hit_data.is_in_shadow == 1)
	{
		color = add_ambient_value(img);
		return (color);
	}
	light_color = get_light_values(img, hit);
	img->hit_data.color = multiply_vec4(img->hit_data.color, light_color);
	color = add_vec4(img->hit_data.color, add_ambient_value(img));
	// printf("color %f, %f, %f\n", color.r, color.g, color.b);
	return (color);
}
