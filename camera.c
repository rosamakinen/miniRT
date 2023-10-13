/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:18:33 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/13 08:03:53 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./includes/minirt.h"

// void	get_ray_direction(t_camera *cam, t_scene *img, int img_x, int img_y)
// {
// 	float normal_x;
// 	float normal_y;

// 	if (img_x < img->width / 2)
// 		normal_x = img->width / 2 - img_x;
// 	else
// 		normal_x = img_x - img->width / 2;

// 	if (img_y > img->height / 2)
// 		normal_y = img->height / 2 - img_y;
// 	else
// 		normal_y = img_y - img->height / 2;

// 	cam->norm_coord.x = normal_x;
// 	cam->norm_coord.y = normal_y;
// 	cam->norm_coord.z = -1;
// }
