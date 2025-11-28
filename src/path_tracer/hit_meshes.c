#include "minirt.h"
#include <math.h>

/// @brief Checks for intersection between a ray and a sphere
/// @param hit Pointer to store hit record
/// @param sphere The sphere object
/// @param ray The ray
/// @return TRUE if hit, FALSE otherwise
t_bool	hit_sphere(t_hit_record *hit, t_sphere sphere, t_ray ray)
{
	t_hit_sp_data	data;

	data.oc = ft_vec3_sub(ray.origin, sphere.location);
	data.a = 1.0;
	data.b = 2 * ft_vec3_dot(data.oc, ray.dir);
	data.c = ft_vec3_dot(data.oc, data.oc) - (sphere.diameter * 0.5)
		* (sphere.diameter * 0.5);
	data.disc = (data.b * data.b) - (4 * data.a * data.c);
	if (data.disc < 0)
		return (FALSE);
	data.sqrt_disc = sqrt(data.disc);
	data.t1 = (-data.b - data.sqrt_disc) / (2 * data.a);
	data.t2 = (-data.b + data.sqrt_disc) / (2 * data.a);
	if (data.t1 > EPS)
		hit->t = data.t1;
	else if (data.t2 > EPS)
		hit->t = data.t2;
	else
		return (FALSE);
	hit->p = ft_ray_at(ray, hit->t);
	hit->n = ft_normalize(ft_vec3_sub(hit->p, sphere.location));
	return (TRUE);
}

/// @brief Checks for intersection between a ray and a plane
/// @param hit Pointer to store hit record
/// @param plane The plane object
/// @param ray The ray
/// @return TRUE if hit, FALSE otherwise
t_bool	hit_plane(t_hit_record *hit, t_plane plane, t_ray ray)
{
	double	denom;
	double	t;

	denom = ft_vec3_dot(plane.direction, ray.dir);
	if (fabs(denom) < EPS)
		return (FALSE);
	t = ft_vec3_dot(ft_vec3_sub(plane.location, ray.origin), plane.direction)
		/ denom;
	if (t < EPS)
		return (FALSE);
	hit->t = t;
	hit->p = ft_ray_at(ray, hit->t);
	if (ft_vec3_dot(ray.dir, plane.direction) < 0)
		hit->n = plane.direction;
	else
		hit->n = ft_vec3_neg(plane.direction);
	hit->n = ft_normalize(hit->n);
	return (TRUE);
}

/// @brief Checks for intersection between a ray and a cylinder
/// @param hit Pointer to store hit record
/// @param obj The mesh object containing the cylinder
/// @param ray The ray
/// @return TRUE if hit, FALSE otherwise
t_bool	hit_cylinder(t_hit_record *hit, t_mesh obj, t_ray ray)
{
	t_cylinder	cyl;
	t_cyl_vars	v;

	cyl = obj.u_data.cylinder;
	hit->t = INFINITY;
	init_cylinder_vars(&v, cyl, ray);
	hit_cylinder_body(hit, &v, cyl, ray);
	hit_cylinder_caps(hit, &v, cyl, ray);
	return (hit->t != INFINITY);
}

/// @brief Checks for intersection between a ray and a triangle
/// @brief Uses the Möller–Trumbore intersection algorithm helper
/// @param hit Pointer to store hit record
/// @param triangle The triangle object
/// @param ray The ray
/// @return TRUE if hit, FALSE otherwise
t_bool	hit_triangle(t_hit_record *hit, t_triangle triangle, t_ray ray)
{
	t_tri_vars	v;
	t_vec3		normal;

	if (!moller_trumbore(triangle, ray, &v))
		return (FALSE);
	if (v.t > EPS)
	{
		normal = ft_cross(v.e1, v.e2);
		compute_hit_data(hit, ray, v.t, normal);
		return (TRUE);
	}
	return (FALSE);
}
