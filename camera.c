/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:18:33 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/14 11:03:42 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

t_vec3	vec_sub(t_vec3 vector1, t_vec3 vector2)
{
	t_vec3	result;

	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return (result);
}

void	get_ray_direction(t_camera *cam, t_scene *img, int img_x, int img_y)
{
	float normal_x;
	float normal_y;

	if (img_x < img->width / 2)
		normal_x = img->width / 2 - img_x;
	else
		normal_x = img_x - img->width / 2;

	if (img_y > img->height / 2)
		normal_y = img->height / 2 - img_y;
	else
		normal_y = img_y - img->height / 2;

	cam->norm_coord.x = normal_x;
	cam->norm_coord.y = normal_y;
}
