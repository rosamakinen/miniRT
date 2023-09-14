/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:32:54 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/14 07:39:50 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT
# define MINI_RT

#include <mlx.h>
#include <stdlib.h>
#include "vectors.h"
#include "parser.h"

typedef struct s_vec3 t_vec3;

// typedef struct	s_window
// {
// 	int		width;
// 	int		height;
// 	void	*mlx;
// 	void	*win;
// }			t_window;

// typedef struct	s_camera
// {
// 	int	normal_x;
// 	int	normal_y;
// 	t_vec3	ray_direction;
// 	t_vec3	cam_position; // ray_origin
// }			t_camera;

//window
int	handle_window(t_scene *img);
int	exit_button(t_scene *img);

//drawing
int	draw_img(t_scene *img);
int	draw_sphere(t_camera *cam, t_scene *img, int x, int y);

t_vec3	vec_sub(t_vec3 vector1, t_vec3 vector2);

//camera
void	get_ray_direction(t_camera *cam, t_scene *img, int x, int y);
#endif
