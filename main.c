/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:29:32 by rmakinen          #+#    #+#             */
/*   Updated: 2023/10/04 07:47:29 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minirt.h"

// int	main(int argc, char **argv)
// {
// 	t_window	img;
// 	t_scene		scene;

// 	if (argc == 1)
// 	{
// 		ft_printf("%s\n", argv[0]);
// 		ft_printf("this is the start\n");
// 		handle_window(&img);
// 		draw_img(&img);
// 		mlx_loop(img.mlx);
// 	}
// 	return(0);
// }

int	main(void)
{
	t_scene		main_scene;
	t_object	*temp;
	t_sphere	*temp_sphere;
	t_plane		*temp_plane;
	t_cylinder	*temp_cylinder;

	main_scene = scene_constractor("file.test");
	printf("we got back from scene_const\n");
	if (main_scene.error_catcher)
	{
		printf("we got back from\n");
		return (return_parser_error(main_scene.error_catcher));
	}
	printf("We got light: %f, %f, %f and ratio %f\n", main_scene.light_sources->pos.x, main_scene.light_sources->pos.y, main_scene.light_sources->pos.z, main_scene.light_sources->ratio);
	printf("We got ambient light ratio: %f,and color %x\n", main_scene.ambient_light.ratio, main_scene.ambient_light.color);
	printf("We got camera pos: %f, %f, %f,and degrees %d\n", main_scene.camera.pos.x, main_scene.camera.pos.y, main_scene.camera.pos.z, main_scene.camera.fov);
	temp = main_scene.objects;
	while (temp->next != NULL)
	{
		if (temp->type == OBJECT_SPHERE)
		{
			temp_sphere = (t_sphere *)temp->data;
			printf("We got sphere with %f, %f, %f pos, %f diameter and %x color\n", temp_sphere->pos.x, temp_sphere->pos.y, temp_sphere->pos.z, temp_sphere->diameter, temp_sphere->color);
		}
		else if (temp->type == OBJECT_CYLINDER)
		{
			temp_cylinder = (t_cylinder *)temp->data;
			printf("We got cylinder with %f, %f, %f posand  %f, %f,%f rot axis, and %f diameter, and %f height and %x color\n", temp_cylinder->pos.x, temp_cylinder->pos.y, temp_cylinder->pos.z,
				temp_cylinder->pos.x, temp_cylinder->pos.y, temp_cylinder->pos.z, temp_cylinder->diameter, temp_cylinder->height, temp_cylinder->color);
		}
		else if (temp->type == OBJECT_PLANE)
		{
			temp_plane = (t_plane *)temp->data;
			printf("we got a plane with %f,%f,%f point and %f, %f, %f normal and %x color\n", temp_plane->point.x, temp_plane->point.y, temp_plane->point.z,
				temp_plane->normal_vector.x, temp_plane->normal_vector.y, temp_plane->normal_vector.z, temp_plane->color);
		}
		temp = temp->next;
	}
	handle_window(&main_scene);
	draw_img(&main_scene);
	mlx_loop(main_scene.mlx);
	return (0);
}
