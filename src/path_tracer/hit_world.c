/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_world.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by ngaudoui          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief Dispatches the intersection test to the specific object type
/// @param tmp_hit Pointer to store temporary hit record
/// @param obj The mesh object to test
/// @param ray_wld The ray in world space
/// @return TRUE if hit, FALSE otherwise
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

/// @brief Extracts the color from the specific object
/// type and assigns it to the hit record
/// @param out Pointer to the hit record
/// @param obj The mesh object
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
}

/// @brief Updates the closest hit record if the new hit is closer
/// @param tmp_hit The temporary hit record to check
/// @param out The final hit record to update
/// @param best_t Pointer to the closest distance found so far
/// @param obj The object that was hit
/// @return TRUE if the hit was updated, FALSE otherwise
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

/// @brief Iterates through all objects in the
/// scene to find the closest intersection
/// @param ray_wld The ray in world space
/// @param scene The scene containing objects
/// @param out Pointer to store the hit record of the closest object
/// @return TRUE if an object was hit, FALSE otherwise
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
