/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:13:11 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/14 16:30:47 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

// int	check_cylinder_shadow(t_hit *hit, t_object *object, t_vec3 shadow_direction)
// {
		// t_plane	*cylinder;
		// t_vec3	point1;
		// t_vec3	point2;

		// cylinder = (t_cylinder *)object->data;
		// if (cylinder_hit(hit->pos, shadow_direction, *cylinder, &point) == 1)
		// 	return (1);
		// return (0);
// }


int	check_plane_shadow(t_hit *hit, t_object *object, t_vec3 shadow_direction)
{
	t_plane	*plane;
	t_vec3	point;

	plane = (t_plane *)object->data;
	if (plane_hit(hit->pos, shadow_direction, *plane, &point) == 1)
		return (1);
	return (0);
}


int	check_sphere_shadow(t_hit *hit, t_object *object, t_vec3 shadow_direction)
{
	t_sphere	*sphere;
	t_vec3		point1;
	t_vec3		point2;

	sphere = (t_sphere *)object->data;
	if (sphere_hit(sphere, hit->pos, shadow_direction, &point1, &point2) == 1)
		return (1);
	return (0);
}

int	check_for_shadow(t_scene *img, t_hit *hit, t_object *object)
{
	t_vec3		shadow_direction;

	shadow_direction = vec3_sub(hit->pos, img->light_sources.pos);
	shadow_direction = vec3_normalize(shadow_direction);
	if (object->type == OBJECT_SPHERE)
	{
		return (check_sphere_shadow(hit, object, shadow_direction));
	}
	if (object->type == OBJECT_PLANE)
	{
		return (check_plane_shadow(hit, object, shadow_direction));
	}
	// if (object->type == OBJECT_CYLINDER)
	// {
	// 	return (check_cylinder_shadow(hit, object, shadow_direction));
	// }
	return (0);
}

void	get_shadow(t_scene *img, t_hit *hit)
{
	t_object	*temp_objects;

	temp_objects = img->objects;
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
