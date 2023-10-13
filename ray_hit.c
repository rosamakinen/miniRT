/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:25:15 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/13 13:47:02 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

t_vec3 vec3_scalar_multiplication(t_vec3 v, float s)
{
    return (t_vec3){v.x * s, v.y * s, v.z * s};
}

t_vec3 vec3_scalar_division(t_vec3 v, float s)
{
    return (t_vec3){v.x * s, v.y * s, v.z * s};
}

//Honorable mention. The following function would not have been possible without the contributions
//of Sheree and Dorian!
t_vec3 find_ray_dir(t_camera *camera, float x, float y)
{
    float   offset[3];
    float   mini_ratio;
    t_vec3  ray_dir;
    t_vec3  temp_right;
    t_vec3  temp_up;

    mini_ratio = atan2f(y, x);
    offset[0] = distance((t_vec3){x, y, 0}) * 0.5f;
    offset[1] = offset[0] * cosf(mini_ratio);
    offset[2] = offset[0] * sinf(mini_ratio);
    temp_right = vec3_scalar_multiplication(camera->right_dir, offset[1]);
    temp_up = vec3_scalar_multiplication(camera->up_dir, offset[2]);
    ray_dir = vec3_add(temp_right, temp_up);
    ray_dir = vec3_add(camera->forward_dir, ray_dir);
    ray_dir = vec3_normalize(ray_dir);
    return (ray_dir);
}

void    translate_t_vec3s(float *x, float *y, float aspect_ratio, float fov)
{
   *x = (1.0f - (2.0f * (*x + 0.5f) / WINDOW_WIDTH)) * \
		aspect_ratio * tanf(fov * (M_PI / 360));
    *y = (1.0f - (2.0f * (*y + 0.5f) / WINDOW_HEIGHT)) * \
		tanf(fov * (M_PI / 360));
}

int sphere_hit(const t_sphere *sphere, const t_vec3 ray_start, const t_vec3 direction, t_vec3 *intersection1, t_vec3 *intersection2)
{
    float   a;
    float   b;
    float   c;
    float   discriminant;
    t_vec3  dist;

    dist = vec3_sub(sphere->pos, ray_start);
    a = dot_vector3(direction, direction);
    b = 2.0 * dot_vector3(direction, dist);
    c = dot_vector3(dist, dist) - ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
    discriminant = b * b - 4 * a * c;
    if (discriminant > 0)
    {
        c = (-b + sqrtf(discriminant)) / (2.0 * a);
        if (c < 0)
            return (0);
        *intersection1 = (t_vec3){ray_start.x + c * direction.x * -1, ray_start.y
                + c * direction.y * -1, ray_start.z + c * direction.z * -1};
        c = (-b - sqrtf(discriminant)) / (2.0 * a);
        *intersection2 = (t_vec3){ray_start.x + c * direction.x * -1, ray_start.y
                + c * direction.y * -1, ray_start.z + c * direction.z * -1};
        return 1;
    }
    return 0;
}

t_hit   find_sphere_hit(t_sphere *sphere, t_vec3 ray_direction, t_camera *camera)
{
    t_hit	hit;
    t_vec3  point1;
    t_vec3  point2;

    ft_bzero(&hit, sizeof(t_hit));
    if (sphere_hit(sphere, camera->pos, ray_direction, &point1, &point2))
	{
		if (distance(vec3_sub(camera->pos, point1)) < distance(vec3_sub(camera->pos, point2)))
			hit.pos = point1;
		else
			hit.pos = point2;
		hit.hit = 1;
	}
    return (hit);
}

int plane_hit(t_vec3 origin, t_vec3 direction, t_plane plane, t_vec3 *point)
{
    float   angle;
    float   dist;
    t_vec3  plane_to_cam;

    direction.z = -1 * direction.z;
    angle = dot_vector3(plane.normal_vector, direction);
    if(fabsf(angle) < 0.0001)
         return (0);
    plane_to_cam = vec3_sub(plane.point, origin);
    dist = dot_vector3(plane_to_cam, plane.normal_vector) / angle;
    if (dist < 0.0001)
         return (0);
    *point = (t_vec3){origin.x + dist * direction.x, origin.y \
        + dist * direction.y, origin.z + dist * direction.z};
    return (1);
}

t_hit   find_plane_hit(t_plane *plane, t_vec3 ray_direction, t_camera *camera)
{
    t_hit	hit;
    t_vec3  point1;

    ft_bzero(&hit, sizeof(t_hit));

    if (plane_hit(camera->pos, ray_direction, *plane, &point1))
	{
		hit.pos = point1;
		hit.hit = 1;
	}
    return (hit);
}

t_hit	get_hit(t_camera *cam, t_object *objects, float x, float y)
{
	t_hit	hit = {0};
    float   aspect_ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
    float   fake_x = x;
    float   fake_y = y;
    translate_t_vec3s(&fake_x, &fake_y, aspect_ratio, cam->fov);
	t_vec3 test_dir= find_ray_dir(cam, fake_x, fake_y);
   // static int p = 0;
    // if (p++ < 2)
    // {
    //     printf("forward %f, %f, %f\n", cam->forward_dir.x, cam->forward_dir.y, cam->forward_dir.z);
    //     printf("up %f, %f, %f\n", cam->up_dir.x, cam->up_dir.y, cam->up_dir.z);
    //     printf("right %f, %f, %f\n", cam->right_dir.x, cam->right_dir.y, cam->right_dir.z);
    // }
    if (objects->type == OBJECT_SPHERE)
    {
        hit = find_sphere_hit((t_sphere *)objects->data, test_dir, cam);
       // printf("do we detect sphere %i?\n", hit.hit);
    }
    if (objects->type == OBJECT_PLANE)
         hit = find_plane_hit((t_plane *)objects->data, test_dir, cam);
	return (hit);
}
