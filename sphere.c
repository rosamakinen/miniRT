/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:01:24 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/20 10:31:11 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"
#include "./libft/includes/libft.h"
#include "./libft/includes/ft_printf.h"
#include <math.h>
#include <stdio.h>

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

	cam_ray = vec3_sub(cam->pos, sphere->pos);
	radius = sphere->diameter / 2;

	// (bx^2 + by^2 + bz^2)t^2 + (2 axbx + 2 ayby + 2 azbz)t + (ax^2 + ay^2 + az^2 - r^2) = 0
	// 			* a *					* b *						* c *
	//t = hit distance
	//a = ray origin // "camera"
	//b = ray direction
	//r = radius

	//** quadratic formula is b^2 - 4ac **
	cam->norm_coord.z = 0;
	a = dot_vector3(cam->norm_coord, cam->norm_coord);
	b = 2.0f * dot_vector3(cam_ray, cam->norm_coord);
	c = dot_vector3(cam_ray, cam_ray) - radius * radius;
	hit = b * b - 4.0 * a * c;
	if (hit >= 0.0)
	{
		mlx_pixel_put(img->mlx, img->win, x, y, 0xFFC301); //yellow for hit
		return (1);
	}
	return (0);
}
