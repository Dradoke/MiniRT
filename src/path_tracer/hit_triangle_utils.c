#include "minirt.h"

/// @brief Checks if the determinant is close to zero (ray parallel to triangle)
/// @param det The determinant value
/// @return TRUE if determinant is valid (non-zero), FALSE otherwise
t_bool	check_determinant(double det)
{
	if (fabs(det) < EPS)
		return (FALSE);
	return (TRUE);
}

/// @brief Checks if the barycentric coordinate U is within valid range [0, 1]
/// @param u The U coordinate
/// @return TRUE if valid, FALSE otherwise
t_bool	check_barycentric_u(double u)
{
	if (u < 0.0 || u > 1.0)
		return (FALSE);
	return (TRUE);
}

/// @brief Checks if the barycentric coordinate V is within valid range
/// @brief Must be >= 0 and (U + V) <= 1
/// @param u The U coordinate
/// @param v The V coordinate
/// @return TRUE if valid, FALSE otherwise
t_bool	check_barycentric_v(double u, double v)
{
	if (v < 0.0 || (u + v) > 1.0)
		return (FALSE);
	return (TRUE);
}

/// @brief Fills the hit record with intersection data (t, point, normal)
/// @brief Also ensures the normal points towards the ray origin (face culling)
/// @param hit Pointer to the hit record to fill
/// @param ray The ray that hit the triangle
/// @param t The distance to the intersection
/// @param normal The calculated geometric normal of the triangle
void	compute_hit_data(t_hit_record *hit, t_ray ray,
	double t, t_vec3 normal)
{
	hit->t = t;
	hit->p = ft_ray_at(ray, hit->t);
	hit->n = ft_normalize(normal);
	if (ft_vec3_dot(ray.dir, hit->n) > 0)
		hit->n = ft_vec3_neg(hit->n);
}

/// @brief Implements the Möller–Trumbore intersection algorithm
/// @brief Calculates barycentric coordinates and distance t
/// @param tri The triangle object
/// @param ray The ray to test
/// @param v Pointer to triangle variables struct to store results
/// @return TRUE if the ray intersects
/// the triangle plane within the triangle bounds
t_bool	moller_trumbore(t_triangle tri,
	t_ray ray, t_tri_vars *v)
{
	v->e1 = ft_vec3_sub(tri.vertex2, tri.vertex1);
	v->e2 = ft_vec3_sub(tri.vertex3, tri.vertex1);
	v->p_vec = ft_cross(ray.dir, v->e2);
	v->det = ft_vec3_dot(v->e1, v->p_vec);
	if (!check_determinant(v->det))
		return (FALSE);
	v->inv_det = 1.0 / v->det;
	v->t_vec = ft_vec3_sub(ray.origin, tri.vertex1);
	v->u = ft_vec3_dot(v->t_vec, v->p_vec) * v->inv_det;
	if (!check_barycentric_u(v->u))
		return (FALSE);
	v->q_vec = ft_cross(v->t_vec, v->e1);
	v->v = ft_vec3_dot(ray.dir, v->q_vec) * v->inv_det;
	if (!check_barycentric_v(v->u, v->v))
		return (FALSE);
	v->t = ft_vec3_dot(v->e2, v->q_vec) * v->inv_det;
	return (TRUE);
}
