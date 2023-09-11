/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 10:15:38 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/09/09 13:04:12 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		ft_print_error("Failed to open given file!\n");
	if (error == INVALID_INPUT)
		ft_print_error("Detected invalid input in the given file!\n");
	return (1);
}
