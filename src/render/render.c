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

/**
 * @brief Effectue une rotation d'un vecteur en utilisant les angles d'Euler.
 * NOTE: Cette implémentation est basique. Pour des rotations complexes,
 * les quaternions ou les matrices de rotation sont plus robustes.
 * @param v Le vecteur à faire pivoter.
 * @param rotation Les angles de rotation (x, y, z) en radians.
 */
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

/**
 * @brief Lance un rayon dans la scène et détermine la couleur du pixel.
 * C'est le cœur de votre raytracer.
 *
 * @param ray Le rayon à lancer.
 * @param scene La scène contenant tous les objets.
 * @return La couleur (t_rgba) de ce que le rayon a touché.
 */
static t_rgba	shoot_ray(t_ray *ray, t_scene *scene)
{
	(void)scene; // Pour l'instant, nous n'utilisons pas la scène.

	// TODO: C'est ici que vous devez implémenter la logique d'intersection.
	// 1. Itérer sur tous les objets de la scène.
	// 2. Pour chaque objet, calculer s'il y a une intersection avec le rayon.
	// 3. Garder l'intersection la plus proche.
	// 4. Si une intersection est trouvée, calculer la couleur (lumière, ombres, etc.).
	// 5. Sinon, renvoyer la couleur de fond (ex: un dégradé de ciel).

	// Pour l'instant, on retourne un dégradé basé sur la direction Y du rayon
	// pour visualiser que les rayons sont bien orientés.
	double	t = 0.5 * (ray->dir.y + 1.0);
	t_rgba	start_color = {{0, 170, 255, 255}}; // Bleu ciel
	t_rgba	end_color = {{255, 255, 255, 255}}; // Blanc
	t_rgba	color;

	color.r = (1.0 - t) * end_color.r + t * start_color.r;
	color.g = (1.0 - t) * end_color.g + t * start_color.g;
	color.b = (1.0 - t) * end_color.b + t * start_color.b;
	color.a = 255;
	return (color);
}

static void	perspective(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	double	aspect_ratio;
	double	viewport_h;
	double	viewport_w;
	t_vec3	pixel_dir;

	// 1. Calculer les dimensions du plan de vue virtuel (viewport)
	aspect_ratio = (double)data->mlx->width / (double)data->mlx->height;
	viewport_h = 2.0 * tan(ft_degtorad(data->scene.cam.aov) / 2.0);
	viewport_w = viewport_h * aspect_ratio;

	// 2. Calculer la position du pixel sur ce plan de vue
	// On convertit les coordonnées du pixel [0, width] en [-1, 1] et on met à l'échelle
	pixel_dir.x = (2.0 * (x + 0.5) / data->mlx->width - 1.0) * viewport_w / 2.0;
	pixel_dir.y = (1.0 - 2.0 * (y + 0.5) / data->mlx->height) * viewport_h / 2.0;
	pixel_dir.z = -1.0; // Le plan est à une distance de -1 (convention)

	// 3. Orienter le rayon selon la rotation de la caméra
	pixel_dir = rotate_vector(pixel_dir, data->scene.cam.rotation);

	// 4. Normaliser le vecteur direction et l'assigner au rayon
	ray->dir = vec3_normalize(transform_ray_dir(pixel_dir,
				data->scene.cam.transform));
}

static void	fisheye(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	t_vec3	pixel_dir;
	double	angle_h;
	double	angle_v;

	// 1. Calculer les angles de déviation par rapport au centre
	angle_h = ft_degtorad((x - data->mlx->width / 2.0) * (data->scene.cam.aov / data->mlx->width));
	angle_v = ft_degtorad((y - data->mlx->height / 2.0) * (data->scene.cam.aov / data->mlx->height));

	// 2. Créer un vecteur de base pointant vers l'avant
	pixel_dir = (t_vec3){{0, 0, -1}};

	// 3. Appliquer les rotations pour ce pixel
	pixel_dir = rotate_vector(pixel_dir, (t_vec3){{ft_degtorad((y - data->mlx->height / 2.0) * (data->scene.cam.aov / data->mlx->height)), ft_degtorad((x - data->mlx->width / 2.0) * (data->scene.cam.aov / data->mlx->width)), 0}});

	// 4. Appliquer la rotation globale de la caméra
	pixel_dir = rotate_vector(pixel_dir, data->scene.cam.rotation);

	// 5. Normaliser et assigner (la rotation devrait préserver la norme si bien faite)
	ray->dir = vec3_normalize(pixel_dir);
}

t_bool	ft_render(t_data *data)
{
	t_ray	ray;
	t_rgba	color;
	t_i32	x;
	t_i32	y;

	ray.origin.x = data->scene.cam.transform[0][3];
	ray.origin.y = data->scene.cam.transform[1][3];
	ray.origin.z = data->scene.cam.transform[2][3];
	y = 0;
	while (y < data->mlx->height)
	{
		x = 0;
		while (x < data->mlx->width)
		{
			// Choisir la fonction de projection en fonction du flag
			if (data->flags[FISHEYE])
				fisheye(data, &ray, x, y);
			else
				perspective(data, &ray, x, y);

			// Lancer le rayon et obtenir la couleur
			color = shoot_ray(&ray, &data->scene);

			// Dessiner le pixel sur l'image
			mlx_put_pixel(data->img, x, y, color.color);
			x++;
		}
		y++;
	}
	return (true);
}
