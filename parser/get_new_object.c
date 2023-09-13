#include "../includes/parser.h"

static int get_new_sphere(t_object *scene_object, const char *str)
{
    t_sphere    *new_sphere;
    int         i;

    i = 2;
    if(!scene_object)
        return (MALLOC_FAILED);
    scene_object->data = malloc(sizeof(t_sphere));
    if (!scene_object->data)
        return (MALLOC_FAILED);
    scene_object->type = OBJECT_SPHERE;
    new_sphere = (t_sphere *)scene_object->data;
    if (get_3d_coordindate(&new_sphere->pos, str, &i))
        return (INVALID_INPUT);
    if (get_float(&new_sphere->diameter, str, &i))
         return (INVALID_INPUT);
    if (get_color(&new_sphere->color, str, &i))
        return (INVALID_INPUT);
    scene_object->next = (t_object *)malloc(sizeof(t_object));
    if (!scene_object->next)
        return (MALLOC_FAILED);
    return (EXIT_SUCCESS);
}

static int get_new_plane(t_object *scene_object, const char *str)
{
    t_plane     *new_plane;
    int         i;

    i = 2;
    if(!scene_object)
        return (MALLOC_FAILED);
    scene_object->data = malloc(sizeof(t_plane));
    if (!scene_object->data)
        return (MALLOC_FAILED);
    scene_object->type = OBJECT_PLANE;
    new_plane = (t_plane *)scene_object->data;
    if (get_3d_coordindate(&new_plane->point, str, &i))
        return (INVALID_INPUT);
    if (get_3d_normal_vector(&new_plane->normal_vector, str, &i))
         return (INVALID_INPUT);
    if (get_color(&new_plane->color, str, &i))
        return (INVALID_INPUT);
    scene_object->next = (t_object *)malloc(sizeof(t_object));
    if (!scene_object->next)
        return (MALLOC_FAILED);
    return (EXIT_SUCCESS);
}

static int  get_new_cylinder(t_object *scene_object, const char *str)
{
    t_cylinder  *new_cylinder;
    int         i;

    i = 2;
    if(!scene_object)
        return (MALLOC_FAILED);
    scene_object->data = malloc(sizeof(t_cylinder));
    if (!scene_object->data)
        return (MALLOC_FAILED);
    scene_object->type = OBJECT_CYLINDER;
    new_cylinder = (t_cylinder *)scene_object->data;
    if (get_3d_coordindate(&new_cylinder->pos, str, &i))
        return (INVALID_INPUT);
    if (get_3d_normal_vector(&new_cylinder->axis_vector, str, &i))
        return (INVALID_INPUT);
    if (get_float(&new_cylinder->diameter, str, &i))
        return (INVALID_INPUT);
    if (get_float(&new_cylinder->height, str, &i))
        return (INVALID_INPUT);
    if (get_color(&new_cylinder->color, str, &i))
        return (INVALID_INPUT);
    scene_object->next = (t_object *)malloc(sizeof(t_object));
    if (!scene_object->next)
        return (MALLOC_FAILED);
    return (EXIT_SUCCESS);
}

short	get_new_object(t_object *scene_object, const char *str)
{
    if (str && str[0] == 's' && str[1] == 'p')
        return(get_new_sphere(scene_object, str));
    else if (str && str[0] == 'p' && str[1] == 'l')
        return(get_new_plane(scene_object, str));
    else if (str && str[0] == 'c' && str[1] == 'y')
        return(get_new_cylinder(scene_object, str));
	else
		return (INVALID_INPUT);
    //ATTENTION: TODO: make sure these get freed at some point!
	return (EXIT_SUCCESS);
}
