#include "minirt.h"
#include <math.h>

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
/// @return Return the direction to a destination from an origin point as a t_vec3
t_vec3	get_dir(t_vec3 origine, t_vec3 dest)
{
	t_vec3	vector = (t_vec3){{dest.x - origine.x, dest.y - origine.y,
		dest.z - origine.z}};
	float	norme = sqrtf((powf(vector.x, 2)
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

// float	ft_direct_contribution(t_vec3 point_loc, t_point_light light)
// {
// 	float	cos_factor;
// 	float	p1;
// 	float	p2;

// 	cos_factor = ft_get_scalaire(point_loc, light.location);
// 	if (cos_factor < 0.0)
// 		cos_factor = 0;
// 	p1 = LIGHT_PDF;
// 	p2 = ft_brdf_pdf(cos_factor);

// }

/// @brief Take two vectors to produce a third one that is perpendicular to the first two vector
/// @param a Vector 1
/// @param b Vector 2
/// @return Return a vector perpendicular to the two vectors in parameters
t_vec3	ft_cross(t_vec3 a, t_vec3 b)
{
    t_vec3	c;

    c.x = (a.y * b.z) - (a.z * b.y);
    /* CORRECTION : Formule standard du produit vectoriel (Main Droite) */
    c.y = (a.z * b.x) - (a.x * b.z); 
    c.z = (a.x * b.y) - (a.y * b.x);
    return (c);
}

/// @brief This function takes a vector and a scalar, and multiplies each component of the vector by the scalar
/// @param v vector
/// @param s scalar
/// @return vector "v" * scalar "s"
t_vec3	ft_vec3_scale(t_vec3 v, float s)
{
	return (t_vec3){{v.x * s, v.y * s, v.z * s}};
}

t_vec3	ft_vec3_add(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3){{v1.x + v2.x, v1.y + v2.y, v1.z + v2.z}};
}

t_vec3	ft_vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3){{v1.x - v2.x, v1.y - v2.y, v1.z - v2.z}};
}

t_vec3    ft_vec3_mul(t_vec3 v, float s)
{
    t_vec3 r;

    r.x = v.x * s;
    r.y = v.y * s;
    r.z = v.z * s;
    return (r);
}

/* convertir t_rgba (uint8) -> t_rgb (float 0..1) */
t_rgb rgba_to_rgb(t_rgba c)
{
    t_rgb out;
    out.r = (float)c.r / 255.0f;
    out.g = (float)c.g / 255.0f;
    out.b = (float)c.b / 255.0f;
    return out;
}

/* convertir t_rgb (float 0..1) -> t_rgba (uint8, clamp) */
t_rgba rgb_to_rgba(t_rgb c)
{
    t_rgba out;
    out.r = (uint8_t)(fminf(fmaxf(c.r, 0.0f), 1.0f) * 255.0f);
    out.g = (uint8_t)(fminf(fmaxf(c.g, 0.0f), 1.0f) * 255.0f);
    out.b = (uint8_t)(fminf(fmaxf(c.b, 0.0f), 1.0f) * 255.0f);
    out.a = 255;
    return out;
}

/* multiplicaton float : retourne t_rgb en 0..1 */
t_rgb rgb_mult_rgb(t_rgb a, t_rgb b)
{
    t_rgb r;
    r.r = a.r * b.r;
    r.g = a.g * b.g;
    r.b = a.b * b.b;
    return r;
}

/* addition float */
t_rgb rgb_add(t_rgb a, t_rgb b)
{
    t_rgb r;
    r.r = a.r + b.r;
    r.g = a.g + b.g;
    r.b = a.b + b.b;
    return r;
}

/* si tu veux garder ft_rgba_mult pour compat, l'implémenter en appelant rgba_to_rgb/rgb_to_rgba */
t_rgba ft_rgba_mult(t_rgba c1, t_rgba c2)
{
    t_rgb a = rgba_to_rgb(c1);
    t_rgb b = rgba_to_rgb(c2);
    t_rgb r = rgb_mult_rgb(a, b);
    return rgb_to_rgba(r);
}

