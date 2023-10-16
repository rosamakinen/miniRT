/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:58:16 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/16 11:04:43 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
# include "minirt.h"

typedef struct s_vec3 t_vec3;
typedef struct s_vec4 t_vec4;

//vectors_math.c
float		distance(t_vec3 vector1);
float		distance_2vecs(t_vec3 vector1, t_vec3 vector2);
t_vec3		vec3_sub(t_vec3 vector1, t_vec3 vector2);
float		dot_vector3(t_vec3 vector1, t_vec3 vector2);
t_vec3		vec3_add(t_vec3 vec1, t_vec3 vec2);

//vectors_math2.c
t_vec3		cross_product(t_vec3 vector1, t_vec3 vector2);
t_vec3		vec3_scalar_multiplication(t_vec3 v, float s);
t_vec3		vec3_scalar_division(t_vec3 v, float s);
t_vec3		vec3_normalize(t_vec3 vector);
t_vec3		vec3_negative(t_vec3 vector);

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

#endif
