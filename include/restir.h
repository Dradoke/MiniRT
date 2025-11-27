#ifndef RESTIR_H
# define RESTIR_H
# include "minirt.h"

/// @file restir.h
/// @brief Specific structures for restir

/// @def Maximum rebounds number
# define MAX_DEPTH 5

# define RANDF_MIN 0.0
# define RANDF_MAX 1.0

# define PI 3.14159265f
# define EPS 1e-5

typedef struct s_rgb
{
	float	r;
	float	g;
	float	b;
}				t_rgb;

/// @brief Ambiant light element, extended as A in .rt file
typedef struct s_ambiant_light
{
	float			brightness;
	t_rgba			color;
}				t_ambiant_light;

/// @brief This is the structure for (the “champion” sample).
typedef struct s_sample
{
	/** @name Base informations */
	/// @{ 
	t_rgb	li;		/// Light energy (color)
	t_vec3	dir;	/// Light source direction
	float	dist;	/// Light source distance
	/// @}
	/** @name weight re-calculation data*/
	/// @{ 
	t_vec3	hitpoint;	/// Origine ray point (on surface)
	t_vec3	normal;		/// Surface normal on impact point
	float	pdf;		/// PDF (Probability Density Function) of this sample
	/// @}
}				t_sample;

/// @brief This is the principal structure for the Pool.
typedef struct s_pool
{
	t_sample	sample; /// champion sample chosen
	float		sum_weight;		/// Sum of the weights (sum_weights)
	int			nb_samples;		/// number of sample seen
}				t_pool;

/// @brief Hold all the material informations
/// @param albedo diffuse color RGB
/// @param spec_reflexion specular reflexion
/// @param roughness rugosity of the material, affect the reflexion
typedef struct s_material
{
	t_rgb	albedo;
	t_vec3	spec_reflexion;
	float	roughness;
	/*Rajouter un pointeur vers la fonction BRDF*/
}				t_material;

/// @brief Regroup every needed informations for the color calculation
/// @brief at p point
/// @param p Postion
/// @param n Normal
/// @param material surface proprerties reference
/// @param omega_o direction to where the rayon come from
/// @param color impact point color based on the object's color
///	@param t distance from the impact point in relation to the origin of the ray
typedef struct s_hit_record
{
	t_vec3		p;
	t_vec3		n;
	t_bool		has_touched;
	t_vec3		omega_o;
	t_rgba		color;
	double		t;
}				t_hit_record;

typedef struct s_path_tracing
{
	t_hit_record	hit;
	t_vec3			d_new;
	t_vec3			d_local;
	t_rgb			direct_light;
	t_rgb			indirect_light;
	t_ray			next_ray;
	t_rgb			entrant_light;
	t_rgb			out_light;

}				t_path_tracing;

typedef struct s_hit_sp_data
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	sqrt_disc;
	double	t1;
	double	t2;
}	t_hit_sp_data;

typedef struct s_cyl_vars
{
	t_vec3	axis;
	t_vec3	oc;
	double	r;
	double	dd;
	double	dv;
	double	d_oc;
	double	oc_v;
	double	od;
	double	sqrt_disc;
	double	t_vals[2];
	double	signs[2];
	int		i;
}	t_cyl_vars;

typedef struct s_tri_vars
{
	t_vec3	e1;
	t_vec3	e2;
	t_vec3	p_vec;
	t_vec3	t_vec;
	t_vec3	q_vec;
	double	det;
	double	inv_det;
	double	t;
	double	u;
	double	v;
}	t_tri_vars;

//••••••••••••••••••••••••••••••••••••••••••••••••••••path_tracer/simple_tracer
// st_utils.c
t_vec3		get_local_dir(unsigned int *seed);
t_vec3		get_world_dir(t_vec3 u, t_vec3 v, t_vec3 w, t_vec3 d_local);
t_vec3		get_rand_dir(t_hit_record hit, t_vec3 d_local);
t_ray		ft_create_reb_ray(t_vec3 d_new, t_hit_record hit);
t_rgb		get_albedo(t_rgba color);
// st_utils2.c
t_rgb		get_light_color(t_point_light light);
int			is_light_visible(t_hit_record hit, t_scene scene, int i);
t_rgb		calc_light_contrib(t_hit_record hit, t_scene scene, int i,
				t_rgb albedo);
