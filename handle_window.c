/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:32:59 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/13 12:46:16 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

int	key_event(int keycode, t_scene *img)
{
	if (keycode == 53)
	{
		//img not allocated yet
		//free(img);
		img = NULL;
		exit (0);
	}

	return (0);
}

int	exit_button(t_scene *img)
{
	//img not allocated yet
	//free(img);
	img = NULL;
	exit (0);
	return (0);
}

int	handle_window(t_scene *img)
{
	img->width = 640;
	img->height = 640;
	img->mlx = mlx_init();
	img->win = mlx_new_window(img->mlx, img->width, img->height, \
	"test_window");
	mlx_hook(img->win, 2, 1L << 0, &key_event, img);
	mlx_hook(img->win, 17, 1L << 17, &exit_button, img);
	return (0);
}
