/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_identifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:57:12 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/09/14 10:59:02 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	check_valid_object(const char *str)
{
	if (str[0] == 's' && str[1] == 'p' && str[2] == ' ')
		return (1);
	if (str[0] == 'p' && str[1] == 'l' && str[2] == ' ')
		return (1);
	if (str[0] == 'c' && str[1] == 'y' && str[2] == ' ')
		return (1);
	return (0);
}

short	get_object_identifier(const char *str)
{
	if (str[0] == 'L' && str[1] == ' ')
		return (LIGHT_SOURCE);
	if (str[0] == 'C' && str[1] == ' ')
		return (CAMERA);
	if (str[0] == 'A' && str[1] == ' ')
		return (AMBIENT_LIGHT);
	if (check_valid_object(str))
		return (VALID_OBJECT);
	return (INVALID_OBJECTS);
}
