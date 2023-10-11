/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:26:03 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/11 10:26:47 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

t_vec4	add_ambient_value(t_scene *img)
{
	t_vec4	ambient;
	t_vec4	ambient_color;

	ambient_color = int_to_vec4(img->ambient_light.color);
	normalize_color_vec4(&ambient_color);
	ambient = multiply_vec4_float(ambient_color, img->ambient_light.ratio);
	return (ambient);
}

// t_vec4	get_specular(t_scene *img)
// {
// 	t_vec4	specular_angle;
// 	t_vec4	specular;

// 	specular_angle = fmaxf(dot(reflectDir, viewDir), 0.0);
// 	specular = pow(specular_angle, shininess);

// 	return (specular);

    // vec3 halfDir = normalize(lightDir + viewDir);
    // float specAngle = max(dot(halfDir, normal), 0.0);
    // specular = pow(specAngle, shininess);
// }


// def compute_point_light_intensity(light_position, point_position, light_intensity):
//     # Calculate the direction vector from point to light
//     light_direction = normalize(light_position - point_position)

//     # Calculate the distance between the point and the light
//     distance = length(light_position - point_position)

//     # Apply the inverse square law to compute intensity
//     intensity = light_intensity / (4.0 * PI * distance * distance)

//     return intensity

// float	get_brightness(t_scene *img, int i, t_hit *hit)
// {
// 	t_vec3	light_direction;
// 	float	distance;
// 	float	result;


// 	light_direction = vec3_sub(img->light_sources[i].pos, hit->pos);
// 	light_direction = vec3_normalize(light_direction);
// 	distance = distance_for_two(img->light_sources[i].pos, hit->pos);
// 	result = (img->light_sources->ratio * 100) / (4.0f * 3.14159265358979323846 * distance * distance);
// 	printf("brightness light n. %i, %f\n", i, result);
// 	return (result);
// }

float	get_specular(t_scene *img, int i, t_hit *hit)
{
	t_vec3	light_direction;
	t_vec3	half_direction;
	// float l_distance;
	float specular;
	float	specular_angle;

	light_direction = vec3_sub(img->light_sources[i].pos, hit->pos);
	light_direction = vec3_normalize(light_direction);
	// l_distance = distance(light_direction);
	// l_distance = l_distance * l_distance;

	// this is blinn phong
	half_direction = vec3_add(light_direction, vec3_negative(img->camera.norm_vector));
	half_direction = vec3_normalize(half_direction);
	specular_angle = fmaxf(dot_vector3(half_direction, img->hit_data.normal), 0.0);
	specular = powf(specular_angle, 40);
	return (specular);
}

float	get_brightness(t_scene *img, int i, t_hit *hit)
{
	float	result;
	t_vec3	light_direction;

	light_direction = vec3_sub(img->light_sources[i].pos, hit->pos);
	light_direction = vec3_normalize(light_direction);
	result = (dot_vector3(img->hit_data.normal, light_direction) \
	* img->light_sources[i].ratio);
	if (result < TINY_VALUE)
		result = 0.0;
	return (result);
}
