/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_camera_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:29:50 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/19 15:07:00 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

static int	check_inside_sphere(t_scene *scene, t_sphere *sphere)
{
	if (distance(vec3_sub(scene->camera.pos, sphere->pos)) <= sphere->diameter \
		/ 2)
		return (INSIDE_OBJECT);
	return (0);
}

static int	closest_point_to_vector(t_vec3 start, t_vec3 end, t_vec3 point, \
	t_cylinder *cylinder)
{
	t_vec3	line_ve;
	t_vec3	point_to_point;
	float	dist;
	float	dot;

	line_ve = vec3_sub(end, start);
	line_ve = vec3_normalize(line_ve);
	point_to_point = vec3_sub(point, start);
	dot = dot_vector3(line_ve, line_ve);
	if (dot < 0.0001)
		return (0);
	dist = dot_vector3(point_to_point, line_ve) / dot;
	start = (t_vec3){start.x + dist * line_ve.x, start.y + dist \
		* line_ve.y, start.z + dist * line_ve.z};
	if (distance(vec3_sub(start, cylinder->pos)) < cylinder->height / 2 \
		&& distance(vec3_sub(point, start)) < cylinder->diameter / 2)
		return (1);
	return (0);
}

static int	check_inside_cylinder(t_scene *scene, t_cylinder *cylinder)
{
	t_vec3	start;
	t_vec3	end;

	cylinder->axis_vector = vec3_normalize(cylinder->axis_vector);
	start = (t_vec3){cylinder->pos.x + cylinder->axis_vector.x \
		* (cylinder->diameter / 2), cylinder->pos.y + cylinder->axis_vector.y \
		* (cylinder->diameter / 2), cylinder->pos.z + cylinder->axis_vector.z \
		* (cylinder->diameter / 2)};
	end = (t_vec3){cylinder->pos.x + cylinder->axis_vector.x \
		* (cylinder->diameter / 2) * (-1.0f), cylinder->pos.y \
		+ cylinder->axis_vector.y * (cylinder->diameter / 2) * (-1.0f), \
		cylinder->pos.z + cylinder->axis_vector.z \
		* (cylinder->diameter / 2) * (-1.0f)};
	if (closest_point_to_vector(start, end, scene->camera.pos, cylinder))
		return (INSIDE_OBJECT);
	return (0);
}

static int	check_inside_plane(t_scene *scene, t_plane *plane)
{
	t_vec3	camera_to_plane;

	camera_to_plane = vec3_normalize(vec3_sub(plane->point, scene->camera.pos));
	plane->normal_vector = vec3_normalize(plane->normal_vector);
	if (fabsf(dot_vector3(camera_to_plane, plane->normal_vector)) <= TINY_VALUE)
		return (INSIDE_OBJECT);
	return (0);
}

int	check_camera(t_scene *scene)
{
	t_object	*temp;

	temp = scene->objects;
	while (temp->next != NULL && !scene->error_catcher)
	{
		if (temp->type == OBJECT_SPHERE)
			scene->error_catcher = check_inside_sphere(scene, \
			(t_sphere *)temp->data);
		else if (temp->type == OBJECT_PLANE)
			scene->error_catcher = check_inside_plane(scene, \
			(t_plane *)temp->data);
		else if (temp->type == OBJECT_CYLINDER)
			scene->error_catcher = check_inside_cylinder(scene, \
			(t_cylinder *)temp->data);
		temp = temp->next;
	}
	return (scene->error_catcher);
}
