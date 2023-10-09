/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 06:24:44 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/09 10:57:38 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void	init_color(t_vec4 *color)
{
	color->alpha = 1;
	color->r = 0;
	color->g = 0;
	color->b = 0;
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
		printf("brightness %f\n", img->hit_data.brightness);
		light_color = int_to_vec4(img->light_sources[i].color);
		normalize_color_vec4(&light_color);
		light_color = multiply_vec4_float(light_color, img->hit_data.brightness);
		final_light = add_vec4(final_light, light_color);
		printf("final_light r %f, g %f, b %f\n", final_light.r, final_light.g, final_light.b);
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
	printf("light col at start r %f, g %f, b %f\n", light_color.r, light_color.g, light_color.b);

	img->hit_data.color = multiply_vec4(img->hit_data.color, light_color);
	color = add_vec4(img->hit_data.color, add_ambient_value(img));
	printf("hit col at end r %f, g %f, b %f\n\n", color.r, color.g, color.b);
	return (color);
}
