/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:34:26 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/18 11:14:39 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

float	distance(t_vec3 vector1)
{
	float	ret;

	ret = dot_vector3(vector1, vector1);
	return (sqrtf(ret));
}

float	distance_2vecs(t_vec3 vector1, t_vec3 vector2)
{
	float	ret;

	ret = dot_vector3(vector1, vector2);
	return (sqrtf(ret));
}

t_vec3	vec3_sub(t_vec3 vector1, t_vec3 vector2)
{
	t_vec3	result;

	result.x = vector1.x - vector2.x;
	result.y = vector1.y - vector2.y;
	result.z = vector1.z - vector2.z;
	return (result);
}

float	dot_vector3(t_vec3 vector1, t_vec3 vector2)
{
	return ((vector1.x * vector2.x) + (vector1.y * vector2.y) \
	+ (vector1.z * vector2.z));
}

t_vec3	vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	temp;

	temp.x = vec1.x + vec2.x;
	temp.y = vec1.y + vec2.y;
	temp.z = vec1.z + vec2.z;
	return (temp);
}
