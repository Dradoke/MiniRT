#ifndef MINIRT_H
# define MINIRT_H
//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# define WIDTH 1000
# define HEIGHT 1000

# define CAM_SENSI 0.01
# define MOVE_SPEED 1.0
# define ROLL_SPEED 1.0

# define RESIZE_DEBOUNCE_TIME 0.15

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# include <unistd.h>		// read, write, close
# include <fcntl.h>			// open
# include <stdlib.h>		// malloc, free, exit
# include <stdio.h>			// printf, perror
# include <string.h>		// strerror
# include <errno.h>			// errno (perror/strerror)
# include <math.h>			// math functions

# include "MLX42.h"	// MinilibX
# include "libft.h"			// LibFT

# include "colors.h"
# include "fterr.h"
# include "struct.h"
# include "prototype.h"
# include "restir.h"

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
#endif