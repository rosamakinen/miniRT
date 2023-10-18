/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:15:38 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/18 16:32:52 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	ft_print_error(const char *str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			write(STDERR_FILENO, &str[i], 1);
	}
	return (i);
}

int	return_parser_error(short error)
{
	if (error == OPEN_FAIL)
		ft_print_error("Error\nFailed to open given file!\n");
	if (error == INVALID_INPUT)
		ft_print_error("Error\nDetected invalid input in the given file!\n");
	if (error == MALLOC_FAILED)
		ft_print_error("Error\nSuprise, suprise.... Malloc failed!\n");
	if (error == INVALID_OBJECTS)
		ft_print_error("Error\nSorry, you used an object we can't handle!\n");
	if (error == MISSING_KEY_ELEMENTS)
		ft_print_error("Error\nSorry, you forgot to add key elements!\n");
	if (error == EXCESS_ELEMENTS)
		ft_print_error("Error\nSorry, you added more elements than needed!\n");
	return (1);
}
