#include "minirt.h"

/// @brief seed initialisation with dev/urandom
/// @param seed 
void	ft_init_random_seed(unsigned int *seed)
{
	int	fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		(*seed) = 12345;
		return ;
	}
	if (read(fd, seed, sizeof((*seed))) != sizeof((*seed)))
	{
		perror("read");
		(*seed) = 12345;
	}
	close(fd);
}

/// @brief Generates a random float between min and max using a seed
/// @param min Minimum value
/// @param max Maximum value
/// @param seed Pointer to the random seed
/// @return Random float value
float	ft_random_float(float min, float max, unsigned int *seed)
{
	float	normalized;

	(*seed) = ((*seed) * 1103515245 + 12345) & 0x7fffffff;
	normalized = fabs(sin((double)(*seed)));
	return (min + normalized * (max - min));
}

/// @brief normalize() is an operation that takes a vector and changes its
///	@brief length to exactly 1, without changing its direction.
/// @param vector t_vec3 to normalize
/// @return Return a normalized t_vec3
t_vec3	ft_normalize(t_vec3 vector)
{
	float	norme;

	norme = sqrtf(powf(vector.x, 2) + powf(vector.y, 2) + powf(vector.z, 2));
	return ((t_vec3){{vector.x / norme, vector.y / norme, vector.z / norme}});
}

/// @brief Return the direction to a destination from an origin point
/// @param origine origine point
/// @param dest destination point
/// @return Return the direction to a destination
/// @return from an origin point as a t_vec3
t_vec3	get_dir(t_vec3 origine, t_vec3 dest)
{
	t_vec3	vector;
	float	norme;

	vector = (t_vec3){{dest.x - origine.x, dest.y - origine.y,
		dest.z - origine.z}};
	norme = sqrtf((powf(vector.x, 2)
				+ powf(vector.y, 2) + powf(vector.z, 2)));
	return ((t_vec3){{vector.x / norme, vector.y / norme, vector.z / norme}});
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
