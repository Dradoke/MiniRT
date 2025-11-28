#include "minirt.h"

/// @brief Calculates the point on a ray at distance t
/// @param r The ray
/// @param t The distance parameter
/// @return The point coordinates
t_vec3	ft_ray_at(t_ray r, double t)
{
	return (ft_vec3_add(r.origin, ft_vec3_scale(r.dir, t)));
}

/// @brief Multiplies a 4x4 matrix by a 3D vector
/// @param m The matrix
/// @param v The vector
/// @param w The w component (1 for points, 0 for vectors)
/// @return The transformed vector
t_vec3	mat4_mul_vec3(t_mat4 m, t_vec3 v, double w)
{
	t_vec3	out;

	out.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * w;
	out.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * w;
	out.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * w;
	return (out);
}
