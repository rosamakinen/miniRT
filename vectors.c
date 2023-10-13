/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 06:34:26 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/13 16:22:20 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

float	distance(t_vec3 vector1)
{
	float	ret;

	ret = dot_vector3(vector1, vector1);
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

t_vec3	vec3_normalize(t_vec3 vector)
{
	float	magnitude;

	magnitude = distance(vector);
	if (magnitude > 0)
	{
		vector.x /= magnitude;
		vector.y /= magnitude;
		vector.z /= magnitude;
	}
	return (vector);
}

t_vec3    cross_product(t_vec3 vector1, t_vec3 vector2)
{
    t_vec3 result;

    result.x = vector1.y * vector2.z - vector1.z * vector2.y;
    result.y = vector1.z * vector2.x - vector1.x * vector2.z;
    result.z = vector1.x * vector2.y - vector1.y * vector2.x;
    return (result);
}

t_vec3 vec3_add(t_vec3 vec1, t_vec3 vec2)
{
	t_vec3	temp;

	temp.x = vec1.x + vec2.x;
	temp.y = vec1.y + vec2.y;
	temp.z = vec1.z + vec2.z;
	return (temp);
}

t_vec3	vec3_negative(t_vec3 vector)
{
	t_vec3	temp;

	temp.x = - vector.x;
	temp.y = - vector.y;
	temp.z = - vector.z;
	return(temp);
}
