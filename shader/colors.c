/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 06:24:44 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/24 12:59:55 by rmakinen         ###   ########.fr       */
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
	img->hit_data.specular = get_specular(img, hit);
	light_color = int_to_vec4(img->light_sources.color);
	vec4_normalize_color(&light_color);
	light_color = vec4_multiply_float(light_color, img->hit_data.brightness);
	return (light_color);
}

t_vec4	get_pixel_color(t_scene *img, t_hit *hit)
{
	t_vec4	color;
	t_vec4	color2;
	t_vec4	light_color;

	get_object_basecolor(img);
	init_color(&color);
	init_color(&light_color);
	if (img->hit_data.is_in_shadow == 1)
	{
		color = add_ambient_value(img);
		printf("ambient in shadow %f, %f, %f, %f\n", color.alpha, color.r, color.g, color.b);
		return (color);
	}
	light_color = get_light_values(img, hit);
	color = vec4_add_float(vec4_multiply(img->hit_data.color, light_color), (img->hit_data.specular * SPECULAR));
	color2 = add_ambient_value(img);
	printf("hit+light+spec  %f, %f, %f\n", color.r, color.g, color.b);
	printf("ambient in light  %f, %f, %f\n", color2.r, color2.g, color2.b);
	vec4_add(color, color2);
	return (color);
}
