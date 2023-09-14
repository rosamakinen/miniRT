/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:50:20 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/09/14 10:59:02 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

short	get_camera(t_scene *scene, const char *str)
{
	int	i;

	i = 2;
	if (get_vec3(&scene->camera.pos, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	if (get_3d_normal_vector(&scene->camera.norm_vector, str, &i)
		== EXIT_FAILURE)
		return (INVALID_INPUT);
	if (get_degrees(&scene->camera.fov, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	if (str[i] && str[i] != '\n')
		return (INVALID_INPUT);
	scene->check_once.camera++;
	if (scene->check_once.camera > 1)
		return (EXCESS_ELEMENTS);
	return (EXIT_SUCCESS);
}
