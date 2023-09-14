/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:01:24 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/14 08:14:16 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"
#include "./includes/vectors.h"
#include "./libft/includes/libft.h"
#include "./libft/includes/ft_printf.h"
#include <math.h>
#include <stdio.h>

float	dot_vector3(t_vec3 vector1, t_vec3 vector2)
{
	return(vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z);
}

t_vec3	sub_coord(t_vec3 coord1, t_vec3 coord2)
{
	t_vec3	temp;

	temp.x = coord1.x - coord2.x; // to calculate vector from the camera position(ray origin) and the position of the object.
	temp.y = coord1.y - coord2.y;
	temp.z = coord1.z - coord2.z;
	return (temp);
}

int	draw_sphere(t_camera *cam, t_scene *img, int x, int y)
{
	float	radius;
	float	a;
	float	b;
	float	c;
	float	hit;
	t_object	*temp;
	t_sphere	*sphere;
	t_vec3		cam_ray;

	temp = img->objects;
	if (temp->type == OBJECT_SPHERE)
		sphere = (t_sphere *)temp->data;
	else
		return (0);

	cam_ray = sub_coord(cam->pos, sphere->pos);
	radius = sphere->diameter / 2;

	//a = x_c * x_c + y_c * y_c + z_c * z_c; // vec

	// (bx^2 + by^2 + bz^2)t^2 + (2 axbx + 2 ayby + 2 azbz)t + (ax^2 + ay^2 + az^2 - r^2) = 0
	// 			* a *					* b *						* c *
	//t = hit distance
	//a = ray origin // "camera"
	//b = ray direction
	//r = radius

	//** quadratic formula is b^2 - 4ac **
	a = dot_vector3(cam->norm_coord, cam->norm_coord);
	b = 2.0f * dot_vector3(cam_ray, cam->norm_coord);
	c = dot_vector3(cam_ray, cam_ray) - radius * radius;
	hit = b * b - 4.0*a*c;
	//printf("hit = %f\n", hit);
	if (hit >= 0.0)
	{
		mlx_pixel_put(img->mlx, img->win, x, y, 0xFFC301); //yellow for hit
		return (1);
	}
	return (0);
}
