#include "minirt.h"

/// @brief Creates a new 3D vector
/// @param x 
/// @param y 
/// @param z 
/// @return 
t_vec3	vec3_new(t_f32 x, t_f32 y, t_f32 z)
{
	return ((t_vec3){{x, y, z}});
}

/// @brief Adds two 3D vectors (v1 + v2)
/// @param v1 
/// @param v2 
/// @return 
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z}});
}

/// @brief Subtracts two 3D vectors (v1 - v2)
/// @param v1 
/// @param v2 
/// @return 
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z}});
}

/// @brief Sets a 3D vector to scale by a dot product
/// @param v 
/// @param s 
/// @return 
t_vec3	vec3_scale(t_vec3 v, t_f32 s)
{
	return ((t_vec3){{v.x * s, v.y * s, v.z * s}});
}

/// @brief Calculates dot product of two 3D vectors
/// @param v1 
/// @param v2 
/// @return 
t_f32	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
