/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:26:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/09 10:46:46 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

t_vec4	add_ambient_value(t_scene *img)
{
	t_vec4	ambient;
	t_vec4	ambient_color;

	ambient_color = int_to_vec4(img->ambient_light.color);
	normalize_color_vec4(&ambient_color);
	ambient = multiply_vec4_float(ambient_color, img->ambient_light.ratio);
	// ambient = multiply_vec4(img->hit_data.color, ambient);
	printf("after ambient r: %f, g: %f, b: %f\n", ambient.r, ambient.g, ambient.b);
	return (ambient);
}

float	get_brightness(t_scene *img, int i, t_hit *hit)
{
	float	result;
	t_vec3	light_direction;

	printf("light ratio is: %f\n", img->light_sources[i].ratio);
	printf("light pos is: %f, %f, %f\n", img->light_sources[i].pos.x, img->light_sources[i].pos.y, img->light_sources[i].pos.z);
	light_direction = vec3_sub(img->light_sources[i].pos, hit->pos);
	light_direction = vec3_normalize(light_direction);
	result = (dot_vector3(img->hit_data.normal, light_direction) \
	* img->light_sources[i].ratio);
	if (result < 0.0)
		result = 0.0;
	return (result);
}
