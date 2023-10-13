/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:32:59 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/13 08:46:22 by rmakinen         ###   ########.fr       */
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
	img->width = WINDOW_WIDTH;
	img->height = WINDOW_HEIGHT;
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, img->width, img->height, \
	"miniRT");
	mlx_hook(img->win, 2, 1L << 0, &key_event, img);
	mlx_hook(img->win, 17, 1L << 17, &exit_button, img);
	return (0);
}
