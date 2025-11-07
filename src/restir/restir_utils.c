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