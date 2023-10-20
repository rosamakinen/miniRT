/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_identifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 11:57:12 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/20 12:33:07 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	check_valid_object(const char *str)
{
	if (str[0] == 's' && str[1] == 'p' && str[2] == ' ' && ft_strlen(str) > 4)
		return (1);
	if (str[0] == 'p' && str[1] == 'l' && str[2] == ' ' && ft_strlen(str) > 4)
		return (1);
	if (str[0] == 'c' && str[1] == 'y' && str[2] == ' ' && ft_strlen(str) > 4)
		return (1);
	return (INVALID_OBJECTS);
}

short	get_object_identifier(const char *str)
{
	if (str[0] == 'L' && str[1] == ' ' && ft_strlen(str) > 4)
		return (LIGHT_SOURCE);
	if (str[0] == 'C' && str[1] == ' ' && ft_strlen(str) > 4)
		return (CAMERA);
	if (str[0] == 'A' && str[1] == ' ' && ft_strlen(str) > 4)
		return (AMBIENT_LIGHT);
	if (check_valid_object(str) != INVALID_OBJECTS)
		return (VALID_OBJECT);
	return (INVALID_OBJECTS);
}
