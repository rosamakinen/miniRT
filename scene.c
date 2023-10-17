/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 09:44:07 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/17 13:41:43 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

void	get_distance(t_scene *img, t_camera *cam, t_hit *hit, t_hit new, int id)
{
	float	old_distance;
	t_vec3	old_subtracted;
	float	new_distance;
	t_vec3	new_subtracted;

	old_subtracted = vec3_sub(cam->forward_dir, (*hit).pos);
	old_distance = distance(old_subtracted);
	new_subtracted = vec3_sub(cam->forward_dir, new.pos);
	new_distance = distance(new_subtracted);

	if (new_distance < old_distance || hit->hit == 0)
	{
		(*hit) = new;
		img->hit_data.closest_id = id;
		img->hit_data.distance = new_distance;
	}
}

int	get_closest_hit(t_camera *cam, t_scene *img, t_hit *hit, int x, int y)
{
	t_object	*temp;
	t_hit		new = {0};

	temp = img->objects;
	img->hit_data.distance = FLT_MAX;
	img->hit_data.closest_id = INT_MAX;
	while (temp->next != NULL)
	{
		new = get_hit(cam, temp, x, y);
		if (new.hit == 1)
		{
			get_distance(img, cam, hit, new, temp->id);
		}
		temp = temp->next;
	}
	return (0);
}

void	set_id(t_scene *img)
{
	t_object	*temp;
	int			i;

	i = 1;
	temp = img->objects;
	while (temp->next)
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

	hit.hit = 0;
	img->hit_data.is_in_shadow = 0;
	img->hit_data.distance = FLT_MAX;
	int_col = 0;
	get_closest_hit(cam, img, &hit, x, y);
	if (hit.hit == 1)
	{
		get_shadow(img, &hit);
		get_normal(img, &hit);
		color = get_pixel_color(img, &hit);
		int_col = normalized_vec4_to_int(color);
		return (int_col);
	}
	else
		return (0x000000);
	return (0);
}

int	raytrace(t_scene *img)
{
	t_camera	cam;
	int			color;
	int			x;
	int			y;

	x = 0;
	y = 0;
	cam = img->camera;
	handle_window(img);
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
	return (0);
}
