/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:39:31 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/16 12:15:34 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

int infinite_cylinder_hit(t_vec3 ray_start, t_vec3 ray_direction, t_cylinder *cylinder, t_vec3 *intersection1, t_vec3 *intersection2) {

    float   a;
    float   b;
    float   c1;
    float   c2;
    float   discriminant;
    t_vec3  dist;

    // Translate and rotate the ray to the cylinder's local coordinates
    dist = vec3_sub(cylinder->pos, ray_start);
    a = dot_vector3(ray_direction, ray_direction);
    b = 2.0 * dot_vector3(ray_direction, dist);
    c1 = dist.x * dist.x + dist.y * dist.y - (cylinder->diameter * cylinder->diameter / 4.0);
    discriminant = b * b - 4 * a * c1;
    if (discriminant < 0) {
        return 0;
    }
    c1 = (-b + sqrt(discriminant)) / (2 * a);
    float z1 = ray_start.z + c1 * ray_direction.z;
    c2 = (-b - sqrt(discriminant)) / (2 * a);
    double z2 = ray_start.z + c2 * ray_direction.z;

    if (!(z1 >= -cylinder->height / 2.0 && z1 <= cylinder->height / 2.0) && !(z2 >= -cylinder->height / 2.0 && z2 <= cylinder->height / 2.0))
        return 0;
    *intersection1 = (t_vec3){ray_start.x + c1 * ray_direction.x , ray_start.y
                + c1 * ray_direction.y, ray_start.z + c1 * ray_direction.z };
    *intersection2 = (t_vec3){ray_start.x + c2 * ray_direction.x, ray_start.y
                + c2 * ray_direction.y, ray_start.z + c2 * ray_direction.z};
    return 1;
}

void cyl_cap_plane_initialize(t_plane *my_planes, t_cylinder *cylinder, int dir)
{
	my_planes->color = cylinder->color;
	my_planes->normal_vector = (t_vec3){cylinder->axis_vector.x * dir, cylinder->axis_vector.y * dir, cylinder->axis_vector.z * dir};
	my_planes->point = (t_vec3){my_planes->normal_vector.x * (cylinder->height / 2), my_planes->normal_vector.y * (cylinder->height / 2), my_planes->normal_vector.z * (cylinder->height / 2)};
}

int find_min(float *dists, int size)
{
	int	i;
	int answer;
	float holder;

	i = -1;
	answer = 0;
	holder = dists[0];
	while (++i < size)
	{
		if (dists[i] < holder)
		{
			holder = dists[i];
			answer = i;
		}
	}
	return (answer);
}

t_vec3 closest_point_to_line(t_vec3 start, t_vec3 end, t_vec3 point) {
	t_vec3	line_ve;
	t_vec3	point_to_point;
	float	dist;
	float	dot;

	line_ve = (t_vec3){start.x - end.x, start.y - end.y, start.z - end.z};
    point_to_point = (t_vec3){point.x - start.x, point.y - start.y, point.z - start.z};
    dist = distance(vec3_sub(line_ve, line_ve));
    dot = dot_vector3(point_to_point, line_ve) / (dist * dist);
    end = (t_vec3){start.x + dot * line_ve.x,  start.y + dot * line_ve.y, start.z + dot * line_ve.z};
    return (end);
}

t_vec3 cylinder_normal(t_vec3 center, t_vec3 axis_rot, t_vec3 hit_pos, float dir)
{
	t_vec3	start;
	t_vec3	end;
	t_vec3	closest;

	start = (t_vec3){center.x + axis_rot.x * dir, center.y + axis_rot.y * dir, center.z + axis_rot.z * dir};
	end = (t_vec3){center.x + axis_rot.x * dir* -1, center.y + axis_rot.y * dir * -1, center.z + axis_rot.z * dir* -1};
	closest = closest_point_to_line(start, end, hit_pos);
	start = vec3_sub(hit_pos, closest);
	start = vec3_normalize(start);
	return (start);
}

t_hit	find_cylinder_hit(t_cylinder *cylinder, t_vec3 ray_direction, t_vec3 start_pos)
{
	t_hit		hit = {0};
	int			check[3];
	t_vec3		hit_pos[4];
	t_plane		my_planes[2];
	float		dist[4];

	cyl_cap_plane_initialize(&my_planes[0], cylinder, 1);
	cyl_cap_plane_initialize(&my_planes[1], cylinder, -1);
	check[0] = plane_hit(start_pos, ray_direction, my_planes[0], &hit_pos[0]);
	dist[0] = (check[0] == 0) * FLT_MAX + (check[0] != 0) * distance(vec3_sub(my_planes[0].point, hit_pos[0]));
	if (dist[0] > cylinder->diameter / 2)
		dist[0] = FLT_MAX;
	check[1] = plane_hit(start_pos, ray_direction, my_planes[1], &hit_pos[1]);
	dist[1] = (check[1] == 0) * FLT_MAX  + (check[1] != 0) * distance(vec3_sub(my_planes[1].point, hit_pos[1]));
	if (dist[1] > cylinder->diameter / 2)
		dist[1] = FLT_MAX;
	check[2] = infinite_cylinder_hit(start_pos, ray_direction, cylinder, &hit_pos[2], &hit_pos[3]);
	dist[2] = (check[2] == 0) * FLT_MAX  + (check[2] != 0) * distance(vec3_sub(start_pos, hit_pos[2]));
	dist[3] = (check[2] == 0) * FLT_MAX  + (check[2] != 0) * distance(vec3_sub(start_pos, hit_pos[3]));
	hit.hit = find_min(&dist[0], 4);
	if (dist[hit.hit] == FLT_MAX)
	{
		hit.hit = 0;
		return (hit);
	}
	cylinder->my_hit.pos = hit_pos[hit.hit];
	if (hit.hit < 2)
	{
		cylinder->my_hit.my_normal = my_planes[hit.hit].normal_vector;
		hit.pos = hit_pos[hit.hit];
		hit.hit = 1;
	}
	else
	{
		cylinder->my_hit.my_normal = cylinder_normal(cylinder->pos, cylinder->axis_vector, hit_pos[hit.hit], cylinder->height / 2);
		hit.pos = hit_pos[hit.hit];
		hit.hit = 1;
	}

	return (hit);
}
