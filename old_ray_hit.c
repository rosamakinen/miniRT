/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_ray_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:25:15 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/13 07:59:40 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "includes/minirt.h"

// int sphere_hit(const t_sphere *sphere, const t_vec3 *ray_start, const t_vec3 *direction, t_vec3 *intersection1, t_vec3 *intersection2) {
//     // Calculate values for the quadratic equation because of circles formula
//     float a = direction->x * direction->x + direction->y * direction->y + direction->z * direction->z;
//     float b = 2 * (direction->x * (ray_start->x - sphere->pos.x) + direction->y * (ray_start->y - sphere->pos.y) + direction->z * (ray_start->z - sphere->pos.z));
//     float c = (ray_start->x - sphere->pos.x) * (ray_start->x - sphere->pos.x) +
//                (ray_start->y - sphere->pos.y) * (ray_start->y - sphere->pos.y) +
//                (ray_start->z - sphere->pos.z) * (ray_start->z - sphere->pos.z) -
//                (sphere->diameter / 2) * (sphere->diameter / 2);

//     // check if there are any interesectios. This is refering to the quadratic formula discriminant. If it is less than zero it means there are no intersections. No real solutions.
//     float discriminant = b * b - 4 * a * c;
//     if (discriminant < 0) {
//         return 0; // No intersection
//     }
//     // We all come to the following code if there are function zeros and we calculate the two possible intersect  values (2 because circle is of second degree)
//     float   t1 = (-b + sqrt(discriminant)) / (2 * a);
//     float   t2 = (-b - sqrt(discriminant)) / (2 * a);

//         // Calculate the intersection points
//     intersection1->x = ray_start->x + t1 * direction->x;
//     intersection1->y = ray_start->y + t1 * direction->y;
//     intersection1->z = ray_start->z + t1 * direction->z;

//     intersection2->x = ray_start->x + t2 * direction->x;
//     intersection2->y = ray_start->y + t2 * direction->y;
//     intersection2->z = ray_start->z + t2 * direction->z;

//     return 1; // Ideally here we calculate the distance between ray origin and return onl 1 intersection but I left both for now just in case
// }

// int plane_hit(const t_vec3 *ray_origin, const t_vec3 *direction, const t_plane *plane, t_vec3 *intersectionPoint)
// {
//     t_vec3 planeNormal = plane->normal_vector;

//     float dotProduct = direction->x * planeNormal.x +
//                         direction->y * planeNormal.y +
//                         direction->z * planeNormal.z;

//     if (fabs(dotProduct) < (float)0.005) {
//         return 0; // No intersection
//     }

//     // Calculate the vector from the ray's origin to the center of the circular plane
//     t_vec3 rayToCenter;
//     rayToCenter.x = plane->point.x - ray_origin->x;
//     rayToCenter.y = plane->point.y - ray_origin->y;
//     rayToCenter.z = plane->point.z - ray_origin->z;

//     // Dot product
//     float t = (rayToCenter.x * planeNormal.x +
//                 rayToCenter.y * planeNormal.y +
//                 rayToCenter.z * planeNormal.z) / dotProduct;
//     if (t < 0) {
//         return 0; // No intersection
//     }
//     //otherwise intersect point is at:
//     intersectionPoint->x = ray_origin->x + t *  direction->x;
//     intersectionPoint->y = ray_origin->y + t *  direction->y;
//     intersectionPoint->z = ray_origin->z + t *  direction->z;

//     return 1; // No intersection
// }

// int infinite_cylinder_hit(const t_vec3 *ray_origin, const t_vec3 *ray_direction, const t_cylinder *cylinder, t_vec3 *intersection1, t_vec3 *intersection2)
// {
//     t_vec3 cylinderToRayOrigin;
//     cylinderToRayOrigin.x = ray_origin->x - cylinder->pos.x;
//     cylinderToRayOrigin.y = ray_origin->y - cylinder->pos.y;
//     cylinderToRayOrigin.z = ray_origin->z - cylinder->pos.z;

//     float dotProduct = ray_direction->x * cylinder->axis_vector.x +
//                         ray_direction->y * cylinder->axis_vector.y +
//                         ray_direction->z * cylinder->axis_vector.z;

//     float dotProduct2 = cylinderToRayOrigin.x * cylinder->axis_vector.x +
//                          cylinderToRayOrigin.y * cylinder->axis_vector.y +
//                          cylinderToRayOrigin.z * cylinder->axis_vector.z;

//     // Calculate for the quadratic equation like the circle
//     float a = ray_direction->x * ray_direction->x +
//                ray_direction->y * ray_direction->y +
//                ray_direction->z * ray_direction->z - dotProduct * dotProduct;

//     float b = 2.0 * (ray_direction->x * cylinderToRayOrigin.x +
//                       ray_direction->y * cylinderToRayOrigin.y +
//                       ray_direction->z * cylinderToRayOrigin.z - dotProduct * dotProduct2);

//     float c = cylinderToRayOrigin.x * cylinderToRayOrigin.x +
//                cylinderToRayOrigin.y * cylinderToRayOrigin.y +
//                cylinderToRayOrigin.z * cylinderToRayOrigin.z - dotProduct2 * dotProduct2 - cylinder->diameter / 2 * cylinder->diameter / 2;

//     // Quadratic discriminant
//     double discriminant = b * b - 4.0 * a * c;

//     if (discriminant < 0) {
//         return 0; // No intersection
//     } else {
//         double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
//         double t2 = (-b - sqrt(discriminant)) / (2.0 * a);

//         intersection1->x = ray_origin->x + t1 * ray_direction->x;
//         intersection1->y = ray_origin->y + t1 * ray_direction->y;
//         intersection1->z = ray_origin->z + t1 * ray_direction->z;

//         intersection2->x = ray_origin->x + t2 * ray_direction->x;
//         intersection2->y = ray_origin->y + t2 * ray_direction->y;
//         intersection2->z = ray_origin->z + t2 * ray_direction->z;

//         return 1; // Two intersections
//     }
// }

// int	translate_points(float *x, float *y)
// {
// 	if (*x > 1080 / 2 )
// 		 *x -= 1080 /2;
// 	else
// 		*x = (1080 / 2 - *x) * (-1);
// 	if (*y > 1080 / 2 )
// 		*y = (1080 / 2 - *y) * (-1);
// 	else
// 		 *y -= 1080 /2;
// 	*y *= (-1);
// 	return (0);
// }

// t_hit	get_hit(t_camera *cam, t_object *objects, float x, float y)
// {
// 	float temp_x = x;
// 	float temp_y = y;
// 	t_hit	hit;

// 	hit.hit = 0;
// 	(void)cam;
// 	translate_points(&temp_x, &temp_y);
// 	t_vec3 test_dir= {0, 0, 1};
// 	t_vec3 test_cam = {temp_x, temp_y, 0};
// 	t_vec3 test1;
// 	t_vec3 test2;
// 	t_sphere *my_sphere = (t_sphere *)objects->data;
// 	int answer = sphere_hit(my_sphere, &test_cam, &test_dir, &test1, &test2);
// 	if (answer)
// 	{
// 		t_vec3 hit1 = vec3_sub(cam->pos, test1);
// 		t_vec3 hit2 = vec3_sub(cam->pos, test2);
// 		float dist1 = distance(hit1);
// 		float dist2 = distance(hit2);
// 		if (dist1 < dist2)
// 			hit.pos = test1;
// 		else
// 			hit.pos = test2;
// 		hit.hit = 1;
// 	}
// 	return (hit);
// }

