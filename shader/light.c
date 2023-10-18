/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:26:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/18 11:03:23 by rmakinen         ###   ########.fr       */
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

t_vec4	get_white_light(void)
{
	t_vec4	white;

	white.alpha = 1;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	return (white);
}

float	get_brightness(t_scene *img, t_hit *hit)
{
	float	result;
	t_vec3	light_direction;

	light_direction = vec3_sub(img->light_sources.pos, hit->pos);
	light_direction = vec3_normalize(light_direction);
	result = (dot_vector3(img->hit_data.normal, light_direction) \
	* img->light_sources.ratio);
	if (result < 0)
		result = 0.0;
	return (result);
}
