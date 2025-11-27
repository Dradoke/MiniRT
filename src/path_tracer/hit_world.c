#include "minirt.h"

//extraction de la détection de collision selon le type
static t_bool	hit_object(t_hit_record *tmp_hit, t_mesh *obj, t_ray ray_wld)
{
	t_bool	hit;

	hit = FALSE;
	if (obj->type == SP)
		hit = hit_sphere(tmp_hit, obj->u_data.sphere, ray_wld);
	else if (obj->type == PL)
		hit = hit_plane(tmp_hit, obj->u_data.plane, ray_wld);
	else if (obj->type == CY)
		hit = hit_cylinder(tmp_hit, *obj, ray_wld);
	else if (obj->type == TR)
		hit = hit_triangle(tmp_hit, obj->u_data.triangle, ray_wld);
	return (hit);
}

//extraction de l'assignation de couleur
static void	set_hit_color(t_hit_record *out, t_mesh *obj)
{
	if (obj->type == SP)
		out->color = obj->u_data.sphere.color;
	else if (obj->type == PL)
		out->color = obj->u_data.plane.color;
	else if (obj->type == CY)
		out->color = obj->u_data.cylinder.color;
	else if (obj->type == TR)
		out->color = obj->u_data.triangle.color;
	// else
    //     out->color = (t_rgba){{255, 0, 255, 255}};
}

//extraction de la mise à jour du hit le plus proche
static t_bool	update_closest_hit(t_hit_record *tmp_hit, t_hit_record *out,
	double *best_t, t_mesh *obj)
{
	if (tmp_hit->t < *best_t && tmp_hit->t > EPS)
	{
		*best_t = tmp_hit->t;
		*out = *tmp_hit;
		set_hit_color(out, obj);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	hit_world(t_ray *ray_wld, const t_scene *scene, t_hit_record *out)
{
	double			best_t;
	t_hit_record	tmp_hit;
	t_bool			hit_any;
	int				i;

	best_t = INFINITY;
	hit_any = FALSE;
	tmp_hit.t = INFINITY;
	i = 0;
	while (i < scene->obj_count[MESH])
	{
		if (hit_object(&tmp_hit, &scene->mesh[i], *ray_wld))
		{
			if (update_closest_hit(&tmp_hit, out, &best_t, &scene->mesh[i]))
				hit_any = TRUE;
		}
		i++;
	}
	return (hit_any);
}
