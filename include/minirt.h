/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngaudoui <ngaudoui@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 19:59:04 by ngaudoui          #+#    #+#             */
/*   Updated: 2025/11/28 18:47:02 by ngaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# define WIDTH 256
# define HEIGHT 256

# define CAM_SENSI 0.01
# define MOVE_SPEED 1.0
# define ROLL_SPEED 0.1

# define RESIZE_DEBOUNCE_TIME 0.15

# define MAX_BLOCK_SIZE 8

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
# include "colors.h"
# include "fterr.h"
# include "struct.h"
# include "prototype.h"
# include "path_tracing.h"

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••
#endif