t_rgba ft_rgba_add(t_rgba c1, t_rgba c2)
{
    float r = (c1.r / 255.0f) + (c2.r / 255.0f);
    float g = (c1.g / 255.0f) + (c2.g / 255.0f);
    float b = (c1.b / 255.0f) + (c2.b / 255.0f);
    t_rgba out;
    out.r = (uint8_t)(fminf(r, 1.0f) * 255.0f);
    out.g = (uint8_t)(fminf(g, 1.0f) * 255.0f);
    out.b = (uint8_t)(fminf(b, 1.0f) * 255.0f);
    out.a = 255;
    return (out);
}

t_vec3 ft_vec3_neg(t_vec3 v)
{
	return (t_vec3){{-v.x, -v.y, -v.z}};
}

double ft_vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

double ft_vec3_len2(t_vec3 v)
{
	return (ft_vec3_dot(v, v));
}

double ft_vec3_len(t_vec3 v)
{
	return (sqrt(ft_vec3_len2(v)));
}

t_vec3 ft_ray_at(t_ray r, double t)
{
	return (ft_vec3_add(r.origin, ft_vec3_scale(r.dir, t)));
}

// t_rgba	ft_rgba_add(t_rgba c1, t_rgba c2)
// {
// 	t_rgba	result;

// 	result.r = c1.r + c2.r;
// 	result.g = c1.g + c2.g;
// 	result.b = c1.b + c2.b;
// 	result.a = c1.a + c2.a;
// 	return (result);
// }

t_vec3 mat4_mul_vec3(t_mat4 m, t_vec3 v, double w)
{
	t_vec3 out;

	out.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * w;
	out.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * w;
	out.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * w;

	return out;
}

// t_mat4 mat4_transpose(t_mat4 m)
// {
// 	t_mat4 out;

// 	for (int i = 0; i < 4; i++)
// 		for (int j = 0; j < 4; j++)
// 			out[i][j] = m[j][i];

// 	return out;
// }

t_ray transform_ray_world_to_local(t_ray r, t_mat4 inv)
{
	t_ray out;

	out.origin = mat4_mul_vec3(inv, r.origin, 1.0);
	out.dir = mat4_mul_vec3(inv, r.dir, 0.0);
	out.dir = ft_normalize(out.dir);

	return out;
}

// void transform_hit_local_to_world(t_hit_record *hit, t_mat4 transform, t_mat4 inv_transform)
// {
// 	hit->p = mat4_mul_vec3(transform, hit->p, 1.0);
// 	t_mat4 invT = mat4_transpose(inv_transform);
// 	hit->n = mat4_mul_vec3(invT, hit->n, 0.0);
// 	hit->n = ft_normalize(hit->n);
// }

t_bool	hit_sphere(t_hit_record *hit, t_sphere sphere, t_ray ray)
{
	t_hit_sp_data data;

	data.oc = ft_vec3_sub(ray.origin, sphere.location);
	data.a = 1.0;
	data.b = 2 * ft_vec3_dot(data.oc, ray.dir);
	data.c = ft_vec3_dot(data.oc, data.oc) - (sphere.diameter * 0.5) * (sphere.diameter * 0.5);
	data.disc = (data.b * data.b) - (4 * data.a * data.c);
	if (data.disc < 0)
		return (FALSE);
	data.sqrt_disc = sqrt(data.disc);
	data.t1 = (-data.b - data.sqrt_disc) / (2 * data.a);
	data.t2 = (-data.b + data.sqrt_disc) / (2 * data.a);
	if (data.t1 > EPS)
		hit->t = data.t1;
	else if (data.t2 > EPS)
		hit->t = data.t2;
	else
		return (FALSE);
	hit->p = ft_ray_at(ray, hit->t);
	hit->n = ft_normalize(ft_vec3_sub(hit->p, sphere.location));
	return (TRUE);
}

