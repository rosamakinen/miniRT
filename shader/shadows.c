/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:13:11 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/19 09:04:39 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	check_cylinder_shadow(t_hit *hit, t_object *object, \
t_vec3 shadow_direction, t_float_vec3 data)
{
	t_cylinder	*cylinder;
	t_hit		shadow_hit;

	cylinder = (t_cylinder *)object->data;
	shadow_hit = find_cylinder_hit(cylinder, shadow_direction, hit->pos);
	if (shadow_hit.hit == 1)
	{
		if (distance(vec3_sub(data.light, shadow_hit.pos)) >= data.dist)
			return (0);
		return (shadow_hit.hit);
	}
	return (0);
}

int	check_plane_shadow(t_hit *hit, t_object *object, t_vec3 shadow_direction, \
t_float_vec3 data)
{
	t_plane	*plane;
	t_vec3	point;

	plane = (t_plane *)object->data;
	if (plane_hit(hit->pos, shadow_direction, *plane, &point) == 1)
	{
		if (sanity_check(data.light, shadow_direction, point))
			return (0);
		if (distance(vec3_sub(data.light, point)) >= data.dist)
			return (0);
		return (1);
	}
	return (0);
}

int	check_sphere_shadow(t_hit *hit, t_object *object, t_vec3 shadow_direction, \
t_float_vec3 data)
{
	t_sphere	*sphere;
	t_vec3		points[2];

	sphere = (t_sphere *)object->data;
	if (sphere_hit(sphere, hit->pos, shadow_direction, points) == 1)
	{
		if (distance(vec3_sub(data.light, points[0])) >= data.dist && \
		distance(vec3_sub(data.light, points[1])) >= data.dist)
			return (0);
		return (1);
	}
	return (0);
}

int	check_for_shadow(t_scene *img, t_hit *hit, t_object *object)
{
	t_vec3			shadow_direction;
	t_float_vec3	data;

	shadow_direction = vec3_sub(img->light_sources.pos, hit->pos);
	data.dist = distance(shadow_direction);
	data.light = img->light_sources.pos;
	shadow_direction = vec3_normalize(shadow_direction);
	if (object->type == OBJECT_SPHERE)
		return (check_sphere_shadow(hit, object, shadow_direction, data));
	if (object->type == OBJECT_PLANE)
		return (check_plane_shadow(hit, object, shadow_direction, data));
	if (object->type == OBJECT_CYLINDER)
		return (check_cylinder_shadow(hit, object, shadow_direction, data));
	return (0);
}

void	get_shadow(t_scene *img, t_hit *hit)
{
	t_object	*temp_objects;

	temp_objects = img->objects;
	img->hit_data.is_in_shadow = 0;
	while (temp_objects->next != NULL)
	{
		if (temp_objects->id != img->hit_data.closest_id)
		{
			if (check_for_shadow(img, hit, temp_objects))
			{
				img->hit_data.is_in_shadow = 1;
				return ;
			}
		}
		temp_objects = temp_objects->next;
	}
}
