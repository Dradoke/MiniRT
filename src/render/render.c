#include "minirt.h"

t_vec3	vec3(t_f64 x, t_f64 y, t_f64 z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return (vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec3_norm(t_vec3 v)
{
	t_f64	l;

	l = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (vec3(v.x / l, v.y / l, v.z / l));
}

t_f64	dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

int	hit_sphere(t_sphere s, t_ray r)
{
	t_vec3	oc;
	t_f64	a;
	t_f64	b;
	t_f64	c;
	t_f64	discriminant;

	oc = vec3_sub(r.origin, s.location);
	a = dot(r.dir, r.dir);
	b = 2.0 * dot(oc, r.dir);
	c = dot(oc, oc) - s.diameter * s.diameter;
	discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

void	render_image(t_sphere sphere, mlx_image_t *img)
{
	int		y;
	int		x;
	t_f64	u;
	t_f64	v;
	t_ray	ray;

	y = 0;
	while (y < (t_f64)img->height)
	{
		x = 0;
		while (x < (t_f64)img->width)
		{
			u = (2.0 * x / (t_f64)img->width - 1.0);
			v = (1.0 - 2.0 * y / (t_f64)img->height);
			ray.origin = vec3(0, 0, 0);
			ray.dir = vec3_norm(vec3(u, v, -1));
			if (hit_sphere(sphere, ray))
				mlx_put_pixel(img, x, y, sphere.color);
			else
				mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}