t_bool	hit_plane(t_hit_record *hit, t_plane plane, t_ray ray)
{
	double	denom;
	double	t;

	denom = ft_vec3_dot(plane.rotation, ray.dir);
	if (fabs(denom) < EPS)
		return (FALSE);
	t = ft_vec3_dot(ft_vec3_sub(plane.location, ray.origin), plane.rotation)
		/ denom;
	if (t < EPS)
		return (FALSE);
	hit->t = t;
	hit->p = ft_ray_at(ray, hit->t);
	if (ft_vec3_dot(ray.dir, plane.rotation) < 0)
		hit->n = plane.rotation;
	else
		hit->n = ft_vec3_neg(plane.rotation);
	hit->n = ft_normalize(hit->n);
	return (TRUE);
}

/* Fonction utilitaire pour le produit scalaire si elle n'existe pas, ou utilise la tienne */
static double dot(t_vec3 a, t_vec3 b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }

t_bool	hit_cylinder(t_hit_record *hit, t_mesh obj, t_ray ray)
{
    t_cylinder	cyl = obj.u_data.cylinder;
    t_vec3		oc;
    t_vec3		axis;
    double		r;
    double		a, b, c, disc;
    double		m;
    double		t;
    t_vec3		proj;
    int			i;

    /* 1. Configuration en Espace Monde */
    /* CORRECTION : Utiliser 'rotation' comme axe directeur */
    axis = ft_normalize(cyl.rotation); 
    oc = ft_vec3_sub(ray.origin, cyl.location);
    r = cyl.diameter * 0.5;

    /* 2. Équation quadratique vectorielle (Cylindre infini) */
    /* (D - (D.V)V)^2 * t^2 + ... */
    double dd = dot(ray.dir, ray.dir);
    double dv = dot(ray.dir, axis);
    double d_oc = dot(oc, oc);
    double oc_v = dot(oc, axis);
    double od = dot(oc, ray.dir);

    a = dd - (dv * dv);
    b = 2.0 * (od - (dv * oc_v));
    c = d_oc - (oc_v * oc_v) - (r * r);

    hit->t = INFINITY;
    
    /* Résolution quadratique */
    disc = b * b - 4 * a * c;
    if (disc >= 0)
    {
        double sqrt_disc = sqrt(disc);
        double t_vals[2] = {(-b - sqrt_disc) / (2 * a), (-b + sqrt_disc) / (2 * a)};

        for (i = 0; i < 2; i++)
        {
            t = t_vals[i];
            if (t > EPS && t < hit->t)
            {
                /* Vérification de la hauteur (Projection sur l'axe) */
                /* m = (P - C) . V */
                m = oc_v + t * dv;
                if (m >= -(cyl.height / 2.0) && m <= (cyl.height / 2.0))
                {
                    hit->t = t;
                    hit->p = ft_ray_at(ray, t);
                    
                    /* 3. Calcul de la Normale PROPRE (Correction du bruit) */
                    /* N = normalize(P - (C + V * m)) */
                    /* proj = C + V * m */
                    proj.x = cyl.location.x + axis.x * m;
                    proj.y = cyl.location.y + axis.y * m;
                    proj.z = cyl.location.z + axis.z * m;
                    
                    hit->n = ft_vec3_sub(hit->p, proj);
                    hit->n = ft_normalize(hit->n);
                }
            }
        }
    }

    /* 4. Intersection avec les disques (Bouchons) */
    if (fabs(dv) > EPS)
    {
        double t_cap;
        t_vec3 cap_center;
        t_vec3 p_cap;
        
        // Bouchon Haut (+H/2) et Bas (-H/2)
        double signs[2] = {1.0, -1.0};
        for (i = 0; i < 2; i++)
        {
            // Centre du disque : C + sign * (H/2) * V
            double h_shift = signs[i] * (cyl.height / 2.0);
            cap_center.x = cyl.location.x + axis.x * h_shift;
            cap_center.y = cyl.location.y + axis.y * h_shift;
            cap_center.z = cyl.location.z + axis.z * h_shift;

            // t = (Center - Origin) . N / (Dir . N)
            t_cap = dot(ft_vec3_sub(cap_center, ray.origin), axis) / dv;
            
            if (t_cap > EPS && t_cap < hit->t)
            {
                p_cap = ft_ray_at(ray, t_cap);
                // Vérifier distance au centre du disque : |P - Center|^2 <= r^2
                t_vec3 v_rad = ft_vec3_sub(p_cap, cap_center);
                if (dot(v_rad, v_rad) <= (r * r))
                {
                    hit->t = t_cap;
                    hit->p = p_cap;
                    // Normale : axis si i=0 (haut), -axis si i=1 (bas)
                    if (signs[i] > 0) hit->n = axis;
                    else              hit->n = (t_vec3){{-axis.x, -axis.y, -axis.z}};
                }
            }
        }
    }

    return (hit->t != INFINITY);
}

