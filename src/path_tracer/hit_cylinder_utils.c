#include "minirt.h"

/// @brief Calculates the dot product of two vectors
/// @param a First vector
/// @param b Second vector
/// @return The dot product
double	dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/// @brief Initializes variables required for cylinder intersection
/// @param v Pointer to cylinder variables struct
/// @param cyl The cylinder object
/// @param ray The ray
void	init_cylinder_vars(t_cyl_vars *v, t_cylinder cyl, t_ray ray)
{
	v->axis = ft_normalize(cyl.direction);
	v->oc = ft_vec3_sub(ray.origin, cyl.location);
	v->r = cyl.diameter * 0.5;
	v->dd = dot(ray.dir, ray.dir);
	v->dv = dot(ray.dir, v->axis);
	v->d_oc = dot(v->oc, v->oc);
	v->oc_v = dot(v->oc, v->axis);
	v->od = dot(v->oc, ray.dir);
}

/// @brief Sets up the coefficients for the quadratic equation
/// @param v Pointer to cylinder variables
/// @param a Pointer to coefficient a
/// @param b Pointer to coefficient b
/// @param c Pointer to coefficient c
void	solve_quadratic(t_cyl_vars *v, double *a, double *b, double *c)
{
	*a = v->dd - (v->dv * v->dv);
	*b = 2.0 * (v->od - (v->dv * v->oc_v));
	*c = v->d_oc - (v->oc_v * v->oc_v) - (v->r * v->r);
}

/// @brief Calculates the projection of a point onto the cylinder axis
/// @param location Cylinder center
/// @param axis Cylinder axis vector
/// @param m Distance along the axis
/// @return The projected point
t_vec3	get_projection(t_vec3 location, t_vec3 axis, double m)
{
	t_vec3	proj;

	proj.x = location.x + axis.x * m;
	proj.y = location.y + axis.y * m;
	proj.z = location.z + axis.z * m;
	return (proj);
}

/// @brief Checks if a potential intersection t is valid on the cylinder body
/// @param hit Pointer to hit record
/// @param v Cylinder variables
/// @param cyl The cylinder object
/// @param ray The ray
/// @return TRUE if valid hit, FALSE otherwise
t_bool	check_body_hit(t_hit_record *hit, t_cyl_vars v,
	t_cylinder cyl, t_ray ray)
{
	double	t;
	double	m;
	t_vec3	proj;

	t = v.t_vals[v.i];
	if (t > EPS && t < hit->t)
	{
		m = v.oc_v + t * v.dv;
		if (m >= -(cyl.height / 2.0) && m <= (cyl.height / 2.0))
		{
			hit->t = t;
			hit->p = ft_ray_at(ray, t);
			proj = get_projection(cyl.location, v.axis, m);
			hit->n = ft_vec3_sub(hit->p, proj);
			hit->n = ft_normalize(hit->n);
			return (TRUE);
		}
	}
	return (FALSE);
}
