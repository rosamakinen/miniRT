/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:39:31 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/17 15:13:31 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

t_vec3 closest_point_to_line(t_vec3 start, t_vec3 end, t_vec3 point, t_cylinder *cylinder)
{
	t_vec3	line_ve;
	t_vec3	point_to_point;
	float	dist;
	float	dot;

	line_ve = vec3_sub(end, start);
	line_ve = vec3_normalize(line_ve);
	point_to_point = vec3_sub(point, start);
	dot =  dot_vector3(line_ve, line_ve);
	if (dot < 0.0001)
		return ((t_vec3){FLT_MAX, FLT_MAX, FLT_MAX});
	dist = dot_vector3(point_to_point, line_ve) / dot;
	start = (t_vec3){start.x + dist * line_ve.x,  start.y + dist * line_ve.y, start.z + dist * line_ve.z};
	if (distance(vec3_sub(start, cylinder->pos)) > cylinder->height / 2)
		return ((t_vec3){FLT_MAX, FLT_MAX, FLT_MAX});
	return (start);
}

int	check_hit(t_cylinder *cylinder, t_vec3 hitpoint)
{
	t_vec3	top_cap;
	t_vec3	bottom_cap;
	t_vec3	inverse;

	inverse = vec3_negative(cylinder->axis_vector);
	top_cap = vec3_add(cylinder->pos, vec3_scalar_multiplication(cylinder->axis_vector,
				cylinder->height / 2));
	bottom_cap = vec3_add(cylinder->pos, vec3_scalar_multiplication(inverse,
				cylinder->height / 2));
	top_cap = closest_point_to_line(top_cap, bottom_cap, hitpoint, cylinder);
	if(top_cap.x == FLT_MAX || top_cap.y == FLT_MAX || top_cap.z == FLT_MAX)
		return (0);
	return (1);
}

t_vec3	dist_compare(t_vec3 start, t_vec3 one, t_vec3 two)
{
	float dist_one;
	float dist_two;

	dist_one = distance(vec3_sub(start, one));
	dist_two = distance(vec3_sub(start, two));
	if (dist_one < dist_two)
		return (one);
	return (two);
}

int	find_best_hit(t_vec3 *intersection1, t_vec3 *intersection2, t_vec3 start, t_cylinder *cylinder)
{
	int check[2];

	check[0] = check_hit(cylinder, *intersection1);
	check[1] = check_hit(cylinder, *intersection2);
	if (check[0] && !check[1])
		return (1);
	else if (!check[0] && check[1])
	{
		*intersection1 = *intersection2;
		return (1);
	}
	else if (!check[0] && !check[1])
		return (0);
	else if (check[0] && check[1])
	{
		*intersection1 = dist_compare(start, *intersection1, *intersection2);
		return (1);
	}
	return (0);
}

int infinite_cylinder_hit(t_vec3 ray_start, t_vec3 ray_direction, t_cylinder *cylinder, t_vec3 *intersection1, t_vec3 *intersection2)
{
	t_vec3	one;
	t_vec3	two;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	cylinder->axis_vector = vec3_normalize(cylinder->axis_vector);
	one = vec3_sub(ray_direction, vec3_scalar_multiplication(cylinder->axis_vector, dot_vector3(ray_direction, cylinder->axis_vector)));
	two = vec3_sub(vec3_sub(ray_start, cylinder->pos), vec3_scalar_multiplication(cylinder->axis_vector, dot_vector3(vec3_sub(ray_start, cylinder->pos), cylinder->axis_vector)));
	a = dot_vector3(one, one);
	b = 2 * dot_vector3(one, two);
	c = dot_vector3(two, two) - ((cylinder->diameter / 2) * (cylinder->diameter / 2));
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return 0;
    }
    c = (-b + sqrt(discriminant)) / (2 * a);
    a = (-b - sqrt(discriminant)) / (2 * a);
	*intersection1 = (t_vec3){ray_start.x + c * ray_direction.x , ray_start.y
                + c * ray_direction.y, ray_start.z + c * ray_direction.z };
    *intersection2 = (t_vec3){ray_start.x + a * ray_direction.x, ray_start.y
                + a * ray_direction.y, ray_start.z + a * ray_direction.z};
	return find_best_hit(intersection1, intersection2, ray_start, cylinder);
}

void cyl_cap_plane_initialize(t_plane *my_planes, t_cylinder *cylinder, int dir)
{
	my_planes->color = cylinder->color;
	my_planes->normal_vector = (t_vec3){cylinder->axis_vector.x * dir, cylinder->axis_vector.y * dir, cylinder->axis_vector.z * dir};
	my_planes->normal_vector = vec3_normalize(my_planes->normal_vector);
	my_planes->point = (t_vec3){cylinder->pos.x + my_planes->normal_vector.x * (cylinder->height / 2),cylinder->pos.y + my_planes->normal_vector.y * (cylinder->height / 2),cylinder->pos.z + my_planes->normal_vector.z * (cylinder->height / 2)};
}

int find_min(float *dists, int size)
{
	int	i;
	int answer;
	float holder;

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

t_vec3 cylinder_normal(t_vec3 center, t_vec3 axis_rot, t_vec3 hit_pos, float d, t_cylinder *cylinder)
{
	t_vec3	start;
	t_vec3	end;
	t_vec3	closest;

	end = (t_vec3){center.x + axis_rot.x * d, center.y + axis_rot.y * d, center.z + axis_rot.z * d};
	start = (t_vec3){center.x + axis_rot.x * d * -1, center.y + axis_rot.y * d * -1, center.z + axis_rot.z * d * -1};
	closest = closest_point_to_line(start, end, hit_pos, cylinder);
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
	float		dist[3];

	cyl_cap_plane_initialize(&my_planes[0], cylinder, 1);
	cyl_cap_plane_initialize(&my_planes[1], cylinder, -1);
	check[0] = plane_hit(start_pos, ray_direction, my_planes[0], &hit_pos[0]);
	dist[0] = FLT_MAX;
	if (check[0])
	{
		dist[0] = distance(vec3_sub(my_planes[0].point, hit_pos[0]));
		if ((cylinder->diameter / 2) < dist[0])
			dist[0] = FLT_MAX;
		else
			dist[0] = distance(vec3_sub(start_pos, hit_pos[0]));
	}
	check[1] = plane_hit(start_pos, ray_direction, my_planes[1], &hit_pos[1]);
	dist[1] = FLT_MAX;
	if (check[1])
	{
		dist[1] = distance(vec3_sub(my_planes[1].point, hit_pos[1]));
		if ((cylinder->diameter / 2) < dist[1])
			dist[1] = FLT_MAX;
		else
			dist[1] = distance(vec3_sub(start_pos, hit_pos[1]));
	}
	check[2] = infinite_cylinder_hit(start_pos, ray_direction, cylinder, &hit_pos[2], &hit_pos[3]);
	dist[2] = FLT_MAX;
	if (check[2])
		dist[2] = distance(vec3_sub(start_pos, hit_pos[2]));
	hit.hit = find_min(&dist[0], 3);
	if (hit.hit < 2)
	{
		cylinder->my_hit.my_normal = my_planes[hit.hit].normal_vector;
		hit.pos = hit_pos[hit.hit];
		hit.hit = 1;
	}
	else if (hit.hit == 2)
	{
		cylinder->my_hit.my_normal = cylinder_normal(cylinder->pos, cylinder->axis_vector, hit_pos[2], cylinder->height / 2, cylinder);
		hit.hit = 1;
		hit.pos = hit_pos[2];
	}
	else
		hit.hit = 0;
	return (hit);
}
