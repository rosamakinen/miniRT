/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:56:18 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/18 16:35:02 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	plane_hit(t_vec3 origin, t_vec3 direction, t_plane plane, t_vec3 *point)
{
	float	angle;
	float	dist;
	t_vec3	plane_to_cam;

	angle = dot_vector3(plane.normal_vector, direction);
	if (fabsf(angle) < 0.0001)
		return (0);
	plane_to_cam = vec3_sub(plane.point, origin);
	dist = dot_vector3(plane_to_cam, plane.normal_vector) / angle;
	if (dist < 0.0000001)
		return (0);
	*point = (t_vec3){origin.x + dist * direction.x, origin.y \
		+ dist * direction.y, origin.z + dist * direction.z};
	return (1);
}

int	sphere_hit(const t_sphere *sphere, const t_vec3 ray_start, \
	const t_vec3 direction, t_vec3 *intersections)
{
	t_quadratic	formula;
	t_vec3		dist;

	dist = vec3_sub(ray_start, sphere->pos);
	formula.a = dot_vector3(direction, direction);
	formula.b = 2.0 * dot_vector3(direction, dist);
	formula.c = dot_vector3(dist, dist) \
		- ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	formula.discriminant = formula.b * formula.b - 4 * formula.a * formula.c;
	if (formula.discriminant > 0)
	{
		formula.c = (-formula.b + sqrtf(formula.discriminant)) \
			/ (2.0 * formula.a);
		intersections[0] = (t_vec3){ray_start.x + formula.c \
			* direction.x, ray_start.y \
				+ formula.c * direction.y, ray_start.z \
				+ formula.c * direction.z};
		formula.c = (-formula.b - sqrtf(formula.discriminant)) \
			/ (2.0 * formula.a);
		intersections[1] = (t_vec3){ray_start.x + formula.c * direction.x, \
			ray_start.y + formula.c * direction.y, ray_start.z + formula.c \
			* direction.z};
		return (1);
	}
	return (0);
}

t_hit	find_cylinder_hit(t_cylinder *cylinder, t_vec3 ray_direction, \
	t_vec3 start_pos)
{
	t_hit		hit;
	t_vec3		body_hit;
	t_plane		my_plane;
	float		dist[2];

	my_plane = find_cap_hit(cylinder, ray_direction, start_pos, &dist[0]);
	dist[1] = FLT_MAX;
	if (infinite_cylinder_hit(start_pos, ray_direction, cylinder, &body_hit))
		dist[1] = distance(vec3_sub(start_pos, body_hit));
	hit.hit = find_min(&dist[0], 2);
	if (hit.hit == 0)
	{
		cylinder->my_hit.my_normal = my_plane.normal_vector;
		hit.pos = my_plane.point;
		hit.hit = 1;
	}
	else if (hit.hit == 1)
	{
		cylinder->my_hit.my_normal = cylinder_normal(cylinder->pos, \
			body_hit, cylinder->height / 2, cylinder);
		hit.pos = body_hit;
	}
	else
		hit.hit = 0;
	return (hit);
}
