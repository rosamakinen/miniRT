/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:26:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/25 07:55:09 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

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

	light_direction = vec3_sub(img->light_sources.pos, hit->pos);// subtracting light pos, hit pos
	light_direction = vec3_normalize(light_direction);
	light_direction = negative_vector(light_direction);
	result = dot_vector3(img->hit_data.normal, light_direction);
	return (result);
}
