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
	double	cos_a[3];
	double	sin_a[3];

	cos_a[X] = cos(rotation.x);
	sin_a[X] = sin(rotation.x);
	cos_a[Y] = cos(rotation.y);
	sin_a[Y] = sin(rotation.y);
	cos_a[Z] = cos(rotation.z);
	sin_a[Z] = sin(rotation.z);
	rotated_v.x = v.x * (cos_a[Y] * cos_a[Z])
		+ v.y * (sin_a[X] * sin_a[Y] * cos_a[Z] - cos_a[X] * sin_a[Z])
		+ v.z * (cos_a[X] * sin_a[Y] * cos_a[Z] + sin_a[X] * sin_a[Z]);
	rotated_v.y = v.x * (cos_a[Y] * sin_a[Z])
		+ v.y * (sin_a[X] * sin_a[Y] * sin_a[Z] + cos_a[X] * cos_a[Z])
		+ v.z * (cos_a[X] * sin_a[Y] * sin_a[Z] - sin_a[X] * cos_a[Z]);
	rotated_v.z = v.x * (-sin_a[Y])
		+ v.y * (sin_a[X] * cos_a[Y])
		+ v.z * (cos_a[X] * cos_a[Y]);
	return (rotated_v);
}

void	perspective(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	double	aspect_ratio;
	double	viewport_h;
	double	viewport_w;
	t_vec3	pixel_dir;

	aspect_ratio = (double)data->mlx->width / (double)data->mlx->height;
	viewport_h = 2.0 * tan(ft_degtorad(data->scene.cam.aov) / 2.0);
	viewport_w = viewport_h * aspect_ratio;
	pixel_dir.x = (2.0 * (x + 0.5) / data->mlx->width - 1.0) * viewport_w / 2.0;
	pixel_dir.y = (1.0 - 2.0 * (y + 0.5) / data->mlx->height)
		* viewport_h / 2.0;
	pixel_dir.z = -1.0;
	ray->dir = vec3_normalize(transform_ray_dir(pixel_dir,
				data->scene.cam.matrix[NORMAL]));
}

void	fisheye(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	t_vec3	pixel_dir;
	double	angle_h;
	double	angle_v;

	angle_h = ft_degtorad((x - data->mlx->width / 2.0)
			* ((double)data->scene.cam.aov / (double)data->mlx->width));
	angle_v = ft_degtorad((y - data->mlx->height / 2.0)
			* ((double)data->scene.cam.aov / (double)data->mlx->width));
	pixel_dir = (t_vec3){{0, 0, -1}};
	pixel_dir = rotate_vector(pixel_dir, (t_vec3){{-angle_v, -angle_h, 0}});
	ray->dir = vec3_normalize(transform_ray_dir(pixel_dir,
				data->scene.cam.matrix[NORMAL]));
}
