/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:29:32 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/04 11:20:25 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/includes/libft.h"
#include "./libft/includes/ft_printf.h"

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_printf("%s\n", argv[0]);
		ft_printf("this is the start\n");
	}
	return(0);
}
