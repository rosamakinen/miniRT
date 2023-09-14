/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 09:19:21 by mkaratzi          #+#    #+#             */
/*   Updated: 2023/09/14 06:31:29 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"
#include "../includes/minirt.h"
#include "../libft/includes/libft.h"
#include "../libft/includes/get_next_line.h"

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
		if (ft_strlen_int(new_line) <= 0)
			break ;
		if (ft_strlen_int(new_line) == 1)
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
