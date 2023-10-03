/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:32:54 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/03 11:49:09 by rmakinen         ###   ########.fr       */
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
# include <limits.h>
# include "parser.h"
# include "../libft/includes/libft.h"
//# include "../mlx/mlx.h"

typedef struct s_vec3 t_vec3;
typedef struct s_vec4 t_vec4;
typedef struct s_scene t_scene;
typedef struct s_camera t_camera;
typedef struct s_hit t_hit;

typedef struct s_object	t_object;
typedef struct s_cylinder t_cylinder;
typedef struct s_plane t_plane;
typedef struct s_sphere	t_sphere;


//window
int			handle_window(t_scene *img);
int			exit_button();

//drawing
int			draw_img(t_scene *img);
int			draw_sphere(t_camera *cam, t_scene *img, int x, int y);

//vectors.c
float		distance(t_vec3 vector1);
float		dot_vector3(t_vec3 vector1, t_vec3 vector2);
t_vec3		vec3_sub(t_vec3 vector1, t_vec3 vector2);
t_vec3		vec3_normalize(t_vec3 vector);

//camera.c
void		get_ray_direction(t_camera *cam, t_scene *img, int x, int y);

//scene.c
int			get_closest_hit(t_camera *cam, t_scene *img, t_hit *hit, int x, int y);
float		get_brightness(t_scene *img, t_hit *hit);
void		get_distance(t_scene *img, t_camera *cam, t_hit *hit, int id);
void		set_id(t_scene *img);

//normals.c
void		get_normal(t_scene *img, t_hit *hit);
void		get_plane_normal(t_object *data, t_scene *img);
void		get_sphere_normal(t_object *data, t_scene *img, t_hit *hit);

//ray_hit.c
t_hit		get_hit(t_camera *cam, t_object *objects, float x, float y);

//light.c
t_vec4		add_ambient_value(t_scene *img);


//colors.c
t_vec4		get_pixel_color(t_scene *img, t_hit *hit);

//color_math.c
t_vec4		int_to_vec4(int color);
t_vec4		multiply_vec4_float(t_vec4 color, float value);
t_vec4		multiply_vec4(t_vec4 color, t_vec4 multiplier);
t_vec4		add_vec4_float(t_vec4 color, float value);
t_vec4		add_vec4(t_vec4 color, t_vec4 added);

//color_math2.c
int			normalized_vec4_to_int(t_vec4 color);
void		normalize_color_vec4(t_vec4 *color);
t_vec4		clamp_vec4(t_vec4 color);
float		clamp_color(float vec_color);

//object_color.c
void		get_object_basecolor(t_scene *img);
void		get_sphere_color(t_object *data, t_scene *img);
void		get_cylinder_color(t_object *data, t_scene *img);
void		get_plane_color(t_object *data, t_scene *img);

//testing_hit_funcs.c
int			infinite_cylinder_hit(const t_vec3 *ray_origin, const t_vec3 *ray_direction, const t_cylinder *cylinder, t_vec3 *intersection1, t_vec3 *intersection2);
int			sphere_hit(const t_sphere *sphere, const t_vec3 *ray_start, const t_vec3 *direction, t_vec3 *intersection1, t_vec3 *intersection2);
int			plane_hit(const t_vec3 *ray_origin, const t_vec3 *direction, const t_plane *plane, t_vec3 *intersectionPoint);

#endif
