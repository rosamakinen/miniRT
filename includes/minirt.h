/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:32:54 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/19 20:00:11 by mkaratzi         ###   ########.fr       */
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
typedef struct s_object	t_object;


typedef struct s_cylinder t_cylinder;
typedef struct s_plane t_plane;
typedef struct s_sphere	t_sphere;

//window
int	handle_window(t_scene *img);
int	exit_button(t_scene *img);

//drawing
int	draw_img(t_scene *img);
int	draw_sphere(t_camera *cam, t_scene *img, int x, int y);

t_vec3	vec_sub(t_vec3 vector1, t_vec3 vector2);

//camera
void	get_ray_direction(t_camera *cam, t_scene *img, int x, int y);

//testing_hit_funcs.c
int infinite_cylinder_hit(const t_vec3 *ray_origin, const t_vec3 *ray_direction, const t_cylinder *cylinder, t_vec3 *intersection1, t_vec3 *intersection2);
int sphere_hit(const t_sphere *sphere, const t_vec3 *ray_start, const t_vec3 *direction, t_vec3 *intersection1, t_vec3 *intersection2);
int plane_hit(const t_vec3 *ray_origin, const t_vec3 *direction, const t_plane *plane, t_vec3 *intersectionPoint);

#endif
