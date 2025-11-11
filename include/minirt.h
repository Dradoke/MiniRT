#ifndef MINIRT_H
# define MINIRT_H
//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# define WIDTH 256
# define HEIGHT 256

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# include <unistd.h>		// read, write, close
# include <fcntl.h>			// open
# include <stdlib.h>		// malloc, free, exit
# include <stdio.h>			// printf, perror
# include <string.h>		// strerror
# include <errno.h>			// errno (perror/strerror)
# include <math.h>			// math functions

# include "MLX42/MLX42.h"	// MinilibX
# include "libft.h"			// LibFT

# include "prototype.h"
# include "struct.h"
# include "fterr.h"

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
#endif