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
	// ft_init_random_seed(seed);
// 	// printf("Ambiant Light:\nx: %f\ny : %f\nz : %f\n", ((t_ambiant_light *)lights->content)->color.r, ((t_ambiant_light *)lights->content)->color.g, ((t_ambiant_light *)lights->content)->color.b);
// 	lights = lights->next;
// 	// printf("\nLight:\nx: %f\ny : %f\nz : %f\n", ((t_light *)lights->content)->color.r, ((t_light *)lights->content)->color.g, ((t_light *)lights->content)->color.b);
// 	printf("sizeof t_ambiant: %lu\nsizeof t_light: %lu\n", sizeof(t_ambiant_light), sizeof(t_light));
	
// 	free(amb_light);
// 	return (0);
// }