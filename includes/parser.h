/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:19:26 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/09/14 07:56:55 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: Remove the following subject notes
//START
/*
◦ Ambient lightning:
	A 0.2 255,255,255
	∗ identifier: A
	∗ ambient lighting ratio in range [0.0,1.0]: 0.2
	∗ R,G,B colors in range [0-255]: 255, 255, 255
◦ Camera:
	C -50.0,0,20 0,0,1 70
	∗ identifier: C
	∗ x,y,z coordinates of the view point: -50.0,0,20
	∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
	0.0,0.0,1.0
	∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
◦ Light:
	L -40.0,50.0,0.0 0.6 10,0,255
	∗ identifier: L
	∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
	∗ the light brightness ratio in range [0.0,1.0]: 0.6
	∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
◦ Sphere:
	sp 0.0,0.0,20.6 12.6 10,0,255
	∗ identifier: sp
	∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
	∗ the sphere diameter: 12.6
	∗ R,G,B colors in range [0-255]: 10, 0, 255
◦ Plane:
	pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
	∗ identifier: pl
	∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
	∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
	∗ R,G,B colors in range [0-255]: 0,0,225
◦ Cylinder:
	cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
	∗ identifier: cy
	∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
	∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
	0.0,0.0,1.0
	∗ the cylinder diameter: 14.2
	∗ the cylinder height: 21.42
	∗ R,G,B colors in range [0,255]: 10, 0, 255
*/
//FINISH
#ifndef PARSER_H
# define PARSER_H
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# define OPEN_FAIL 1
# define INVALID_OBJECTS 2
# define MISSING_KEY_ELEMENTS 3
# define INVALID_INPUT 4
# define MALLOC_FAILED 5
# define LIGHT_SOURCE 0
# define AMBIENT_LIGHT 1
# define CAMERA 2
# define VALID_OBJECT 3
# define OBJECT_SPHERE 4
# define OBJECT_PLANE 5
# define OBJECT_CYLINDER 6

//TODO: Add the following structs to the main header file preferably
//START

typedef unsigned int	t_color;
typedef short			t_degrees;
typedef short			t_object_type;

typedef struct s_check_once
{
	int				light_source;
	int				camera;
	int				ambient_light;
}	t_check_once;

typedef struct s_vec3
{
	float			x;
	float			y;
	float			z;
}	t_vec3;

typedef struct s_object
{
	void			*data;
	struct s_object	*next;
	t_object_type	type;
}	t_object;

typedef struct s_cylinder
{
	t_vec3			pos;
	t_vec3			axis_vector;
	float			diameter;
	float			height;
	t_color			color;
}	t_cylinder;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal_vector;
	t_color		color;
}	t_plane;

typedef struct s_sphere
{
	t_vec3		pos;
	float		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_light_source
{
	t_vec3		pos;
	float		ratio;
	//WARNING: only add next two if we do bonus
	//START
	//t_color				color;
	//struct s_light_source	*next;
	//FINISH
}	t_light_source;

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			norm_vector;
	t_vec3			norm_coord;
	t_degrees			fov;
}	t_camera;

typedef struct s_ambient_light
{
	float			ratio;
	t_color			color;
}	t_ambient_light;

typedef struct s_scene
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	t_light_source	light_sources; //The reason why this is not pointer is that it must exist always
	t_ambient_light	ambient_light; // ^
	t_camera		camera; //        ^^
	t_object		*objects;
	t_check_once	check_once; //this is to check if we only got one light, camera and ambient light
	short			error_catcher;
}	t_scene;
//FINISH

t_scene		scene_constractor(const char *file);

// ft_print_error.c
int			ft_print_error(const char *str);
int			return_parser_error(short error);

// //ft_strlen.c
// int			ft_strlen(const char *str);

//get_object_identifier.c
short		get_object_identifier(const char *str);
int			check_valid_object(const char *str);

//ft_atoX.c
float		ft_atof(const char *str, int *index);
int			is_digit_mod(int a, short allow_neg, short allow_plus);
uint8_t		ft_atouint8(const char *str, int *index);
int			ft_atoi_mod(const char *str, int *index);

//parser_utils.c
int			get_float(float *dst, const char *str, int *index);
int			get_3d_coordindate(t_vec3 *coordinate,
				const char *str, int *index);
int			skip_chars(const char *skippable, int index, const char *str);
int			get_color(t_color *color, const char *str, int *index);
int			get_degrees(t_degrees *dst, const char *str, int *index);
int			get_3d_normal_vector(t_vec3 *coordinate, const char *str,
				int *index);

//get_light_source.c
short		get_light_source(t_scene *scene, const char *str);

//get_ambient_light.c
short		get_ambient_light(t_scene *scene, const char *str);

//get_camera.c
short		get_camera(t_scene *scene, const char *str);

//get_new_object.c
short		get_new_object(t_object *scene_object, const char *str);
#endif
