/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ambient_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:26:17 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/09/13 11:48:22 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

short	get_ambient_light(t_scene *scene, const char *str)
{
	int	i;

	i = 2;
	if (get_float(&scene->ambient_light.ratio, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	if (get_color(&scene->ambient_light.color, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	scene->check_once.ambient_light++;
	if (scene->check_once.ambient_light > 1)
		return (INVALID_INPUT);
	return (EXIT_SUCCESS);
}
