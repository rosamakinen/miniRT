/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 10:01:24 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/06 12:14:55 by rmakinen         ###   ########.fr       */
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

int	draw_sphere(t_window *img, int x, int y)
{
	float	rad;
	float	a;
	float	b;
	float	c;
	float	hit;
	t_vec3	ray_dir;
	t_vec3	ray_origin;
	rad = 50.0;

	ray_dir.x = (float)x;
	ray_dir.y = (float)y;
	ray_dir.z = -1.0;

	ray_origin.x = img->width / 2 - ray_dir.x;
	ray_origin.y = img->height / 2 - ray_dir.y;
	ray_origin.z = 4.0 - ray_dir.z;

	//a = x_c * x_c + y_c * y_c + z_c * z_c; // vec

	// (bx^2 + by^2 + bz^2)t^2 + (2 axbx + 2 ayby + 2 azbz)t + (ax^2 + ay^2 + az^2 - r^2) = 0
	// 			* a *					* b *						* c *
	//t = hit distance
	//a = ray origin // "camera"
	//b = ray direction
	//r = radius

	//** quadratic formula is b^2 - 4ac **
	a = dot_vector3(ray_dir, ray_dir);
	b = 2.0 * dot_vector3(ray_origin, ray_dir);
	c = dot_vector3(ray_origin, ray_origin) - rad * rad;
	hit = b * b - 4.0*a*c;
	printf("hit = %f\n", hit);
	if (hit >= 0.0)
	{
		mlx_pixel_put(img->mlx, img->win, x, y, 0xFFC301); //yellow for hit
		return (1);
	}
	return (0);
}

int	draw_img(t_window *img)
{
	t_camera	cam;
	int	x;
	int	y;

	x = 0;
	y = 0;
	normalize_coordinates(img, &cam);
	while(y <= img->height)
	{
		x = 0;
		while (x <= img->width)
		{
			if (!draw_sphere(img, x, y))
				mlx_pixel_put(img->mlx, img->win, x, y, 0x581847); // dark for background
			x++;
		}
		y++;
	}
	return (0);
}
