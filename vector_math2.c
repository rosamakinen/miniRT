/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:36:10 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/14 12:37:25 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

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

	temp.x = - vector.x;
	temp.y = - vector.y;
	temp.z = - vector.z;
	return(temp);
}