t_rgb		add_ambient(t_rgb acc, t_scene scene, t_rgb albedo);
t_rgba		rgb_to_rgba_clamped(t_rgb color);
// st_utils3.c
t_rgba		ft_calc_direct_light(t_hit_record hit, t_scene scene);
// st.c
t_rgba		path_trace(t_ray ray, t_scene scene, int depth);
t_rgba		ray_trace(t_ray ray, t_scene scene, int depth);
t_rgba		trace_ray(t_ray ray, t_scene scene, int depth, t_bool *flags);
//•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••path_tracer
// ft_vec3_utils1.c
t_vec3		ft_cross(t_vec3 a, t_vec3 b);
t_vec3		ft_vec3_scale(t_vec3 v, float s);
t_vec3		ft_vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3		ft_vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3		ft_vec3_mul(t_vec3 v, float s);
// ft_vec3_utils2.c
float		ft_get_scalaire(t_vec3 vec1, t_vec3 vec2);
t_vec3		ft_vec3_neg(t_vec3 v);
double		ft_vec3_dot(t_vec3 v1, t_vec3 v2);
double		ft_vec3_len2(t_vec3 v);
double		ft_vec3_len(t_vec3 v);
// hit_cylinder_utils.c
double		dot(t_vec3 a, t_vec3 b);
void		init_cylinder_vars(t_cyl_vars *v, t_cylinder cyl, t_ray ray);
void		solve_quadratic(t_cyl_vars *v, double *a, double *b, double *c);
t_vec3		get_projection(t_vec3 location, t_vec3 axis, double m);
t_bool		check_body_hit(t_hit_record *hit, t_cyl_vars v,
				t_cylinder cyl, t_ray ray);
// hit_cylinder_utils2.c
void		hit_cylinder_body(t_hit_record *hit, t_cyl_vars *v,
				t_cylinder cyl, t_ray ray);
t_vec3		get_cap_center(t_cylinder cyl, t_vec3 axis, double sign);
void		set_cap_normal(t_hit_record *hit, t_vec3 axis, double sign);
t_bool		check_cap_hit(t_hit_record *hit, t_cyl_vars v,
				t_cylinder cyl, t_ray ray);
void		hit_cylinder_caps(t_hit_record *hit, t_cyl_vars *v,
				t_cylinder cyl, t_ray ray);
// hit_meshes.c
t_bool		hit_sphere(t_hit_record *hit, t_sphere sphere, t_ray ray);
t_bool		hit_plane(t_hit_record *hit, t_plane plane, t_ray ray);
t_bool		hit_cylinder(t_hit_record *hit, t_mesh obj, t_ray ray);
t_bool		hit_triangle(t_hit_record *hit, t_triangle triangle, t_ray ray);
// hit_triangle_utils.c
t_bool		check_determinant(double det);
t_bool		check_barycentric_u(double u);
t_bool		check_barycentric_v(double u, double v);
void		compute_hit_data(t_hit_record *hit, t_ray ray,
				double t, t_vec3 normal);
t_bool		moller_trumbore(t_triangle tri,
				t_ray ray, t_tri_vars *v);
// hit_world.c
t_bool		hit_world(t_ray *ray_wld, const t_scene *scene, t_hit_record *out);
// pt_utils.c
void		ft_init_random_seed(unsigned int *seed);
float		ft_random_float(float min, float max, unsigned int *seed);
t_vec3		ft_normalize(t_vec3 vector);
t_vec3		get_dir(t_vec3 origine, t_vec3 dest);
float		get_dist(t_vec3 p1, t_vec3 p2);
// ray_utils.c
t_vec3		ft_ray_at(t_ray r, double t);
t_vec3		mat4_mul_vec3(t_mat4 m, t_vec3 v, double w);
t_ray		transform_ray_world_to_local(t_ray r, t_mat4 inv);
// rgba_utils.c
t_rgb		rgba_to_rgb(t_rgba c);
t_rgba		rgb_to_rgba(t_rgb c);
t_rgb		rgb_mult_rgb(t_rgb a, t_rgb b);
t_rgb		rgb_add(t_rgb a, t_rgb b);
t_rgba		ft_rgba_mult(t_rgba c1, t_rgba c2);
// rgba_utils2.c
t_rgba		ft_rgba_add(t_rgba c1, t_rgba c2);
uint32_t	ft_rgba_to_uint(t_rgba c);

#endif