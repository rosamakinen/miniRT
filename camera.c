/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:18:33 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/13 12:44:45 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"
#include "./includes/vectors.h"
#include <math.h>

typedef struct s_ray
{
	t_vec3 pos;
	t_vec3 dir;
} t_ray;


t_3D_vector	vec_sub(t_vec3 vector1, t_3D_coordinate vector2)
{
	t_3D_vector	result;

	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return (result);
}

//use floats instead of ints
void	get_ray_direction(t_camera *cam, t_scene *img, int x, int y)
{
	float normal_x;
	float normal_y;

	normal_x = (((2.0f * (double)x) / img->width - 1.0f) * tan(M_PI/4));
	normal_y = (1.0f - (2.0f * (double)y) / img->height) * tan(M_PI/4);

	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 2000;
	cam->norm_vector = vec_sub((t_vec3){normal_x, normal_y, -1}, cam->pos); //vec3 from the normalized x & y
}
