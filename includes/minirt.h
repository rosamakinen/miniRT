/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:32:54 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/14 11:08:59 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT
# define MINI_RT

# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdint.h>
# include <mlx.h>
# include <stdlib.h>
# include "parser.h"
#include "../libft/includes/libft.h"

typedef struct s_vec3 t_vec3;
typedef struct s_scene t_scene;
typedef struct s_camera t_camera;

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
