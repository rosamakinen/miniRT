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

	//printf("sphere->color = %i\n", sphere->color);
	temp_color = int_to_vec4(sphere->color);
	normalize_color_vec4(&temp_color);
	printf("temp r %f, g %f, b %f\n", temp_color.r, temp_color.g, temp_color.b);
	img->hit_data.color = temp_color;
}

void	get_object_basecolor(t_scene *img)
{
	t_object	*temp_objects;

	temp_objects = img->objects;
	if(img->hit_data.closest_id)
	{
		while (temp_objects->id && temp_objects->id != img->hit_data.closest_id)
		{
			temp_objects = temp_objects->next;
		}
		if (temp_objects->type == OBJECT_SPHERE)
		{
			//printf("closest %i, temp %i\n",img->hit_data.closest_id, temp_objects->id);
			get_sphere_color(temp_objects->data, img);
		}
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

	return (temp_col);
}

t_vec4	add_ambient_value(t_scene *img)
{
	t_vec4	ambient;

	ambient = multiply_vec4_value(img->hit_data.color, img->ambient_light.ratio);
	return (ambient);
}


t_vec4	get_pixel_color(t_scene *img, t_hit *hit)
{
	t_vec4	color;
	// int test_color;

	// test_color = 0xFF00FF;
	// img->hit_data.color = uint_to_normalized_vec4(test_color);
	//get_object_basecolor(img); //is already normalized
	img->hit_data.color = transfer_pos_to_color(hit);
	//img->hit_data.color = add_ambient_value(img);
	img->hit_data.brightness = get_brightness(img, hit); // calculated from normal and light directiom
	printf("hit col at start r %f, g %f, b %f\n", img->hit_data.color.r, img->hit_data.color.g, img->hit_data.color.b);
	printf("brightness : %f\n", img->hit_data.brightness);
	color = multiply_vec4_value(img->hit_data.color, img->hit_data.brightness);
	printf("hit col r %f, g %f, b %f\n", color.r, color.g, color.b);
	return (color);
}
