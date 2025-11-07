#include "minirt.h"
/*Cette fonction prend la direction candidate Xj  et le point d'ombrage P comme entrées, et retourne un vecteur de flottants RVB.*/
// t_rgb	*get_distrib_cible_potential(t_vec3 dir, t_vec3 pos)
// {

// }

// t_vec3	get_vector(t_vec3 origine, t_vec3 dest)
// {
// 	return ((t_vec3){dest.x - origine.x, dest.y - origine.y,
// 		dest.z - origine.z});
// }

t_vec3	get_dir(t_vec3 origine, t_vec3 dest)
{
	t_vec3	vector = (t_vec3){dest.x - origine.x, dest.y - origine.y,
		dest.z - origine.z};
	float	norme = sqrtf((powf(vector.x, 2) + powf(vector.y, 2) + powf(vector.z, 2)));
	return ((t_vec3){vector.x / norme, vector.y / norme, vector.z / norme});
}

float	get_scalaire(t_vec3 vec1, t_vec3 vec2)
{
	float scalaire = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;

	if (scalaire <= 0.0)
		return (0.0);
	else
		return (scalaire);
}


int main(void)
{
	t_light	*lights = ft_calloc(sizeof(t_light) * 2);

	lights[0].light_type = DIR_LIGHT;
	lights[1].light_type = POINT_LIGHT;

	float	amb_val[3] = {2.0, 1.8, 1.5};
	float	point_light_val[3] = {800.0, 700.0, 500.0};
	t_ambiant_light *ambiant_light = &lights[0].data.ambiant_light;
	(*ambiant_light).color.r = amb_val[0];
	(*ambiant_light).color.g = amb_val[1];
	(*ambiant_light).color.b = amb_val[2];
	(*ambiant_light).brightness = 0.2;

	t_point_light	*point_light = &lights[1].data.point_light;
	(*point_light).color.r = point_light_val[0];
	(*point_light).color.g = point_light_val[1];
	(*point_light).color.b = point_light_val[2];
	(*point_light).brightness = 0.6;
	(*point_light).pos.x = -40.0;
	(*point_light).pos.y = 50.0;
	(*point_light).pos.z = 0.0;

	printf("Total light wheight: %f\n", ft_scene_light_wheight(lights));
}


// int	main(void)
// {
// 	unsigned int	*seed;
// 	/*t_list de toutes les lumieres de la scene*/
// 	t_list	*lights = ft_calloc(sizeof(t_list));
// 	/*Creation de l'ambiant light*/
// 	t_ambiant_light	*amb_light = ft_calloc(sizeof(t_ambiant_light));
// 	int	amb_val[3] = {128, 255, 0};
// 	amb_light->color.r = amb_val[0] / 255.0;
// 	amb_light->color.g = amb_val[1] / 255.0;
// 	amb_light->color.b = amb_val[2] / 255.0;
// 	amb_light->brightness = 0.2;

// 	/*Creation d'une Light*/
// 	t_point_light	*light = ft_calloc(sizeof(t_point_light));
// 	light->pos.x = -40.0;
// 	light->pos.y = 50.0;
// 	light->pos.z = 0.0;
// 	light->color.r = 10;
// 	light->color.g = 0;
// 	light->color.b = 255;
// 	light->brightness = 0.6;

// 	lights = ft_lstnew(amb_light);
// 	lights->index = 0;
// 	lights->next = ft_lstnew(light);
// 	// t_vec3	base_point = {10, 25, 15};
// 	// t_vec3	light_a = {-40.0, 50.0, 0.0};
// 	// t_vec3	dir_light_a = get_dir(base_point, light_a);
// 	seed = ft_calloc(sizeof(seed));
// 	ft_init_random_seed(seed);
// 	// printf("Ambiant Light:\nx: %f\ny : %f\nz : %f\n", ((t_ambiant_light *)lights->content)->color.r, ((t_ambiant_light *)lights->content)->color.g, ((t_ambiant_light *)lights->content)->color.b);
// 	lights = lights->next;
// 	// printf("\nLight:\nx: %f\ny : %f\nz : %f\n", ((t_light *)lights->content)->color.r, ((t_light *)lights->content)->color.g, ((t_light *)lights->content)->color.b);
// 	printf("sizeof t_ambiant: %lu\nsizeof t_light: %lu\n", sizeof(t_ambiant_light), sizeof(t_light));
	
// 	free(amb_light);
// 	return (0);
// }