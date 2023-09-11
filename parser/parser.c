/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:19:21 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/09/09 14:53:05 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//ATTENTION: This parser relies that the file has been check to be of correct
// format. Ideally there is a function that checks arg count and arg type in
// main, before this function gets called

t_scene	scene_constractor(const char *file)
{
	static t_scene	main_scene = {0};
	int				fd;
	static char		*new_line = NULL;
	t_object		*next_object;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		main_scene.error_catcher = OPEN_FAIL;
	main_scene.objects = (t_object *)malloc(sizeof(t_object));
	next_object = main_scene.objects;
	if(!next_object)
		main_scene.error_catcher = MALLOC_FAILED;
	while (!main_scene.error_catcher)
	{
		new_line = get_next_line(fd);
		if (ft_strlen(new_line) <= 0)
			break ;
		if (ft_strlen(new_line) == 1)
			continue ;
		main_scene.error_catcher = get_object_identifier(new_line);
		if (main_scene.error_catcher == LIGHT_SOURCE)
			main_scene.error_catcher = get_light_source(&main_scene, new_line);
		else if (main_scene.error_catcher == AMBIENT_LIGHT)
			main_scene.error_catcher = get_ambient_light(&main_scene, new_line);
		else if (main_scene.error_catcher == CAMERA)
			main_scene.error_catcher = get_camera(&main_scene, new_line);
		else if (main_scene.error_catcher == VALID_OBJECT)
		{
			main_scene.error_catcher = get_new_object(next_object, new_line);
			next_object = next_object->next;
		}
	}
	next_object->next = NULL;
	return (main_scene);
}

int	main(void)
{
	t_scene	main_scene;
	t_object	*temp;
	t_sphere	*temp_sphere;
	t_plane		*temp_plane;
	t_cylinder	*temp_cylinder;

	main_scene = scene_constractor("file.test");
	if (main_scene.error_catcher)
		return (return_parser_error(main_scene.error_catcher));
	printf("We got light: %f, %f, %f and ratio %f\n", main_scene.light_sources.pos.x, main_scene.light_sources.pos.y, main_scene.light_sources.pos.z, main_scene.light_sources.ratio);
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
	return (0);
}