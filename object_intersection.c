/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:56:18 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/16 10:26:54 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

int	plane_hit(t_vec3 origin, t_vec3 direction, t_plane plane, t_vec3 *point)
{
	float   angle;
	float   dist;
	t_vec3  plane_to_cam;

	angle = dot_vector3(plane.normal_vector, direction);
	if(fabsf(angle) < 0.0001)
		 return (0);
	plane_to_cam = vec3_sub(plane.point, origin);
	dist = dot_vector3(plane_to_cam, plane.normal_vector) / angle;
	if (dist < 0.0000001)
		 return (0);
	*point = (t_vec3){origin.x + dist * direction.x, origin.y \
		+ dist * direction.y, origin.z + dist * direction.z};
	return (1);
}

int	sphere_hit(const t_sphere *sphere, const t_vec3 ray_start, const t_vec3 direction, t_vec3 *intersection1, t_vec3 *intersection2)
{
	float   a;
	float   b;
	float   c;
	float   discriminant;
	t_vec3  dist;

	dist = vec3_sub(ray_start, sphere->pos);
	a = dot_vector3(direction, direction);
	b = 2.0 * dot_vector3(direction, dist);
	c = dot_vector3(dist, dist) - ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		c = (-b + sqrtf(discriminant)) / (2.0 * a);
		*intersection1 = (t_vec3){ray_start.x + c * direction.x, ray_start.y
				+ c * direction.y, ray_start.z + c * direction.z};
		c = (-b - sqrtf(discriminant)) / (2.0 * a);
		*intersection2 = (t_vec3){ray_start.x + c * direction.x, ray_start.y
				+ c * direction.y, ray_start.z + c * direction.z};
		return 1;
	}
	return 0;
}

