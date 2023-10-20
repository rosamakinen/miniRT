/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:26:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/20 15:33:46 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec4	add_ambient_value(t_scene *img)
{
	t_vec4	ambient;
	t_vec4	ambient_color;

	ambient_color = int_to_vec4(img->ambient_light.color);
	vec4_normalize_color(&ambient_color);
	ambient = vec4_multiply_float(ambient_color, img->ambient_light.ratio);
	return (ambient);
}

float	get_specular(t_scene *img, t_hit *hit)
{
	t_vec3	light_direction;
	t_vec3	half_direction;
	float	specular;
	float	specular_angle;

	light_direction = vec3_sub(img->light_sources.pos, hit->pos);
	light_direction = vec3_normalize(light_direction);

	// this is blinn phong
	half_direction = vec3_add(light_direction, vec3_negative(img->camera.norm_vector));
	half_direction = vec3_normalize(half_direction);
	specular_angle = fmaxf(dot_vector3(half_direction, img->hit_data.normal), 0.0);
	specular = powf(specular_angle, 40);
	return (specular);
}

float	get_brightness(t_scene *img, t_hit *hit)
{
	float	result;
	t_vec3	light_direction;

	light_direction = vec3_sub(img->light_sources.pos, hit->pos);
	light_direction = vec3_normalize(light_direction);
	result = (dot_vector3(img->hit_data.normal, light_direction) \
	* img->light_sources.ratio);
	if (result < TINY_VALUE)
		result = 0.0;
	return (result);
}
