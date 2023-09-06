/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:29:32 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/06 12:07:50 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/includes/libft.h"
#include "./libft/includes/ft_printf.h"
#include "./includes/minirt.h"

int	main(int argc, char **argv)
{
	t_window	img;
	if (argc == 1)
	{
		ft_printf("%s\n", argv[0]);
		ft_printf("this is the start\n");
		handle_window(&img);
		draw_img(&img);
		mlx_loop(img.mlx);
	}
	return(0);
}
