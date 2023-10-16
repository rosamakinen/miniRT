/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:32:54 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/16 11:49:37 by rmakinen         ###   ########.fr       */
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
# include "vectors.h"
# include "../libft/includes/libft.h"
//# include "../mlx/mlx.h"

# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 1080

typedef struct s_vec3 t_vec3;
typedef struct s_vec4 t_vec4;
typedef struct s_scene t_scene;
typedef struct s_camera t_camera;
typedef struct s_hit t_hit;
typedef struct s_float_vec3 t_float_vec3;

typedef struct s_object	t_object;
typedef struct s_cylinder t_cylinder;
typedef struct s_plane t_plane;
typedef struct s_sphere	t_sphere;


//window
int			handle_window(t_scene *img);
int			exit_button();

//drawing
int			draw_img(t_scene *img);

//scene.c
int			get_closest_hit(t_camera *cam, t_scene *img, t_hit *hit, int x, int y);
void		get_distance(t_scene *img, t_camera *cam, t_hit *hit, t_hit new, int id);
void		set_id(t_scene *img);

//ray_hit.c
t_hit		get_hit(t_camera *cam, t_object *objects, float x, float y);
int			plane_hit(t_vec3 origin, t_vec3 direction, t_plane plane, t_vec3 *point);
int			sphere_hit(const t_sphere *sphere, const t_vec3 ray_start, const t_vec3 direction, t_vec3 *intersection1, t_vec3 *intersection2);

//normals.c
void		get_normal(t_scene *img, t_hit *hit);
void		get_plane_normal(t_object *data, t_scene *img);
void		get_sphere_normal(t_object *data, t_scene *img, t_hit *hit);

//light.c
t_vec4		add_ambient_value(t_scene *img);
t_vec4		get_white_light(void);
float		get_brightness(t_scene *img, t_hit *hit);

//shadows.c
void		get_shadow(t_scene *img, t_hit *hit);
int			check_for_shadow(t_scene *img, t_hit *hit, t_object *object);
int			check_sphere_shadow(t_hit *hit, t_object *object, t_vec3 shadow_direction, t_float_vec3 data);
int			check_plane_shadow(t_hit *hit, t_object *object, t_vec3 shadow_direction, t_float_vec3 data);

//colors.c
t_vec4		get_pixel_color(t_scene *img, t_hit *hit);

//cylinder.c
t_hit		find_cylinder_hit(t_cylinder *cylinder, t_vec3 ray_direction, t_vec3 start_pos);


//object_color.c
void		get_object_basecolor(t_scene *img);
void		get_sphere_color(t_object *data, t_scene *img);
void		get_cylinder_color(t_object *data, t_scene *img);
void		get_plane_color(t_object *data, t_scene *img);

#endif
