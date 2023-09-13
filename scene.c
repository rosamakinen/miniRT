/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:44:07 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/13 12:42:54 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"
#include "./includes/vectors.h"
#include "./libft/includes/libft.h"
#include "./libft/includes/ft_printf.h"
#include <math.h>
#include <stdio.h>

int	draw_img(t_scene *img)
{
	t_camera	cam;
	int	x;
	int	y;

	x = 0;
	y = 0;
	while(y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			get_ray_direction(&cam, img, x, y);
			//printf("cam->ray_dir: %f, %f, %f\n", cam.ray_direction.x, cam.ray_direction.y, cam.ray_direction.z);
			if (!draw_sphere(&cam, img, x, y))
				mlx_pixel_put(img->mlx, img->win, x, y, 0x581847); // dark for background
			x++;
		}
		y++;
	}
	return (0);
}
