/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:19:21 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/10/18 17:23:45 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

//ATTENTION: This parser relies that the file has been check to be of correct
// format. Ideally there is a function that checks arg count and arg type in
// main, before this function gets called

int	skip_chars(const char *skippable, int index, const char *str)
{
	int	i;
	int	j;
	int	found;

	i = index;
	while (str[i])
	{
		j = 0;
		found = 0;
		while (skippable[j])
		{
			if (str[i] == skippable[j])
				found = 1;
			j++;
		}
		if (!found)
			return (i);
		i++;
	}
	return (i);
}

static int	constractor_loop(t_scene *scene, const char *str)
{
	int	catcher;

	catcher = 0;
	if (ft_strlen_int(str) == 1)
	{
		catcher = !(str[0] == '\n');
		return (catcher);
	}
	catcher = get_object_identifier(str);
	if (catcher == LIGHT_SOURCE)
		catcher = get_light_source(scene, str);
	else if (catcher == AMBIENT_LIGHT)
		catcher = get_ambient_light(scene, str);
	else if (catcher == CAMERA)
		catcher = get_camera(scene, str);
	else if (catcher == VALID_OBJECT)
		catcher = get_new_object(scene->objects, str);
	return (catcher);
}

static int	check_required(t_scene *scene)
{
	if (!scene->check_once.ambient_light || !scene->check_once.light_source
		|| !scene->check_once.camera)
	{
		scene->error_catcher = MISSING_KEY_ELEMENTS;
		return (MISSING_KEY_ELEMENTS);
	}
	return (EXIT_SUCCESS);
}

t_scene	scene_constractor(const char *file)
{
	static t_scene	main_scene = {0};
	int				fd;
	static char		*new_line = NULL;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		main_scene.error_catcher = OPEN_FAIL;
	main_scene.objects = (t_object *)malloc(sizeof(t_object));
	if (!main_scene.objects)
		main_scene.error_catcher = MALLOC_FAILED;
	main_scene.objects->next = NULL;
	while (!main_scene.error_catcher)
	{
		new_line = get_next_line(fd);
		if (ft_strlen_int(new_line) <= 0 && !close(fd))
			break ;
		main_scene.error_catcher = constractor_loop(&main_scene, new_line);
		free(new_line);
	}
	if (main_scene.error_catcher || check_required(&main_scene))
	{
		free_all_objects(main_scene.objects);
		main_scene.objects = NULL;
	}
	return (main_scene);
}
