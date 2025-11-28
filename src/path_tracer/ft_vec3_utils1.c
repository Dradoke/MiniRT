#include "minirt.h"

/// @brief Take two vectors to produce a third one that
/// @brief is perpendicular to the first two vector
/// @param a Vector 1
/// @param b Vector 2
/// @return Return a vector perpendicular to the two vectors in parameters
t_vec3	ft_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = (a.z * b.x) - (a.x * b.z);
	c.z = (a.x * b.y) - (a.y * b.x);
	return (c);
}

/// @brief This function takes a vector and a scalar,
/// @brief and multiplies each component of the vector by the scalar
/// @param v vector
/// @param s scalar
/// @return vector "v" * scalar "s"
t_vec3	ft_vec3_scale(t_vec3 v, float s)
{
	return ((t_vec3){{v.x * s, v.y * s, v.z * s}});
}

/// @brief Calculates the sum of two vectors
/// @brief by adding their corresponding components
/// @param v1 The first vector
/// @param v2 The second vector
/// @return A new vector resulting from (v1 + v2)
t_vec3	ft_vec3_add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z}});
}

/// @brief Calculates the difference between two vectors
/// @brief by subtracting the second vector from the first
/// @param v1 The vector to subtract from
/// @param v2 The vector to subtract
/// @return A new vector resulting from (v1 - v2)
t_vec3	ft_vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z}});
}
