/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 06:24:44 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/03 07:44:28 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

// t_vec4	transfer_pos_to_color(t_hit *hit)
// {
// 	t_vec4 temp_col;

// 	temp_col.alpha = 1;
// 	hit->pos = vec3_normalize(hit->pos);
// 	temp_col.r = hit->pos.x;
// 	temp_col.g = hit->pos.y;
// 	temp_col.b = hit->pos.z;

// 	return (temp_col);
// }

t_vec4	get_pixel_color(t_scene *img, t_hit *hit)
{
	t_vec4	color;
	t_vec4	light_color;

	get_object_basecolor(img); //is already normalized
	light_color = int_to_vec4(img->light_sources.color);
	normalize_color_vec4(&light_color);
	printf("hit col at start r %f, g %f, b %f\n", img->hit_data.color.r, img->hit_data.color.g, img->hit_data.color.b);
	// img->hit_data.color = transfer_pos_to_color(hit);
	img->hit_data.brightness = get_brightness(img, hit); // calculated from normal and light directiom
	light_color = multiply_vec4_float(light_color, img->hit_data.brightness);
	printf("brightness : %f\n", img->hit_data.brightness);
	color = multiply_vec4(img->hit_data.color, light_color);
	color = add_vec4(color, add_ambient_value(img));
	printf("hit col at end r %f, g %f, b %f\n", color.r, color.g, color.b);
	return (color);
}