t_bool	hit_world(t_ray *ray_wld, const t_scene *scene, t_hit_record *out)
{
    double			best_t;
    t_hit_record	tmp_hit;
    t_bool			hit_any;
    int				i;
    t_mesh			*obj;
    t_bool			hit;

    best_t = INFINITY;
    hit_any = FALSE;
    tmp_hit.t = INFINITY;

    for (i = 0; i < scene->obj_count[MESH]; i++)
    {
        obj = &scene->mesh[i];
        hit = FALSE;

        /* CORRECTION MAJEURE : Suppression de la logique "Local Space" cassée. */
        /* On envoie le rayon Monde directement à tous les objets. */
        
        if (obj->type == SP)
            hit = hit_sphere(&tmp_hit, obj->u_data.sphere, *ray_wld);
        else if (obj->type == PL)
            hit = hit_plane(&tmp_hit, obj->u_data.plane, *ray_wld);
        else if (obj->type == CY)
            hit = hit_cylinder(&tmp_hit, *obj, *ray_wld);
        
        /* Si on touche un objet et qu'il est plus proche que le précédent */
        if (hit && tmp_hit.t < best_t && tmp_hit.t > EPS)
        {
            best_t = tmp_hit.t;
            *out = tmp_hit;
            
            /* Copie de la couleur */
            if (obj->type == SP)      out->color = obj->u_data.sphere.color;
            else if (obj->type == PL) out->color = obj->u_data.plane.color;
            else if (obj->type == CY) out->color = obj->u_data.cylinder.color;
            
            hit_any = TRUE;
        }
    }
    return (hit_any);
}

uint32_t ft_rgba_to_uint(t_rgba c)
{
    /* accepte à la fois c en 0..1 (float-like) ou en 0..255 (uint8),
       détecte et packe correctement */
    float rf = (float)c.r;
    float gf = (float)c.g;
    float bf = (float)c.b;
    float af = (float)c.a;
    uint8_t r, g, b, a;

    if (rf > 1.5f || gf > 1.5f || bf > 1.5f || af > 1.5f)
    {
        /* valeurs déjà en 0..255 */
        r = (uint8_t)rf;
        g = (uint8_t)gf;
        b = (uint8_t)bf;
        a = (uint8_t)af;
    }
    else
    {
        /* valeurs en 0..1 */
        r = (uint8_t)(fminf(fmaxf(rf, 0.0f), 1.0f) * 255.0f);
        g = (uint8_t)(fminf(fmaxf(gf, 0.0f), 1.0f) * 255.0f);
        b = (uint8_t)(fminf(fmaxf(bf, 0.0f), 1.0f) * 255.0f);
        a = (uint8_t)(fminf(fmaxf(af, 0.0f), 1.0f) * 255.0f);
    }
    return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | ((uint32_t)a);
}
