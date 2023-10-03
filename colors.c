/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 06:24:44 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/03 06:22:13 by rmakinen         ###   ########.fr       */
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
	// int test_color;

	// test_color = 0xFF00FF;
	// img->hit_data.color = uint_to_normalized_vec4(test_color);
	get_object_basecolor(img); //is already normalized
	printf("hit col at start r %f, g %f, b %f\n", img->hit_data.color.r, img->hit_data.color.g, img->hit_data.color.b);
	// img->hit_data.color = transfer_pos_to_color(hit);
	img->hit_data.brightness = get_brightness(img, hit); // calculated from normal and light directiom
	printf("brightness : %f\n", img->hit_data.brightness);
	color = multiply_vec4_float(img->hit_data.color, img->hit_data.brightness);
	printf("hit col at end r %f, g %f, b %f\n", color.r, color.g, color.b);
	color = add_vec4(color, add_ambient_value(img));
	return (color);
}
