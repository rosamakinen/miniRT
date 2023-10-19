/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:25:15 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/19 08:57:50 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

//Honorable mention. The following function would not have been possible
//without the contributions of Sheree and Dorian!
t_vec3	find_ray_dir(t_camera *camera, float x, float y)
{
	float	offset[3];
	float	mini_ratio;
	t_vec3	ray_dir;
	t_vec3	temp_right;
	t_vec3	temp_up;

	mini_ratio = atan2f(y, x);
	offset[0] = distance((t_vec3){x, y, 0}) * 0.5f;
	offset[1] = offset[0] * cosf(mini_ratio);
	offset[2] = offset[0] * sinf(mini_ratio);
	temp_right = vec3_scalar_multiplication(camera->right_dir, offset[1]);
	temp_up = vec3_scalar_multiplication(camera->up_dir, offset[2]);
	ray_dir = vec3_add(temp_right, temp_up);
	ray_dir = vec3_add(camera->forward_dir, ray_dir);
	ray_dir = vec3_normalize(ray_dir);
	return (ray_dir);
}

t_hit	find_sphere_hit(t_sphere *sphere, t_vec3 ray_direction, \
	t_camera *camera)
{
	t_hit	hit;
	t_vec3	points[2];

	ft_bzero(&hit, sizeof(t_hit));
	if (sphere_hit(sphere, camera->pos, ray_direction, &points[0]))
	{
		if (distance(vec3_sub(camera->pos, points[0])) < \
			distance(vec3_sub(camera->pos, points[1])))
			hit.pos = points[0];
		else
			hit.pos = points[1];
		hit.hit = 1;
	}
	return (hit);
}

t_hit	find_plane_hit(t_plane *plane, t_vec3 ray_direction, t_camera *camera)
{
	t_hit	hit;
	t_vec3	point1;

	ft_bzero(&hit, sizeof(t_hit));
	if (plane_hit(camera->pos, ray_direction, *plane, &point1))
	{
		hit.pos = point1;
		hit.hit = 1;
	}
	return (hit);
}

int	sanity_check(t_vec3 origin, t_vec3 direction, t_vec3 hit)
{
	t_vec3	pos;
	t_vec3	neg;
	float	dist_pos;
	float	dist_neg;

	pos = (t_vec3){origin.x + direction.x, origin.y + direction.y, \
		origin.z + direction.z};
	neg = (t_vec3){origin.x - direction.x, origin.y - direction.y, \
		origin.z - direction.z};
	dist_pos = distance(vec3_sub(pos, hit));
	dist_neg = distance(vec3_sub(neg, hit));
	if (dist_pos <= dist_neg)
		return (1);
	return (0);
}

t_hit	get_hit(t_camera *cam, t_object *objects, float x, float y)
{
	t_hit			hit;
	static float	aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	t_vec3			test_dir;
	float			fake_x;
	float			fake_y;

	fake_x = x;
	fake_y = y;
	hit.hit = 0;
	translate_t_vec3s(&fake_x, &fake_y, aspect_ratio, cam->fov);
	test_dir = find_ray_dir(cam, fake_x, fake_y);
	if (objects->type == OBJECT_SPHERE)
		hit = find_sphere_hit((t_sphere *)objects->data, test_dir, cam);
	if (objects->type == OBJECT_PLANE)
		hit = find_plane_hit((t_plane *)objects->data, test_dir, cam);
	if (objects->type == OBJECT_CYLINDER)
		hit = find_cylinder_hit((t_cylinder *)objects->data, \
		test_dir, cam->pos);
	if (!sanity_check(cam->pos, test_dir, hit.pos))
		hit.hit = 0;
	return (hit);
}
