#include "minirt.h"
#include <math.h>

t_bool	hit_sphere(t_hit_record *hit, t_sphere sphere, t_ray ray)
{
	t_hit_sp_data	data;

	data.oc = ft_vec3_sub(ray.origin, sphere.location);
	data.a = 1.0;
	data.b = 2 * ft_vec3_dot(data.oc, ray.dir);
	data.c = ft_vec3_dot(data.oc, data.oc) - (sphere.diameter * 0.5)
		* (sphere.diameter * 0.5);
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

	denom = ft_vec3_dot(plane.direction, ray.dir);
	if (fabs(denom) < EPS)
		return (FALSE);
	t = ft_vec3_dot(ft_vec3_sub(plane.location, ray.origin), plane.direction)
		/ denom;
	if (t < EPS)
		return (FALSE);
	hit->t = t;
	hit->p = ft_ray_at(ray, hit->t);
	if (ft_vec3_dot(ray.dir, plane.direction) < 0)
		hit->n = plane.direction;
	else
		hit->n = ft_vec3_neg(plane.direction);
	hit->n = ft_normalize(hit->n);
	return (TRUE);
}

t_bool	hit_cylinder(t_hit_record *hit, t_mesh obj, t_ray ray)
{
	t_cylinder	cyl;
	t_cyl_vars	v;

	cyl = obj.u_data.cylinder;
	hit->t = INFINITY;
	init_cylinder_vars(&v, cyl, ray);
	hit_cylinder_body(hit, &v, cyl, ray);
	hit_cylinder_caps(hit, &v, cyl, ray);
	return (hit->t != INFINITY);
}

t_bool  hit_triangle(t_hit_record *hit, t_triangle triangle, t_ray ray)
{
    t_vec3  e1;
    t_vec3  e2;
    t_vec3  p_vec;
    t_vec3  t_vec;
    t_vec3  q_vec;
    double  det;
    double  inv_det;
    double  t;
    double  u;
    double  v;

    e1 = ft_vec3_sub(triangle.vertex2, triangle.vertex1);
    e2 = ft_vec3_sub(triangle.vertex3, triangle.vertex1);

    p_vec = ft_cross(ray.dir, e2);
    det = ft_vec3_dot(e1, p_vec);

    /* CORRECTION 1 : Culling (Optionnel mais recommandé) */
    /* Si det est proche de 0, le rayon est parallèle au triangle */
    if (fabs(det) < EPS)
        return (FALSE);

    inv_det = 1.0 / det;

    t_vec = ft_vec3_sub(ray.origin, triangle.vertex1);
    u = ft_vec3_dot(t_vec, p_vec) * inv_det;

    if (u < 0.0 || u > 1.0)
        return (FALSE);

    q_vec = ft_cross(t_vec, e1);
    v = ft_vec3_dot(ray.dir, q_vec) * inv_det;

    if (v < 0.0 || (u + v) > 1.0)
        return (FALSE);

    t = ft_vec3_dot(e2, q_vec) * inv_det;

    /* CORRECTION 2 : Vérification stricte de la distance */
    /* On ne modifie hit->t QUE si on est sûr d'avoir trouvé mieux */
    /* Et on ne compare pas avec hit->t ici car hit->t n'est pas fiable à ce stade */
    /* On vérifie juste que t est devant la caméra */
    
    if (t > EPS)
    {
        hit->t = t;
        hit->p = ft_ray_at(ray, hit->t);
        
        /* Calcul de la normale */
        /* Attention : l'ordre du produit vectoriel dépend de l'ordre des sommets (Main Droite) */
        /* E1 x E2 ou E2 x E1 ? Standard : (V2-V1) x (V3-V1) = E1 x E2 */
        hit->n = ft_normalize(ft_cross(e1, e2)); 
        
        /* Face Culling / Orientation de la normale */
        if (ft_vec3_dot(ray.dir, hit->n) > 0)
            hit->n = ft_vec3_neg(hit->n);
            
        return (TRUE);
    }

    return (FALSE);
}