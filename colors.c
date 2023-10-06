/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 06:24:44 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/06 10:40:46 by rmakinen         ###   ########.fr       */
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
t_vec4	get_light_values(t_scene *img, int i, t_hit *hit)
{
	t_vec4	light_color;

	img->hit_data.brightness = get_brightness(img, img->light_sources[i], hit);
	light_color = int_to_vec4(img->light_sources[i].color);
	normalize_color_vec4(&light_color);
	light_color = multiply_vec4_float(light_color, img->hit_data.brightness);
	return (light_color);
}

t_vec4	get_pixel_color(t_scene *img, t_hit *hit)
{
	t_vec4	color;
	t_vec4	light_color;
	int		i;

	i = 0;
	get_object_basecolor(img);
	init_color(&color);
	while (i < img->light_count)
	{
		light_color = get_light_values(img, i, hit);
		printf("light col at start r %f, g %f, b %f\n", light_color.r, light_color.g, light_color.b);
		img->hit_data.color = multiply_vec4(img->hit_data.color, light_color);
		color = add_vec4(img->hit_data.color, color);
		printf("hit col at start r %f, g %f, b %f\n", color.r, color.g, color.b);
		i++;
	}
	color = add_vec4(img->hit_data.color, add_ambient_value(img));
	printf("hit col at end r %f, g %f, b %f\n\n", color.r, color.g, color.b);
	return (color);
}
