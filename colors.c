/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 06:24:44 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/25 11:12:31 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void	get_plane_color(t_object *data, t_scene *img)
{
	t_plane	*plane;
	t_vec4		temp_color;
	plane = (t_plane *)data;

	temp_color = int_to_normalized_vec4(plane->color);
	img->hit_data.color = temp_color;
}
void	get_cylinder_color(t_object *data, t_scene *img)
{
	t_cylinder	*cylinder;
	t_vec4		temp_color;
	cylinder = (t_cylinder *)data;

	temp_color = int_to_normalized_vec4(cylinder->color);
	img->hit_data.color = temp_color;
}
void	get_sphere_color(t_object *data, t_scene *img)
{
	t_sphere	*sphere;
	t_vec4		temp_color;
	sphere = (t_sphere *)data;

	temp_color = int_to_normalized_vec4(sphere->color);
	img->hit_data.color = temp_color;
}

void	get_object_basecolor(t_scene *img)
{
	t_object	*temp_objects;

	temp_objects = img->objects;
	if(img->hit_data.closest_id)
	{
		while (temp_objects->id && temp_objects->id != img->hit_data.closest_id)
			temp_objects = temp_objects->next;
		if (temp_objects->type == OBJECT_SPHERE)
			get_sphere_color(temp_objects->data, img);
		// if (temp_objects->type == OBJECT_PLANE)
		// 	get_plane_color(temp_objects->data, img);
		// if (temp_objects->type == OBJECT_CYLINDER)
		// 	get_cylinder_color(temp_objects->data, img);
	}
}


t_vec4	transfer_pos_to_color(t_hit *hit)
{
	t_vec4 temp_col;

	temp_col.alpha = 1;
	hit->pos = vec3_normalize(hit->pos);
	temp_col.r = hit->pos.x;
	temp_col.g = hit->pos.y;
	temp_col.b = hit->pos.z;

	//printf("temp.r %f, temp.g %f, temp.b %f", hit->pos.x, hit->pos.y, hit->pos.z);
	return (temp_col);
}

t_vec4	get_pixel_color(t_scene *img, t_hit *hit)
{
	t_vec4	color;

	//get_object_basecolor(img); //is already normalized
	img->hit_data.color = transfer_pos_to_color(hit);
	img->hit_data.brightness = get_brightness(img, hit); // calculated from normal and light directiom

	color = multiply_vec4_value(img->hit_data.color, img->hit_data.brightness);
	return (color);
}
