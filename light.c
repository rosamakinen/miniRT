/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:26:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/03 07:36:16 by rmakinen         ###   ########.fr       */
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

t_vec3	negative_vector(t_vec3 light_direction)
{
	t_vec3	temp;

	temp.x = -light_direction.x;
	temp.y = -light_direction.y;
	temp.z = -light_direction.z;
	return (temp);
}

float	get_brightness(t_scene *img, t_hit *hit)
{
	float	result;
	t_vec3	light_direction;

	light_direction = vec3_sub(img->light_sources.pos, hit->pos); // subtracting light pos, hit pos
	light_direction = vec3_normalize(light_direction);
	//light_direction = negative_vector(light_direction); // not needed after all?
	result = (dot_vector3(img->hit_data.normal, light_direction) * img->light_sources.ratio);
	if (result < 0)
	{
		result = 0.0;
	}
	return (result);
}
