#ifndef STRUCT_H
# define STRUCT_H
# include "minirt.h"

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• ENUM

enum e_count_type
{
	LIGHT,
	MESH,
};

typedef enum e_type
{
	NONE,
	A,
	C,
	L,
	SP,
	PL,
	CY,
	TR,
}	t_type;

typedef enum e_flags
{
	RMB,
	FISHEYE,
}	t_flags;

typedef enum e_axis
{
	X,
	Y,
	Z,
}	t_axis;

//•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• COLOR

typedef union u_rgba
{
	struct
	{
		t_ui8	r;
		t_ui8	g;
		t_ui8	b;
		t_ui8	a;
	};
	t_ui8	rgba[4];
	t_ui32	color;
}	t_rgba;

//•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• MLX42

typedef union u_vec3
{
	struct
	{
		t_f32	x;
		t_f32	y;
		t_f32	z;
	};
	t_f32	v[3];
}	t_vec3;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_mat4
{
	t_f32	m[4][4];
}	t_mat4;

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• CAMERA

typedef struct s_cam
{
	t_vec3	location;
	t_vec3	rotation;
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	t_ui8	aov;
	t_f32	aspect_ratio;
}	t_cam;

//•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• LIGHT

typedef struct s_ambient_light
{
	t_f32	brightness;
	t_rgba	color;
}	t_ambient_light;

typedef struct s_point_light
{
	t_vec3	location;
	t_f32	brightness;
	t_rgba	color;
}	t_point_light;

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• MESH

typedef struct s_sphere
{
	t_vec3	location;
	t_f32	diameter;
	t_rgba	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	location;
	t_vec3	rotation;
	t_rgba	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3			location;
	t_vec3			rotation;
	t_f32			diameter;
	t_f32			height;
	t_rgba			color;
}	t_cylinder;

typedef struct s_triangle
{
	t_vec3			vertex1;
	t_vec3			vertex2;
	t_vec3			vertex3;
	t_rgba			color;
}	t_triangle;

typedef struct s_mesh
{
	t_type	type;
	t_mat4	transform;
	t_mat4	inv_transform;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_triangle	triangle;
	}	u_data;
}	t_mesh;

//•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• LIST NODE

typedef struct s_node
{
	t_type	type;
	union
	{
		t_ambient_light		ambient_light;
		t_cam				cam;
		t_point_light		point_light;
		t_sphere			sphere;
		t_plane				plane;
		t_cylinder			cylinder;
		t_triangle			triangle;
	}	u_data;
}	t_node;

//•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••• GLOBAL STRUCT

typedef struct s_scene
{
	t_ambient_light	ambient_light;
	t_cam			cam;
	t_point_light	*light;
	t_mesh			*mesh;
	int				obj_count[2];
	unsigned int	seed;
}	t_scene;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
	t_list		*parse_list;
	t_ui8		flags[2];
	t_f64		last_pos[2];
}	t_data;

//••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

#endif
