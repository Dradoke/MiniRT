#include "minirt.h"

static t_vec3	transform_ray_dir(t_vec3 dir, t_mat4 matrix)
{
	t_vec3	res;

	res.x = dir.x * matrix[0][0] + dir.y * matrix[0][1]
		+ dir.z * matrix[0][2];
	res.y = dir.x * matrix[1][0] + dir.y * matrix[1][1]
		+ dir.z * matrix[1][2];
	res.z = dir.x * matrix[2][0] + dir.y * matrix[2][1]
		+ dir.z * matrix[2][2];
	return (res);
}

static t_vec3	rotate_vector(t_vec3 v, t_vec3 rotation)
{
	t_vec3	rotated_v;
	double	cos_x;
	double	sin_x;
	double	cos_y;
	double	sin_y;
	double	cos_z;
	double	sin_z;

	cos_x = cos(rotation.x);
	sin_x = sin(rotation.x);
	cos_y = cos(rotation.y);
	sin_y = sin(rotation.y);
	cos_z = cos(rotation.z);
	sin_z = sin(rotation.z);
	rotated_v.x = v.x * (cos_y * cos_z)
		+ v.y * (sin_x * sin_y * cos_z - cos_x * sin_z)
		+ v.z * (cos_x * sin_y * cos_z + sin_x * sin_z);
	rotated_v.y = v.x * (cos_y * sin_z)
		+ v.y * (sin_x * sin_y * sin_z + cos_x * cos_z)
		+ v.z * (cos_x * sin_y * sin_z - sin_x * cos_z);
	rotated_v.z = v.x * (-sin_y)
		+ v.y * (sin_x * cos_y)
		+ v.z * (cos_x * cos_y);
	return (rotated_v);
}

static t_rgba	shoot_ray(t_ray *ray, t_scene *scene)
{
	t_rgba	color;
	double	ax;
	double	ay;
	double	az;

	(void)scene;
	ax = fabs(ray->dir.x);
	ay = fabs(ray->dir.y);
	az = fabs(ray->dir.z);
	if (ax > ay && ax > az)
	{
		if (ray->dir.x > 0)
			color.color = 0x6464FFFF; // X+ Bleu Clair (R=100, G=100, B=255)
		else
			color.color = 0x000064FF; // X- Bleu Foncé (R=0, G=0, B=100)
	}
	else if (ay > ax && ay > az)
	{
		if (ray->dir.y > 0)
			color.color = 0xFF6464FF; // Y+ Rouge Clair (R=255, G=100, B=100)
		else
			color.color = 0x640000FF; // Y- Rouge Foncé (R=100, G=0, B=0)
	}
	else
	{
		if (ray->dir.z > 0)
			color.color = 0x64FF64FF; // Z+ Vert Clair (R=100, G=255, B=100)
		else
			color.color = 0x006400FF; // Z- Vert Foncé (R=0, G=100, B=0)
	}
	return (color);
}

static void	perspective(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	double	aspect_ratio;
	double	viewport_h;
	double	viewport_w;
	t_vec3	pixel_dir;

	aspect_ratio = (double)data->mlx->width / (double)data->mlx->height;
	viewport_h = 2.0 * tan(ft_degtorad(data->scene.cam.aov) / 2.0);
	viewport_w = viewport_h * aspect_ratio;
	pixel_dir.x = (2.0 * (x + 0.5) / data->mlx->width - 1.0) * viewport_w / 2.0;
	pixel_dir.y = (1.0 - 2.0 * (y + 0.5) / data->mlx->height) * viewport_h / 2.0;
	pixel_dir.z = -1.0;
	ray->dir = vec3_normalize(transform_ray_dir(pixel_dir,
				data->scene.cam.matrix[NORMAL]));
}

static void	fisheye(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	t_vec3	pixel_dir;
	double	angle_h;
	double	angle_v;

	angle_h = ft_degtorad((x - data->mlx->width / 2.0) * (data->scene.cam.aov / data->mlx->width));
	angle_v = ft_degtorad((y - data->mlx->height / 2.0) * (data->scene.cam.aov / data->mlx->height));
	pixel_dir = (t_vec3){{0, 0, -1}};
	pixel_dir = rotate_vector(pixel_dir, (t_vec3){{ft_degtorad((y - data->mlx->height / 2.0) * (data->scene.cam.aov / data->mlx->height)), ft_degtorad((x - data->mlx->width / 2.0) * (data->scene.cam.aov / data->mlx->width)), 0}});
	pixel_dir = rotate_vector(pixel_dir, data->scene.cam.rotation);
	ray->dir = vec3_normalize(pixel_dir);
}

t_bool	ft_render(t_data *data)
{
	t_ray	ray;
	t_rgba	color;
	t_i32	x;
	t_i32	y;

	ray.origin.x = data->scene.cam.matrix[NORMAL][0][3];
	ray.origin.y = data->scene.cam.matrix[NORMAL][1][3];
	ray.origin.z = data->scene.cam.matrix[NORMAL][2][3];
	y = 0;
	while (y < data->mlx->height)
	{
		x = 0;
		while (x < data->mlx->width)
		{
			if (data->flags[FISHEYE])
				fisheye(data, &ray, x, y);
			else
				perspective(data, &ray, x, y);
			color = shoot_ray(&ray, &data->scene);
			mlx_put_pixel(data->img, x, y, color.color);
			x++;
		}
		y++;
	}
	return (true);
}
