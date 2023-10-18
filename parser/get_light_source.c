/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light_source.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:17:37 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/18 10:02:13 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

short	get_light_source(t_scene *scene, const char *str)
{
	int	i;

	i = 2;
	if (get_vec3(&scene->light_sources.pos, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	if (get_float(&scene->light_sources.ratio, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	if (scene->light_sources.ratio > 1.0 || scene->light_sources.ratio < 0.0)
		return (INVALID_INPUT);
	if (get_color(&scene->light_sources.color, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	if (str[i] && str[i] != '\n')
		return (INVALID_INPUT);
	scene->check_once.light_source++;
	if (scene->check_once.light_source > 1)
		return (EXCESS_ELEMENTS);
	return (EXIT_SUCCESS);
}
