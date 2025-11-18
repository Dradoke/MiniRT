#ifndef RIS_H
# define RIS_H

/**
 * @file ris.h
 * @brief Specific structures for restir
 */

/// @def Maximum rebounds number
# ifndef MAX_DEPTH
#  define MAX_DEPTH 5
# endif

/// @def Sample Per Pixel
# ifndef SPP
#  define SPP 16
# endif

# define RANDF_MIN 0.0
# define RANDF_MAX 1.0

# define PI 3.14159265f
# define LIGHT_PDF 1/(4*PI)
# define EPSILON 0.0001f

typedef struct	s_rgb
{
	float	r;
	float	g;
	float	b;
}				t_rgb;

/// @brief Ambiant light element, extended as A in .rt file
typedef struct	s_ambiant_light
{
	float			brightness;
	t_rgba			color;
}				t_ambiant_light;

/// @brief This is the structure for (the “champion” sample).
typedef struct	s_sample
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
typedef struct	s_pool
{
	t_sample	sample; /// champion sample chosen
	float		sum_weight;		/// Sum of the weights (sum_weights)
	int			nb_samples;		/// number of sample seen
}				t_pool;

/// @brief Hold all the material informations
/// @param albedo diffuse color RGB
/// @param spec_reflexion specular reflexion
/// @param roughness rugosity of the material, affect the reflexion
typedef struct	s_material
{
	t_rgb	albedo;
	t_vec3	spec_reflexion;
	float	roughness;
	/*Rajouter un pointeur vers la fonction BRDF*/
}				t_material;

/// @brief Regroup every needed informations for the color calculation at p point
/// @param p Postion
/// @param n Normal
/// @param material surface proprerties reference
/// @param omega_o direction to where the rayon come from
typedef struct	s_hit_record
{
	t_vec3		p;
	t_vec3		n;
	t_bool		has_touched;
	t_vec3		omega_o;
	t_rgba		color;
}				t_hit_record;

typedef struct	s_path_tracing
{
	t_hit_record	hit;
	t_vec3			d_new;
	t_rgba			direct_light;
	t_rgba			indirect_light;
	t_ray			next_ray;
	t_rgba			entrant_light;
	t_rgba			out_light;

}				t_path_tracing;


float	get_scalaire(t_vec3 vec1, t_vec3 vec2);
t_vec3	ft_normalize(t_vec3 vector);
t_vec3	ft_cross(t_vec3 a, t_vec3 b);
t_vec3	get_dir(t_vec3 origine, t_vec3 dest);
void	ft_init_random_seed(unsigned int *seed);
float	ft_random_float(float min, float max, unsigned int *seed);
t_rgb	ft_init_rgb(void);
t_vec3	ft_vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	ft_vec3_scale(t_vec3 v, float s);
t_rgba	ft_rgba_mult(t_rgba c1, t_rgba c2);
t_rgba	ft_rgba_add(t_rgba c1, t_rgba c2);
#endif