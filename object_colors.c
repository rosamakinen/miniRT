/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 06:14:17 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/03 11:23:52 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void	get_plane_color(t_object *data, t_scene *img)
{
	t_plane	*plane;
	t_vec4	temp_color;

	plane = (t_plane *)data;
	temp_color = int_to_vec4(plane->color);
	img->hit_data.color = temp_color;
}

void	get_cylinder_color(t_object *data, t_scene *img)
{
	t_cylinder	*cylinder;
	t_vec4		temp_color;

	cylinder = (t_cylinder *)data;
	temp_color = int_to_vec4(cylinder->color);
	img->hit_data.color = temp_color;
}

void	get_sphere_color(t_object *data, t_scene *img)
{
	t_sphere	*sphere;
	t_vec4		temp_color;

	sphere = (t_sphere *)data;
	temp_color = int_to_vec4(sphere->color);
	normalize_color_vec4(&temp_color);
	// printf("temp r %f, g %f, b %f\n", temp_color.r, temp_color.g, temp_color.b);
	img->hit_data.color = temp_color;
}

void	get_object_basecolor(t_scene *img)
{
	t_object	*temp_objects;

	temp_objects = img->objects;
	if (img->hit_data.closest_id)
	{
		while (temp_objects->id && temp_objects->id != img->hit_data.closest_id)
		{
			temp_objects = temp_objects->next;
		}
		if (temp_objects->type == OBJECT_SPHERE)
			get_sphere_color(temp_objects->data, img);
		if (temp_objects->type == OBJECT_PLANE)
			get_plane_color(temp_objects->data, img);
		if (temp_objects->type == OBJECT_CYLINDER)
			get_cylinder_color(temp_objects->data, img);
	}
}
