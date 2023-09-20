/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:44:07 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/20 13:10:22 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"
#include "./libft/includes/libft.h"
#include "./libft/includes/ft_printf.h"
#include <math.h>
#include <stdio.h>

//first get ray_direction, store it in camera->norm_coord;
//loop through the objects, for each object send to check hit, and object id
//find the shortest distance and for that object fetch the information
//for now, just if it is a hit and the distance is the smallest, draw a colour on screen



void	get_distance(t_scene *img, t_camera *cam, t_hit *hit, int id)
{
	//distance is:
	//d(P1,P2) = (x2-x1)2 + (y2-y1)2 + (z2-z1)2.

	t_vec3	subtracted;
	float	new_distance;
	subtracted = vec3_sub(cam->norm_coord, (*hit).pos);
	new_distance = distance(subtracted);
	if (new_distance < img->hit_data.distance)
	{
		img->hit_data.closest_id = id;
		img->hit_data.distance = new_distance;
	}
	//printf("%f\n", new_distance);
}

int	get_closest_hit(t_camera *cam, t_scene *img, t_hit *hit, int x, int y)
{
	//loop through the objects && get hit
	//if hit, save the object and

	t_scene		*temp;

	temp = img;
	img->hit_data.distance = FLT_MAX;
	img->hit_data.closest_id = 0;
	if (temp)
	{
			//keep track of which object is which (maybe initialize the ids elsewhere)
			(*hit) = get_hit(cam, temp->objects, x, y);
			// printf("type is %hd, hit is %i\n", temp->objects->type, hit->hit);
			if ((*hit).hit == 1)
			{
				get_distance(img, cam, hit, temp->objects->id);
			}
	}
	img->hit_data.norm_pos = vec3_normalize(hit->pos);
	return (0);
}

int	per_pixel(t_camera *cam, t_scene *img, int x, int y)
{
	t_hit	hit;
	hit.hit = 1;

	img->hit_data.distance = FLT_MAX;
	// get_ray_direction(cam, img, x, y);
	get_closest_hit(cam, img, &hit, x, y);
	get_normal(img, &hit);
	img->hit_data.brightness = get_brightness(img, &hit); // calculated from normal and light direction
	if (img->hit_data.distance != FLT_MAX)
	{
		mlx_pixel_put(img->mlx, img->win, x, y, 0xFFC301 * img->hit_data.brightness); //yellow
		//ft_printf("hit distance: %i\n", (int)img->hit_data.distance);
		return (1);
	}
	else
		mlx_pixel_put(img->mlx, img->win, x, y, 0x581847); // purple

	// func for color
	// func for light
	// etc
	return (0);
}

int	draw_img(t_scene *img)
{
	t_camera	cam;
	int			x;
	int			y;

	x = 0;
	y = 0;
	cam = img->camera;
	while(y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			per_pixel(&cam, img, x , y);
			x++;
		}
		y++;
	}
	return (0);
}
