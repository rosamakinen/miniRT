/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:50:20 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/17 13:08:32 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

//rosa trying to troubleshoot why the camera test with the y does not work
// static void find_up_and_right_vecs(t_camera *camera)
// {
// 	camera->forward_dir = camera->norm_vector;
// 	printf("before we got right_dir %f, %f, %f\n and up_dir %f,%f, %f\n and forward_dir %f, %f, %f\n", camera->right_dir.x, camera->right_dir.y, camera->right_dir.z, camera->up_dir.x, camera->up_dir.y, camera->up_dir.z,camera->forward_dir.x, camera->forward_dir.y,camera->forward_dir.z);
// 	camera->right_dir = cross_product(camera->forward_dir, (t_vec3){0, 1.0, 0.00001});
// 	vec3_normalize(camera->right_dir);
// 	camera->up_dir = cross_product(camera->right_dir, camera->forward_dir);
// 	vec3_normalize(camera->up_dir);
// 	printf("after we got right_dir %f, %f, %f\n and up_dir %f,%f, %f\n and forward_dir %f, %f, %f\n", camera->right_dir.x, camera->right_dir.y, camera->right_dir.z, camera->up_dir.x, camera->up_dir.y, camera->up_dir.z,camera->forward_dir.x, camera->forward_dir.y,camera->forward_dir.z);
// }

//another version, why in the original we are checking forward_dir before initializing it.
// static void find_up_and_right_vecs(t_camera *camera)
// {
// 	t_vec3	initialUp;

// 	camera->forward_dir = camera->norm_vector;
// 	printf("before we got right_dir %f, %f, %f\n and up_dir %f,%f, %f\n and forward_dir %f, %f, %f\n", camera->right_dir.x, camera->right_dir.y, camera->right_dir.z, camera->up_dir.x, camera->up_dir.y, camera->up_dir.z,camera->forward_dir.x, camera->forward_dir.y,camera->forward_dir.z);
// 	if (camera->forward_dir.y < 0.0)
// 	{
// 		initialUp = (t_vec3){0.0, -1.0, 0.0};
// 	}
// 	else
// 	{
// 		initialUp = (t_vec3){0.0, 1.0, 0.0};
// 	}
// 	camera->right_dir = cross_product(camera->forward_dir, initialUp);
// 	camera->right_dir = vec3_normalize(camera->right_dir);
// 	camera->up_dir = cross_product(camera->right_dir, camera->forward_dir);
// 	camera->up_dir = vec3_normalize(camera->up_dir);
// 	printf("after we got right_dir %f, %f, %f\n and up_dir %f,%f, %f\n and forward_dir %f, %f, %f\n", camera->right_dir.x, camera->right_dir.y, camera->right_dir.z, camera->up_dir.x, camera->up_dir.y, camera->up_dir.z,camera->forward_dir.x, camera->forward_dir.y,camera->forward_dir.z);
// }

static void find_up_and_right_vecs(t_camera *camera)
{
    t_vec3 initialUp;


	printf("we got right_dir %f, %f, %f\n", camera->norm_vector.x * 3, camera->norm_vector.y * 3, camera->norm_vector.z * 3);
	if (fabsf(camera->norm_vector.y) > 1.0f - TINY_VALUE) {
        initialUp = (t_vec3){0.0, 0.0, (-1) * (camera->norm_vector.y < 0) + (1) * (camera->norm_vector.y > 0)};
    }
	else {
        initialUp = (t_vec3){0.0, 1.0, 0.0};
    }
	camera->forward_dir = camera->norm_vector;
	camera->right_dir = cross_product(camera->forward_dir, initialUp);
    camera->right_dir = vec3_normalize(camera->right_dir);
	camera->up_dir = cross_product(camera->right_dir, camera->forward_dir);
	camera->up_dir = vec3_normalize(camera->up_dir);
	printf("we got right_dir %f, %f, %f\n and up_dir %f,%f, %f\n and forward_dir %f, %f, %f\n", camera->right_dir.x * 3, camera->right_dir.y * 3, camera->right_dir.z * 3, camera->up_dir.x * 3, camera->up_dir.y * 3, camera->up_dir.z * 3,camera->forward_dir.x * 3, camera->forward_dir.y * 3,camera->forward_dir.z * 3);
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
