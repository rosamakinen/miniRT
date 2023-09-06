/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:18:33 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/06 12:15:49 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"
#include "./includes/vectors.h"

void	normalize_coordinates(t_window *img, t_camera *cam)
{
	float	x;
	float	y;

	y = 0;
	x = 0;
	while(x < img->width)
	{
		y = 0;
		while(y < img->height)
		{
			//normalize the coordinates for the image
			cam->x = 0;
			y++;
		}
		x++;
	}
}
