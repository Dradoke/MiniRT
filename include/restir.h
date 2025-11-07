#ifndef RIS_H
# define RIS_H

/**
 * @file ris.h
 * @brief Specific structures for restir
 */

typedef enum	e_light_type
{
	NONE,
	POINT_LIGHT,
	DIR_LIGHT
}				t_light_type;

typedef struct	s_rgb
{
	float	r;
	float	g;
	float	b;
}				t_rgb;

/// @brief vec3 for Position(p), Direction(x), Normal(n), specular reflexion, light radiance
typedef struct	s_vec3
{
	float	x;
	float	y;
	float	z;
}				t_vec3;

/// @brief Ambiant light element, extended as A in .rt file
typedef struct	s_ambiant_light
{
	float			brightness;
	t_rgb			color;
}				t_ambiant_light;

/// @brief Point Light element, extended as L in .rt file
typedef struct	s_point_light
{
	t_vec3	pos;
	float	brightness;
	t_rgb	color;
}				t_point_light;

typedef	struct	s_light
{
	t_light_type	light_type;
	float			light_energy;
	union
	{
		t_ambiant_light	ambiant_light;
		t_point_light	point_light;
	}	data;
	
}				t_light;


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
/// @param omega_o direction to where th rayon come from
typedef struct	s_hit_record
{
	t_vec3		p;
	t_vec3		n;
	t_material	*material;
	t_vec3		omega_o;
}				t_hit_record;


float	get_scalaire(t_vec3 vec1, t_vec3 vec2);
t_vec3	get_dir(t_vec3 origine, t_vec3 dest);
void	ft_init_random_seed(unsigned int *seed);
float	ft_random_float(float min, float max, unsigned int *seed);
float	ft_scene_light_wheight(t_light *lights);
t_rgb	ft_init_rgb(void);
float	ft_luminance(t_rgb light_rgb);
t_rgb	ft_flux_rgb_dl(t_light lights);
t_rgb	ft_flux_rgb_pl(t_light lights);
#endif