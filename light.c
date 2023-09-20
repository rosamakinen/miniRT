/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:26:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/20 13:11:28 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

float	get_brightness(t_scene *img, t_hit *hit)
{
	float	brightness;
	t_vec3	light_direction;

	light_direction = vec3_sub(img->light_sources.pos, hit->pos);// subtracting light pos, hit pos
	light_direction = vec3_normalize(light_direction);

	brightness = dot_vector3(img->hit_data.normal, light_direction);
	return (brightness);
}
