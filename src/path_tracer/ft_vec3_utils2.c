#include "minirt.h"

float	ft_get_scalaire(t_vec3 vec1, t_vec3 vec2)
{
	float	scalaire;

	scalaire = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	if (scalaire <= 0.0)
		return (0.0);
	else
		return (scalaire);
}

t_vec3	ft_vec3_neg(t_vec3 v)
{
	return ((t_vec3){{-v.x, -v.y, -v.z}});
}

double	ft_vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	ft_vec3_len2(t_vec3 v)
{
	return (ft_vec3_dot(v, v));
}

double	ft_vec3_len(t_vec3 v)
{
	return (sqrt(ft_vec3_len2(v)));
}
