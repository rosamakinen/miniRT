/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:26:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/23 06:40:49 by rmakinen         ###   ########.fr       */
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
	t_vec3	reflect_direction;
	t_vec3	half_direction;
	float	specular;
	float	specular_angle;

	reflect_direction = vec3_sub(img->light_sources.pos, hit->pos);
	reflect_direction = vec3_normalize(reflect_direction);
	half_direction = vec3_add(reflect_direction, vec3_negative(img->camera.not_normalized_norm_vector));
	half_direction = vec3_normalize(half_direction);
	specular_angle = fmaxf(dot_vector3(half_direction, img->hit_data.normal), 0.0);
	specular = powf(specular_angle, 80);
	specular = specular / 1.5f;
	return (specular);
}

    // vec3 halfDir = normalize(lightDir + viewDir);
    // float specAngle = max(dot(halfDir, normal), 0.0);
    // specular = pow(specAngle, shininess);

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
