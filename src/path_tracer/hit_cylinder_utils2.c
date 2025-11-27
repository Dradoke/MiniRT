#include "minirt.h"

/// @brief Solves the quadratic equation for the infinite cylinder body
/// @brief and checks for valid intersections
/// @param hit Pointer to hit record
/// @param v Pointer to cylinder variables
/// @param cyl The cylinder object
/// @param ray The ray
void	hit_cylinder_body(t_hit_record *hit, t_cyl_vars *v,
	t_cylinder cyl, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	solve_quadratic(v, &a, &b, &c);
	disc = b * b - 4 * a * c;
	if (disc >= 0)
	{
		v->sqrt_disc = sqrt(disc);
		v->t_vals[0] = (-b - v->sqrt_disc) / (2 * a);
		v->t_vals[1] = (-b + v->sqrt_disc) / (2 * a);
		v->i = 0;
		while (v->i < 2)
		{
			check_body_hit(hit, *v, cyl, ray);
			v->i++;
		}
	}
}

/// @brief Calculates the center point of a cylinder cap
/// @param cyl The cylinder object
/// @param axis The cylinder axis
/// @param sign Direction (+1 for top, -1 for bottom)
/// @return The center of the cap
t_vec3	get_cap_center(t_cylinder cyl, t_vec3 axis, double sign)
{
	t_vec3	cap_center;
	double	h_shift;

	h_shift = sign * (cyl.height / 2.0);
	cap_center.x = cyl.location.x + axis.x * h_shift;
	cap_center.y = cyl.location.y + axis.y * h_shift;
	cap_center.z = cyl.location.z + axis.z * h_shift;
	return (cap_center);
}

/// @brief Sets the normal for a hit on a cylinder cap
/// @param hit Pointer to hit record
/// @param axis The cylinder axis
/// @param sign Direction (+1 for top, -1 for bottom)
void	set_cap_normal(t_hit_record *hit, t_vec3 axis, double sign)
{
	if (sign > 0)
		hit->n = axis;
	else
		hit->n = (t_vec3){{-axis.x, -axis.y, -axis.z}};
}

/// @brief Checks for intersection with a specific cylinder cap
/// @param hit Pointer to hit record
/// @param v Cylinder variables
/// @param cyl The cylinder object
/// @param ray The ray
/// @return TRUE if hit, FALSE otherwise
t_bool	check_cap_hit(t_hit_record *hit, t_cyl_vars v,
	t_cylinder cyl, t_ray ray)
{
	double	t_cap;
	t_vec3	cap_center;
	t_vec3	p_cap;
	t_vec3	v_rad;

	cap_center = get_cap_center(cyl, v.axis, v.signs[v.i]);
	t_cap = dot(ft_vec3_sub(cap_center, ray.origin), v.axis) / v.dv;
	if (t_cap > EPS && t_cap < hit->t)
	{
		p_cap = ft_ray_at(ray, t_cap);
		v_rad = ft_vec3_sub(p_cap, cap_center);
		if (dot(v_rad, v_rad) <= (v.r * v.r))
		{
			hit->t = t_cap;
			hit->p = p_cap;
			set_cap_normal(hit, v.axis, v.signs[v.i]);
			return (TRUE);
		}
	}
	return (FALSE);
}

/// @brief Checks for intersections with both cylinder caps
/// @param hit Pointer to hit record
/// @param v Pointer to cylinder variables
/// @param cyl The cylinder object
/// @param ray The ray
void	hit_cylinder_caps(t_hit_record *hit, t_cyl_vars *v,
	t_cylinder cyl, t_ray ray)
{
	if (fabs(v->dv) <= EPS)
		return ;
	v->signs[0] = 1.0;
	v->signs[1] = -1.0;
	v->i = 0;
	while (v->i < 2)
	{
		check_cap_hit(hit, *v, cyl, ray);
		v->i++;
	}
}
