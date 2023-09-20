/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:32:54 by rmakinen          #+#    #+#             */
/*   Updated: 2023/09/20 10:27:12 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT
# define MINI_RT

# include <fcntl.h>
# include <float.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdint.h>
# include <mlx.h>
# include <stdlib.h>
# include "parser.h"
# include "../libft/includes/libft.h"

typedef struct s_vec3 t_vec3;
typedef struct s_scene t_scene;
typedef struct s_camera t_camera;
typedef struct s_hit t_hit;

typedef struct s_object	t_object;
typedef struct s_cylinder t_cylinder;
typedef struct s_plane t_plane;
typedef struct s_sphere	t_sphere;


//window
int		handle_window(t_scene *img);
int		exit_button(t_scene *img);

//drawing
int		draw_img(t_scene *img);
int		draw_sphere(t_camera *cam, t_scene *img, int x, int y);

//vector and coordinate manipulation
t_vec3	vec3_sub(t_vec3 vector1, t_vec3 vector2);
float	distance(t_vec3 vector1);
float	dot_vector3(t_vec3 vector1, t_vec3 vector2);

//camera
void	get_ray_direction(t_camera *cam, t_scene *img, int x, int y);

//scene
int		get_closest_hit(t_camera *cam, t_scene *img, t_hit *hit, int x, int y);
void	get_distance(t_scene *img, t_camera *cam, t_hit *hit, int id);
void	get_normal(t_scene *img, t_hit *hit);

//ray_hit
t_hit	get_hit(t_camera *cam, t_object *objects, float x, float y);

#endif
