/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:18:33 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/14 08:10:14 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"
#include "./includes/vectors.h"
#include <math.h>

t_vec3	vec_sub(t_vec3 vector1, t_vec3 vector2)
{
	t_vec3	result;

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
	static int	i = 0;

	normal_x = (((2.0f * (double)x) / img->width - 1.0f) * tan(M_PI/4));
	normal_y = (1.0f - (2.0f * (double)y) / img->height) * tan(M_PI/4);

	if (i++ == 0)
		printf("%f, %f, %f\n", cam->pos.x, cam->pos.y, cam->pos.z);
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 2000;
	cam->norm_coord = vec_sub((t_vec3){normal_x, normal_y, -1}, cam->pos); //vec3 from the normalized x & y
}
