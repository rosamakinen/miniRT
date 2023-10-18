/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:39:31 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/18 17:23:27 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	cyl_cap_plane_initialize(t_plane *my_planes, t_cylinder *cylinder, \
	int dir)
{
	my_planes->color = cylinder->color;
	my_planes->normal_vector = (t_vec3){cylinder->axis_vector.x * dir, \
		cylinder->axis_vector.y * dir, cylinder->axis_vector.z * dir};
	my_planes->normal_vector = vec3_normalize(my_planes->normal_vector);
	my_planes->point = (t_vec3){cylinder->pos.x + my_planes->normal_vector.x \
		* (cylinder->height / 2), cylinder->pos.y + my_planes->normal_vector.y \
		* (cylinder->height / 2), cylinder->pos.z + my_planes->normal_vector.z \
		* (cylinder->height / 2)};
}

int	find_min(float *dists, int size)
{
	int		i;
	int		answer;
	float	holder;

	i = 0;
	answer = 235400;
	holder = FLT_MAX;
	while (i < size)
	{
		if (dists[i] < holder)
		{
			holder = dists[i];
			answer = i;
		}
		i++;
	}
	return (answer);
}

t_vec3	cylinder_normal(t_vec3 center, t_vec3 hit_pos, \
	float d, t_cylinder *cylinder)
{
	t_vec3	start;
	t_vec3	end;
	t_vec3	closest;

	end = (t_vec3){center.x + cylinder->axis_vector.x * d, center.y \
		+ cylinder->axis_vector.y * d, center.z + cylinder->axis_vector.z * d};
	start = (t_vec3){center.x + cylinder->axis_vector.x * d * -1, center.y \
		+ cylinder->axis_vector.y * d * -1, center.z \
		+ cylinder->axis_vector.z * d * -1};
	closest = closest_point_to_line(start, end, hit_pos, cylinder);
	start = vec3_sub(hit_pos, closest);
	start = vec3_normalize(start);
	return (start);
}

float	validate_cap_hit(t_plane cap, t_vec3 start_pos, \
	t_vec3 hit_pos, float radius)
{
	float	answer;

	answer = distance(vec3_sub(cap.point, hit_pos));
	if (radius < answer)
		answer = FLT_MAX;
	else
		answer = distance(vec3_sub(start_pos, hit_pos));
	return (answer);
}

t_plane	find_cap_hit(t_cylinder *cylinder, t_vec3 ray_direction, \
	t_vec3 start_pos, float *distance)
{
	t_plane		my_planes[2];
	t_vec3		hit_pos[2];
	float		dist[2];

	cyl_cap_plane_initialize(&my_planes[0], cylinder, 1);
	cyl_cap_plane_initialize(&my_planes[1], cylinder, -1);
	dist[0] = FLT_MAX;
	if (plane_hit(start_pos, ray_direction, my_planes[0], &hit_pos[0]))
		dist[0] = validate_cap_hit(my_planes[0], start_pos, hit_pos[0], \
			cylinder->diameter / 2);
	dist[1] = FLT_MAX;
	if (plane_hit(start_pos, ray_direction, my_planes[1], &hit_pos[1]))
		dist[1] = validate_cap_hit(my_planes[1], start_pos, hit_pos[1], \
			cylinder->diameter / 2);
	if (dist[0] == FLT_MAX && dist[1] == FLT_MAX)
		*distance = FLT_MAX;
	else
	{
		my_planes[0] = my_planes[(dist[0] > dist[1])];
		my_planes[0].point = hit_pos[(dist[0] > dist[1])];
		*distance = dist[(dist[0] > dist[1])];
	}
	return (my_planes[0]);
}
