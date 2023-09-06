/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:32:54 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/06 12:12:25 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT
# define MINI_RT

#include <mlx.h>
#include <stdlib.h>

typedef struct	s_window
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
}			t_window;

typedef struct	s_camera
{
	float	x;
	float	y;
	float	z;
}			t_camera;

//window
int	handle_window(t_window *img);
int	exit_button(t_window *img);

//drawing
int	draw_circle(t_window *img);
int	draw_img(t_window *img);
int	draw_sphere(t_window *img, int x, int y);

//camera
void	normalize_coordinates(t_window *img, t_camera *cam);

#endif
