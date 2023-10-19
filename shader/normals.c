/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:34:36 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/19 11:46:13 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	get_sphere_normal(t_object *data, t_scene *img, t_hit *hit)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)data;
	img->hit_data.normal = vec3_sub(hit->pos, sphere->pos);
	img->hit_data.normal = vec3_normalize(img->hit_data.normal);
}

void	get_cylinder_normal(t_object *data, t_scene *img)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)data;
	img->hit_data.normal = vec3_normalize(cylinder->my_hit.my_normal);
}

void	get_plane_normal(t_object *data, t_scene *img, t_hit hit)
{
	t_plane	*plane;
	t_vec3	point1;
	t_vec3	point2;

	(void)hit;
	plane = (t_plane *)data;
	img->hit_data.normal = vec3_normalize(plane->normal_vector);
	point1 = (t_vec3){plane->point.x + plane->normal_vector.x, \
		plane->point.y + plane->normal_vector.y, \
		plane->point.z + plane->normal_vector.z};
	point2 = (t_vec3){plane->point.x - plane->normal_vector.x, \
		plane->point.y - plane->normal_vector.y, \
		plane->point.z - plane->normal_vector.z};
	if (distance(vec3_sub(point2, img->camera.pos)) \
		< distance(vec3_sub(point1, img->camera.pos)))
		img->hit_data.normal = vec3_negative(img->hit_data.normal);
}

void	get_normal(t_scene *img, t_hit *hit)
{
	t_object	*temp_objects;

	temp_objects = img->objects;
	if (img->hit_data.closest_id)
	{
		while (temp_objects->next && temp_objects->id != \
		img->hit_data.closest_id)
			temp_objects = temp_objects->next;
		if (temp_objects->type == OBJECT_SPHERE)
			get_sphere_normal(temp_objects->data, img, hit);
		else if (temp_objects->type == OBJECT_PLANE)
			get_plane_normal(temp_objects->data, img, *hit);
		else if (temp_objects->type == OBJECT_CYLINDER)
			get_cylinder_normal(temp_objects->data, img);
	}
}
