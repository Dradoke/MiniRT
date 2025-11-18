#include "minirt.h"

/// @brief seed initialisation with dev/urandom
/// @param seed 
void	ft_init_random_seed(unsigned int *seed)
{
	int	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		(*seed) = 12345;
		return;
	}
	if (read(fd, seed, sizeof((*seed))) != sizeof((*seed)))
	{
		perror("read");
		(*seed) = 12345;
	}
	close(fd);
}

float	ft_random_float(float min, float max, unsigned int *seed)
{
    (*seed) = ((*seed) * 1103515245 + 12345) & 0x7fffffff;
    float normalized = fabs(sin((double)(*seed)));
    return min + normalized * (max - min);
}

/// @brief Return the direction to a destination from an origin point
/// @param origine origine point
/// @param dest destination point
/// @return Return the direction to a destination from an origin point as a t_vec3
t_vec3	get_dir(t_vec3 origine, t_vec3 dest)
{
	t_vec3	vector = (t_vec3){dest.x - origine.x, dest.y - origine.y,
		dest.z - origine.z};
	float	norme = sqrtf((powf(vector.x, 2)
		+ powf(vector.y, 2) + powf(vector.z, 2)));
	return ((t_vec3){vector.x / norme, vector.y / norme, vector.z / norme});
}

/// @brief Calculate the distance between two t_vec3 (two 3d points)
/// @param p1 first point's position
/// @param p2 second point's position
/// @return Return the distance between two points as a float
float	get_dist(t_vec3 p1, t_vec3 p2)
{
	float	dist;

	dist = sqrtf(powf(p1.x - p2.x, 2)
		+ powf(p1.y - p2.y, 2) + powf(p1.z - p2.z, 2));
	return (dist);
}

float	ft_get_scalaire(t_vec3 vec1, t_vec3 vec2)
{
	float scalaire = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	if (scalaire <= 0.0)
		return (0.0);
	else
		return (scalaire);
}

float	ft_brdf_pdf(float cos_factor)
{
	return (cos_factor / PI);
}

float	ft_direct_contribution(t_vec3 point_loc, t_point_light light)
{
	float	cos_factor;
	float	p1;
	float	p2;

	cos_factor = ft_get_scalaire(point_loc, light.location);
	if (cos_factor < 0.0)
		cos_factor = 0;
	p1 = LIGHT_PDF;
	p2 = ft_brdf_pdf(cos_factor);

}

/// @brief Take two vectors to produce a third one that is perpendicular to the first two vector
/// @param a Vector 1
/// @param b Vector 2
/// @return Return a vector perpendicular to the two vectors in parameters
t_vec3	ft_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = (a.x * b.z) - (a.z * b.x);
	c.z = (a.y * b.x) - (a.x * b.y);
	return (c);
}

/// @brief This function takes a vector and a scalar, and multiplies each component of the vector by the scalar
/// @param v vector
/// @param s scalar
/// @return vector "v" * scalar "s"
t_vec3	ft_vec3_scale(t_vec3 v, float s)
{
	t_vec3	result;

	result.x = v.x * s;
	result.y = v.y * s;
	result.z = v.z * s;
	return (result);
}

t_vec3	ft_vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_rgba	ft_rgba_mult(t_rgba c1, t_rgba c2)
{
	t_rgba	result;

	result.r = c1.r * c2.r;
	result.g = c1.g * c2.g;
	result.b = c1.b * c2.b;
	result.a = c1.a * c2.a;
	return (result);
}

t_rgba	ft_rgba_add(t_rgba c1, t_rgba c2)
{
	t_rgba	result;

	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;
	result.a = c1.a + c2.a;
	return (result);
}
