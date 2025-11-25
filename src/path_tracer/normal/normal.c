#include "minirt.h"



t_vec3	ft_sphere_normal(t_vec3 pos, t_vec3 sphere)
{
	t_vec3	vector;
	float	norme;

	vector = (t_vec3){pos.x - sphere.x, pos.y - sphere.y, pos.z - sphere.z};
	norme = sqrtf(powf(vector.x, 2) + powf(vector.y, 2) + powf(vector.z, 2));
	return ((t_vec3){vector.x / norme, vector.y / norme, vector.z / norme});
}

t_vec3	ft_plane_normal(t_vec3 last_vec, t_vec3 plane_vec)
{
	if (get_scalaire(last_vec, plane_vec) > 0)
		return ((t_vec3){!plane_vec.x, !plane_vec.y, !plane_vec.z});
	else
		return (plane_vec);
}