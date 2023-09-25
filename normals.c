/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:34:36 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/25 07:53:30 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

void	get_sphere_normal(t_object *data, t_scene *img, t_hit *hit)
{
	t_sphere	*sphere;
	sphere = (t_sphere *)data;

	img->hit_data.normal = vec3_sub(hit->pos, sphere->pos);
	img->hit_data.normal = vec3_normalize(img->hit_data.normal);
}

void	get_plane_normal(t_object *data, t_scene *img)
{
	t_plane	*plane;
	plane = (t_plane *)data;
	img->hit_data.normal = plane->normal_vector;
}

void	get_normal(t_scene *img, t_hit *hit)
{
	t_object	*temp_objects;

	temp_objects = img->objects;
	if(img->hit_data.closest_id)
	{
		while (temp_objects->id && temp_objects->id != img->hit_data.closest_id)
			temp_objects = temp_objects->next;
		if (temp_objects->type == OBJECT_SPHERE)
			get_sphere_normal(temp_objects->data, img, hit);
		else if (temp_objects->type == OBJECT_PLANE)
			get_plane_normal(temp_objects->data, img);
	}
	// *** here we add normal calculations for all of the shapes ***

	// else if (temp_objects->type == OBJECT_CYLINDER)
	// 	get_cylinder_normal();
}
