/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 06:24:44 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/11 12:29:38 by rmakinen         ###   ########.fr       */
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
	while (i < img->light_count)
	{
		img->hit_data.brightness = get_brightness(img, i, hit);
		img->hit_data.specular = get_specular(img, i, hit);
		light_color = int_to_vec4(img->light_sources[i].color);
		normalize_color_vec4(&light_color);
		light_color = multiply_vec4_float(light_color, img->hit_data.brightness);
		final_light = add_vec4(final_light, light_color);
		i++;
	}
	return (final_light);
}

t_vec4	get_pixel_color(t_scene *img, t_hit *hit)
{
	t_vec4	color;
	t_vec4	light_color;

	get_object_basecolor(img);
	init_color(&color);
	light_color = get_light_values(img, hit);
	img->hit_data.color = multiply_vec4(img->hit_data.color, light_color);
	color = add_vec4(add_vec4_float(img->hit_data.color, img->hit_data.specular), add_ambient_value(img));
	printf("final color : r %f, g %f, b %f\n", color.r, color.g, color.b);
	return (color);
}
