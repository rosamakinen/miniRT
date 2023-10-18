/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:36:10 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/18 11:16:02 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec3	cross_product(t_vec3 vector1, t_vec3 vector2)
{
	t_vec3	result;

	result.x = vector1.y * vector2.z - vector1.z * vector2.y;
	result.y = vector1.z * vector2.x - vector1.x * vector2.z;
	result.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return (result);
}

t_vec3	vec3_scalar_multiplication(t_vec3 v, float s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
}

t_vec3	vec3_scalar_division(t_vec3 v, float s)
{
	return ((t_vec3){v.x * s, v.y * s, v.z * s});
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

t_vec3	vec3_negative(t_vec3 vector)
{
	t_vec3	temp;

	temp.x = -1 * vector.x;
	temp.y = -1 * vector.y;
	temp.z = -1 * vector.z;
	return (temp);
}
