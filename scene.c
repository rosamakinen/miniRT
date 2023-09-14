/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:44:07 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/14 14:32:02 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"
#include "./includes/parser.h"
#include "./libft/includes/libft.h"
#include "./libft/includes/ft_printf.h"
#include <math.h>
#include <stdio.h>

//first get ray_direction, store it in camera->norm_coord;
//loop through the objects, for each object send to check hit, and object id
//find the shortest distance and for that object fetch the information
//for now, if it is a hit and the distance is the smallest, draw a colour on screen

void	get_distance(t_scene *img, t_camera *cam, t_hit hit)
{
	//we loop check for the distance and update it to be the smallest distance
	t_vec3	subtracted;
	float	new_distance;

	new_distance = FLT_MAX;
	//distance is:
	//d(P1,P2) = (x2-x1)2 + (y2-y1)2 + (z2-z1)2.
	subtracted = vec_sub(cam->norm_coord, hit.pos);
	new_distance = distance(subtracted);
	printf("before %f\n", new_distance);
	if (new_distance < img->hit_data.distance)
		img->hit_data.distance = new_distance;
	printf("%f\n", new_distance);
}

int	get_closest_hit(t_camera *cam, t_scene *img, int x, int y)
{
	//loop through the objects && get hit
	//if hit, save the object and
	t_scene		*temp;
	t_hit		hit;

	temp = img;
	hit.hit = 1;
	img->hit_data.distance = FLT_MAX;
	if (temp->objects)
		while (temp->objects->next != NULL)
		{
			//hit = get_hit(cam, temp->objects, x, y);
			printf("type is %hd\n", temp->objects->type);
			x = 0;
			y = 0;
			hit.pos.x = 0;
			hit.pos.y = 0;
			hit.pos.z = 0;
			if (hit.hit == 1)
				get_distance(img, cam, hit);
			temp->objects = temp->objects->next;
		}
	if (img->hit_data.distance != FLT_MAX)
	{
		ft_printf("%i\n", (int)img->hit_data.distance);
		return (1);
	}
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
	while(y++ < img->height)
	{
		x = 0;
		while (x++ < img->width)
		{
			get_ray_direction(&cam, img, x, y); /// coordinate systems x & y
			if (get_closest_hit(&cam, img, x, y))//returns pos, and hit or not
				mlx_pixel_put(img->mlx, img->win, x, y, 0xFFC301); //yellow for hit
			else
				mlx_pixel_put(img->mlx, img->win, x, y, 0x581847); // dark for background
		}
	}
	return (0);
}
