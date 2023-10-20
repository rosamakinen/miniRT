/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaratzi <mkaratzi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:08:48 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/20 12:32:23 by mkaratzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	free_all_objects(t_object *head, int instruction)
{
	static int	i = 0;

	if (head->next != NULL)
		free_all_objects(head->next, instruction);
	if (i++ != instruction)
		free(head->data);
	free(head);
	head = NULL;
	return ;
}

static int	get_new_sphere(t_object *scene_object, const char *str, int *i)
{
	t_sphere	*new_sphere;

	if (!scene_object)
		return (MALLOC_FAILED);
	scene_object->data = malloc(sizeof(t_sphere));
	if (!scene_object->data)
		return (MALLOC_FAILED);
	scene_object->type = OBJECT_SPHERE;
	new_sphere = (t_sphere *)scene_object->data;
	if (get_vec3(&new_sphere->pos, str, i))
		return (INVALID_INPUT);
	if (get_float(&new_sphere->diameter, str, i) || new_sphere->diameter <= 0)
		return (INVALID_INPUT);
	if (get_color(&new_sphere->color, str, i))
		return (INVALID_INPUT);
	scene_object->next = (t_object *)malloc(sizeof(t_object));
	if (!scene_object->next)
		return (MALLOC_FAILED);
	scene_object->next->next = NULL;
	return (EXIT_SUCCESS);
}

static int	get_new_plane(t_object *scene_object, const char *str, int *i)
{
	t_plane	*new_plane;

	if (!scene_object)
		return (MALLOC_FAILED);
	scene_object->data = malloc(sizeof(t_plane));
	if (!scene_object->data)
		return (MALLOC_FAILED);
	scene_object->type = OBJECT_PLANE;
	new_plane = (t_plane *)scene_object->data;
	if (get_vec3(&new_plane->point, str, i))
		return (INVALID_INPUT);
	if (get_3d_normal_vector(&new_plane->normal_vector, str, i))
		return (INVALID_INPUT);
	if (get_color(&new_plane->color, str, i))
		return (INVALID_INPUT);
	scene_object->next = (t_object *)malloc(sizeof(t_object));
	if (!scene_object->next)
		return (MALLOC_FAILED);
	scene_object->next->next = NULL;
	return (EXIT_SUCCESS);
}

static int	get_new_cylinder(t_object *scene_object, const char *str, int *i)
{
	t_cylinder	*new_cylinder;

	if (!scene_object)
		return (MALLOC_FAILED);
	scene_object->data = malloc(sizeof(t_cylinder));
	if (!scene_object->data)
		return (MALLOC_FAILED);
	scene_object->type = OBJECT_CYLINDER;
	new_cylinder = (t_cylinder *)scene_object->data;
	if (get_vec3(&new_cylinder->pos, str, i))
		return (INVALID_INPUT);
	if (get_3d_normal_vector(&new_cylinder->axis_vector, str, i))
		return (INVALID_INPUT);
	if (get_float(&new_cylinder->diameter, str, i) \
		|| new_cylinder->diameter <= 0)
		return (INVALID_INPUT);
	if (get_float(&new_cylinder->height, str, i) || new_cylinder->height <= 0)
		return (INVALID_INPUT);
	if (get_color(&new_cylinder->color, str, i))
		return (INVALID_INPUT);
	scene_object->next = (t_object *)malloc(sizeof(t_object));
	ft_bzero(scene_object->next, sizeof(t_object));
	if (!scene_object->next)
		return (MALLOC_FAILED);
	return (EXIT_SUCCESS);
}

short	get_new_object(t_object *scene_object, const char *str)
{
	int	i;

	i = 2;
	if (!scene_object)
		return (MALLOC_FAILED);
	while (scene_object->next)
		scene_object = scene_object->next;
	if (str && str[0] == 's' && str[1] == 'p')
		return (get_new_sphere(scene_object, str, &i));
	else if (str && str[0] == 'p' && str[1] == 'l')
		return (get_new_plane(scene_object, str, &i));
	else if (str && str[0] == 'c' && str[1] == 'y')
		return (get_new_cylinder(scene_object, str, &i));
	else
		return (INVALID_INPUT);
	if (str[i] && str[i] != '\n')
		return (INVALID_INPUT);
	return (EXIT_SUCCESS);
}
