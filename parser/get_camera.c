/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:50:20 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/18 17:25:40 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	find_up_and_right_vecs(t_camera *camera)
{
	t_vec3	initial_up;

	if (fabsf(camera->norm_vector.y) > (1.0f - TINY_VALUE))
	{
		initial_up = (t_vec3){0.0, 0.0, (-1) * (camera->norm_vector.y < 0) \
		+ (1) * (camera->norm_vector.y > 0)};
	}
	else
		initial_up = (t_vec3){0.0, 1.0, 0.0};
	camera->forward_dir = camera->norm_vector;
	camera->right_dir = cross_product(camera->forward_dir, initial_up);
	camera->right_dir = vec3_normalize(camera->right_dir);
	camera->up_dir = cross_product(camera->right_dir, camera->forward_dir);
	camera->up_dir = vec3_normalize(camera->up_dir);
}

short	get_camera(t_scene *scene, const char *str)
{
	int	i;

	i = 2;
	if (get_vec3(&scene->camera.pos, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	if (get_3d_normal_vector(&scene->camera.norm_vector, str, &i)
		== EXIT_FAILURE)
		return (INVALID_INPUT);
	scene->camera.norm_vector = vec3_normalize(scene->camera.norm_vector);
	find_up_and_right_vecs(&scene->camera);
	if (get_degrees(&scene->camera.fov, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	if (str[i] && str[i] != '\n')
		return (INVALID_INPUT);
	scene->check_once.camera++;
	if (scene->check_once.camera > 1)
		return (EXCESS_ELEMENTS);
	return (EXIT_SUCCESS);
}
