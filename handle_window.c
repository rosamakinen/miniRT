/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:32:59 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/03 11:51:44 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

int	key_event(int keycode)
{
	if (keycode == 53)
		exit (0);
	return (0);
}

int	exit_button(void)
{
	exit (0);
	return (0);
}

int	handle_window(t_scene *img)
{
	img->width = 1080;
	img->height = 1080;
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, img->width, img->height, \
	"test_window");
	mlx_hook(img->win, 2, 1L << 0, &key_event, img);
	mlx_hook(img->win, 17, 1L << 17, &exit_button, img);
	return (0);
}
