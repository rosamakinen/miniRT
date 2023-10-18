/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:19:18 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/18 16:30:06 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	check_hit(t_cylinder *cylinder, t_vec3 hitpoint)
{
	t_vec3	top_cap;
	t_vec3	bottom_cap;
	t_vec3	inverse;

	inverse = vec3_negative(cylinder->axis_vector);
	top_cap = vec3_add(cylinder->pos, \
		vec3_scalar_multiplication(cylinder->axis_vector, \
		cylinder->height / 2));
	bottom_cap = vec3_add(cylinder->pos, vec3_scalar_multiplication(inverse, \
		cylinder->height / 2));
	top_cap = closest_point_to_line(top_cap, bottom_cap, hitpoint, cylinder);
	if (top_cap.x == FLT_MAX || top_cap.y == FLT_MAX || top_cap.z == FLT_MAX)
		return (0);
	return (1);
}

t_vec3	dist_compare(t_vec3 start, t_vec3 one, t_vec3 two)
{
	float	dist_one;
	float	dist_two;

	dist_one = distance(vec3_sub(start, one));
	dist_two = distance(vec3_sub(start, two));
	if (dist_one < dist_two)
		return (one);
	return (two);
}

void	translate_t_vec3s(float *x, float *y, float aspect_ratio, float fov)
{
	*x = (1.0f - (2.0f * (*x + 0.5f) / WINDOW_WIDTH)) * \
		aspect_ratio * tanf(fov * (M_PI / 360));
	*y = (1.0f - (2.0f * (*y + 0.5f) / WINDOW_HEIGHT)) * \
		tanf(fov * (M_PI / 360));
	*x = *x * -1.0f;
}
