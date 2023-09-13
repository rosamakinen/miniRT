/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light_source.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:17:37 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/09/13 14:55:50 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

short	get_light_source(t_scene *scene, const char *str)
{
	int	i;

	i = 2;
	if (get_3d_coordindate(&scene->light_sources.pos, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	if (get_float(&scene->light_sources.ratio, str, &i) == EXIT_FAILURE)
		return (INVALID_INPUT);
	if (str[i] && str[i] != '\n')
		return (INVALID_INPUT);
	scene->check_once.light_source++;
	if (scene->check_once.light_source > 1)
		return (EXCESS_ELEMENTS);
	return (EXIT_SUCCESS);
}
