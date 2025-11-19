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

/// @brief Return the direction to a destination from an origin point
/// @param origine origine point
/// @param dest destination point
/// @return Return the direction to a destination from an origin point as a t_vec3
t_vec3	get_dir(t_vec3 origine, t_vec3 dest)
{
	t_vec3	vector = (t_vec3){dest.x - origine.x, dest.y - origine.y,
		dest.z - origine.z};
	float	norme = sqrtf((powf(vector.x, 2)
		+ powf(vector.y, 2) + powf(vector.z, 2)));
	return ((t_vec3){vector.x / norme, vector.y / norme, vector.z / norme});
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

float	ft_direct_contribution(t_vec3 point_loc, t_point_light light)
{
	float	cos_factor;
	float	p1;
	float	p2;

	cos_factor = ft_get_scalaire(point_loc, light.location);
	if (cos_factor < 0.0)
		cos_factor = 0;
	p1 = LIGHT_PDF;
	p2 = ft_brdf_pdf(cos_factor);

}

/// @brief Take two vectors to produce a third one that is perpendicular to the first two vector
/// @param a Vector 1
/// @param b Vector 2
/// @return Return a vector perpendicular to the two vectors in parameters
t_vec3	ft_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	c;

	c.x = (a.y * b.z) - (a.z * b.y);
	c.y = (a.x * b.z) - (a.z * b.x);
	c.z = (a.y * b.x) - (a.x * b.y);
	return (c);
}

/// @brief This function takes a vector and a scalar, and multiplies each component of the vector by the scalar
/// @param v vector
/// @param s scalar
/// @return vector "v" * scalar "s"
t_vec3	ft_vec3_scale(t_vec3 v, float s)
{
	return (t_vec3){v.x * s, v.y * s, v.z * s};
}

t_vec3	ft_vec3_add(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

t_vec3	ft_vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

t_rgba	ft_rgba_mult(t_rgba c1, t_rgba c2)
{
	t_rgba	result;

	result.r = c1.r * c2.r;
	result.g = c1.g * c2.g;
	result.b = c1.b * c2.b;
	result.a = c1.a * c2.a;
	return (result);
}

t_vec3 ft_vec3_neg(t_vec3 v)
{
	return (t_vec3){-v.x, -v.y, -v.z};
}

double ft_vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

double ft_vec3_len2(t_vec3 v)
{
	return ft_vec3_dot(v, v);
}

double ft_vec3_len(t_vec3 v)
{
	return sqrt(v_len2(v));
}

t_vec3 ft_ray_at(t_ray r, double t)
{
	return ft_vec3_add(r.origin, ft_vec3_scale(r.dir, t));
}

t_rgba	ft_rgba_add(t_rgba c1, t_rgba c2)
{
	t_rgba	result;

	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;
	result.a = c1.a + c2.a;
	return (result);
}

t_vec3 mat4_mul_vec3(t_mat4 m, t_vec3 v, double w)
{
	t_vec3 out;

	out.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * w;
	out.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * w;
	out.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * w;

	return out;
}

t_mat4 mat4_transpose(t_mat4 m)
{
	t_mat4 out;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			out.m[i][j] = m.m[j][i];

	return out;
}

t_ray transform_ray_world_to_local(t_ray r, t_mat4 inv)
{
	t_ray out;

	out.origin = mat4_mul_vec3(inv, r.origin, 1.0);
	out.dir = mat4_mul_vec3(inv, r.dir, 0.0);
	out.dir = ft_normalize(out.dir);

	return out;
}

void transform_hit_local_to_world(t_hit_record *hit, t_mat4 transform, t_mat4 inv_transform)
{
	hit->p = mat4_mul_vec3(transform, hit->p, 1.0);
	t_mat4 invT = mat4_transpose(inv_transform);
	hit->n = mat4_mul_vec3(invT, hit->n, 0.0);
	hit->n = ft_normalize(hit->n);
}

t_bool	hit_sphere(t_hit_record *hit, t_sphere sphere, t_ray ray)
{
	t_hit_sp_data data;

	data.oc = ft_vec3_sub(ray.origin, sphere.location);
	data.a = 1.0;
	data.b = 2 * ft_vec3_dot(data.oc, ray.dir);
	data.c = ft_vec3_dot(data.oc, data.oc) - sphere.radius * sphere.radius;
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
	return (TRUE);
}

t_bool	hit_cylinder(t_hit_record *hit, t_mesh obj, t_ray ray)
{
	t_cylinder	cyl;
	t_vec3	oc;
	double	dx;
	double	dy;
	double	dz;
	double	ox;
	double	oy;
	double	oz;
	double	r;
	double	half;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	sqrt_disc;
	double	tcand[2];
	int	i;
	double	y;
	double	best_t;
	double	y_cap;
	double	t_cap;
	t_vec3	p;

	cyl = obj.u_data.cylinder;
	oc = ft_vec3_sub(ray.origin, cyl.location);
	dx = ray.dir.x;
	dy = ray.dir.y;
	dz = ray.dir.z;
	ox = oc.x;
	oy = oc.y;
	oz = oc.z;
	r = cyl.diameter * 0.5;
	half = cyl.height * 0.5;
	a = (dx * dx) + (dz * dz);
	b = 2 * ((ox * dx) + (oz * dz));
	c = (ox * ox) + (oz * oz) - (r * r);
	best_t = INFINITY;
	if (fabsf(a) >= EPS)
	{
		disc = (b * b) - (4 * a * c);
		if (disc >= 0.0)
		{
			sqrt_disc = sqrt(disc);
			tcand[0] = (-b - sqrt_disc) / (2 * a);
			tcand[1] = (-b + sqrt_disc) / (2 * a);
			i = 0;
			while (i <= 1)
			{
				if (tcand[i] > EPS)
				{
					y = oy + tcand[i] * dy;
					if ((y > (-half - EPS) && y < (half + EPS)) && tcand[i] < best_t)
					{
						best_t = tcand[i];
						hit->p = ft_ray_at(ray, tcand[i]);
						hit->n = ft_vec3_sub(hit->p, cyl.location);
						hit->n.y = 0;
					}
				}
				i++;
			}
		}
	}
	if (fabs(dy) > EPS)
	{
		i = 0;
		while (i <= 1)
		{
			if (i == 0)
				y_cap = cyl.location.y + half;
			else
				y_cap = cyl.location.y - half;
			t_cap = (y_cap - ray.origin.y) / dy;
			if (t_cap > EPS)
			{
				p = ft_ray_at(ray, t_cap);
				if (((pow((p.x - cyl.location.x), 2) + pow((p.z - cyl.location.z), 2)) <= (r * r + EPS)) && t_cap < best_t)
				{
					best_t = t_cap;
					hit->p = p;
					if (i == 0)
						hit->n = (t_vec3){0, 1, 0};
					else
						hit->n = (t_vec3){0, -1, 0};
				}
			}
			i++;
		}
	}
	if (best_t == INFINITY)
		return (FALSE);
	else
	{
		hit->t = best_t;
		hit->n = ft_normalize(hit->n);
		return (TRUE);
	}
}
