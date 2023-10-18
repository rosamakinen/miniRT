/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:52:37 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/18 16:25:09 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_vec3	closest_point_to_line(t_vec3 start, t_vec3 end, t_vec3 point, \
	t_cylinder *cylinder)
{
	t_vec3	line_ve;
	t_vec3	point_to_point;
	float	dist;
	float	dot;

	line_ve = vec3_sub(end, start);
	line_ve = vec3_normalize(line_ve);
	point_to_point = vec3_sub(point, start);
	dot = dot_vector3(line_ve, line_ve);
	if (dot < 0.0001)
		return ((t_vec3){FLT_MAX, FLT_MAX, FLT_MAX});
	dist = dot_vector3(point_to_point, line_ve) / dot;
	start = (t_vec3){start.x + dist * line_ve.x, start.y + dist \
		* line_ve.y, start.z + dist * line_ve.z};
	if (distance(vec3_sub(start, cylinder->pos)) > cylinder->height / 2)
		return ((t_vec3){FLT_MAX, FLT_MAX, FLT_MAX});
	return (start);
}

int	find_best_hit(t_vec3 *intersection1, t_vec3 *intersection2, t_vec3 start, \
	t_cylinder *cylinder)
{
	int	check[2];

	check[0] = check_hit(cylinder, *intersection1);
	check[1] = check_hit(cylinder, *intersection2);
	if (check[0] && !check[1])
		return (1);
	else if (!check[0] && check[1])
	{
		*intersection1 = *intersection2;
		return (1);
	}
	else if (!check[0] && !check[1])
		return (0);
	else if (check[0] && check[1])
	{
		*intersection1 = dist_compare(start, *intersection1, *intersection2);
		return (1);
	}
	return (0);
}

static t_vec3	vector_constructor(t_vec3 start, float scalar, \
	t_vec3 multiplier)
{
	t_vec3	answer;

	answer = (t_vec3){start.x + scalar * multiplier.x, \
		start.y + scalar * multiplier.y, start.z + scalar \
		* multiplier.z};
	return (answer);
}

int	infinite_cylinder_hit(t_vec3 start, t_vec3 ray_direction, \
	t_cylinder *cylinder, t_vec3 *intersection1)
{
	t_vec3		one;
	t_vec3		two;
	t_quadratic	formula;

	cylinder->axis_vector = vec3_normalize(cylinder->axis_vector);
	one = vec3_sub(ray_direction, \
		vec3_scalar_multiplication(cylinder->axis_vector, \
			dot_vector3(ray_direction, cylinder->axis_vector)));
	two = vec3_sub(vec3_sub(start, cylinder->pos), \
		vec3_scalar_multiplication(cylinder->axis_vector, \
		dot_vector3(vec3_sub(start, cylinder->pos), cylinder->axis_vector)));
	formula.a = dot_vector3(one, one);
	formula.b = 2 * dot_vector3(one, two);
	formula.c = dot_vector3(two, two) - ((cylinder->diameter / 2) \
		* (cylinder->diameter / 2));
	formula.discriminant = formula.b * formula.b - 4 * formula.a * formula.c;
	if (formula.discriminant < 0)
		return (0);
	formula.c = (-formula.b + sqrt(formula.discriminant)) / (2 * formula.a);
	formula.a = (-formula.b - sqrt(formula.discriminant)) / (2 * formula.a);
	*intersection1 = vector_constructor(start, formula.c, ray_direction);
	two = vector_constructor(start, formula.a, ray_direction);
	return (find_best_hit(intersection1, &two, start, cylinder));
}
