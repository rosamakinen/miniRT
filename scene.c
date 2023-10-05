/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:44:07 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/04 07:47:00 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

//distance is:
//d(P1,P2) = (x2-x1)2 + (y2-y1)2 + (z2-z1)2.
void	get_distance(t_scene *img, t_camera *cam, t_hit *hit, int id)
{
	t_vec3	subtracted;
	float	new_distance;

	subtracted = vec3_sub(cam->norm_coord, (*hit).pos);
	new_distance = distance(subtracted);
	if (new_distance < img->hit_data.distance)
	{
		img->hit_data.closest_id = id;
		img->hit_data.distance = new_distance;
	}
}

int	get_closest_hit(t_camera *cam, t_scene *img, t_hit *hit, int x, int y)
{
	t_scene		*temp;

	temp = img;
	img->hit_data.distance = FLT_MAX;
	img->hit_data.closest_id = INT_MAX;
	if (temp)
	{
		(*hit) = get_hit(cam, temp->objects, x, y);
		if ((*hit).hit == 1)
		{
			get_distance(img, cam, hit, temp->objects->id);
		}
	}
	img->hit_data.norm_pos = vec3_normalize(hit->pos);
	return (0);
}

void	set_id(t_scene *img)
{
	t_object	*temp;
	int			i;

	i = 1;
	temp = img->objects;
	while (temp)
	{
		temp->id = i;
		temp = temp->next;
		i++;
	}
}

int	per_pixel(t_camera *cam, t_scene *img, int x, int y)
{
	t_hit	hit;
	t_vec4	color;
	int		int_col;

	hit.hit = 1;
	img->hit_data.distance = FLT_MAX;
	int_col = 0;
	get_ray_direction(cam, img, x, y);
	get_closest_hit(cam, img, &hit, x, y);
	if (hit.hit == 1)
	{
		get_normal(img, &hit);
		color = get_pixel_color(img, &hit);
		int_col = normalized_vec4_to_int(color);
		return (int_col);
	}
	else
		return (0x000000);
	return (0);
}

int	draw_img(t_scene *img)
{
	t_camera	cam;
	int			color;
	int			x;
	int			y;

	x = 0;
	y = 0;
	cam = img->camera;
	set_id(img);
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = per_pixel(&cam, img, x, y);
			mlx_pixel_put(img->mlx, img->win, x, y, color);
			x++;
		}
		y++;
	}
	printf("count_light %i\n", img->light_count);
	return (0);
}
