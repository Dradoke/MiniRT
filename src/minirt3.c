#include "minirt.h"
#include "MLX42.h"

// uint32_t ft_rgba_to_uint(t_rgba c)
// {
//     // Clamp chaque composante entre 0.0 et 1.0 puis convertir en 0-255
//     uint8_t r = (uint8_t)(fminf(fmaxf(c.r, 0.0f), 1.0f) * 255.0f);
//     uint8_t g = (uint8_t)(fminf(fmaxf(c.g, 0.0f), 1.0f) * 255.0f);
//     uint8_t b = (uint8_t)(fminf(fmaxf(c.b, 0.0f), 1.0f) * 255.0f);
//     uint8_t a = (uint8_t)(fminf(fmaxf(c.a, 0.0f), 1.0f) * 255.0f);

//     // MLX42 attend ARGB ou RGBA selon la plateforme, ici on fait RGBA :
//     return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | ((uint32_t)a);
// }


// void    build_camera_basis(t_cam *cam)
// {
//     t_vec3 world_up = {{0, 1, 0}};  // "haut" du monde
//     t_vec3 forward = ft_normalize(cam->rotation);

//     t_vec3 right;
//     if (fabs(forward.x) > 0.999f && fabs(forward.z) < 0.001f)
//         world_up = (t_vec3){{0, 0, 1}};  // éviter colinéarité

//     right = ft_normalize(ft_cross(world_up, forward));
//     t_vec3 up = ft_cross(forward, right);

//     cam->forward = forward;
//     cam->right = right;
//     cam->up = up;

//     cam->aspect_ratio = (float)WIDTH / HEIGHT;  // nécessaire pour le rendu
// }

// t_ray generate_camera_ray(t_cam *cam, int x, int y, int w, int h)
// {
//     float px = (2.0f * ((x + 0.5f) / w) - 1.0f)
//              * tanf(cam->aov * 0.5f * PI / 180.0f)
//              * cam->aspect_ratio;

//     float py = (1.0f - 2.0f * ((y + 0.5f) / h))
//              * tanf(cam->aov * 0.5f * PI / 180.0f);

//     t_vec3 dir = ft_normalize(ft_vec3_add(
//                     ft_vec3_add(ft_vec3_scale(cam->right, px),
//                                 ft_vec3_scale(cam->up, py)),
//                     cam->forward));

//     return (t_ray){ cam->location, dir };
// }

/* (ft_rgba_to_uint, build_camera_basis, generate_camera_ray restent ceux du fichier actif) */

// int main(int argc, char **argv)
// {
//     if (argc != 2)
//     {
//         fprintf(stderr, "Usage: %s <file.rt>\n", argv[0]);
//         return 1;
//     }

//     t_data *data = ft_calloc(sizeof(*data)); /* corrige l'appel à ft_calloc */
//     if (!data)
//     {
//         fprintf(stderr, "Error malloc data\n");
//         return 1;
//     }

//     ft_init_random_seed(&data->scene.seed);

//     if (!ft_parser(data, argv[1]))
//     {
//         fprintf(stderr, "Parser error\n");
//         return 1;
//     }

//     if (!data->scene.cam.aov)
//     {
//         fprintf(stderr, "No camera in scene\n");
//         return 1;
//     }
//     // data->scene.ambient_light.brightness = 0.0; // désactiver ambiant pour test
//     // data->scene.light[0].color = (t_rgba){{255, 255, 255, 255}}; // augmenter intensité lumière pour test
//     build_camera_basis(&data->scene.cam);

//     mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
//     if (!mlx)
//     {
//         fprintf(stderr, "MLX init fail\n");
//         return 1;
//     }

//     mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
//     if (!img)
//     {
//         fprintf(stderr, "MLX image fail\n");
//         return 1;
//     }

//     if (mlx_image_to_window(mlx, img, 0, 0) < 0)
//     {
//         fprintf(stderr, "Window fail\n");
//         return 1;
//     }

//     /* debug rapide : afficher couleur renvoyée par trace_path pour quelques rayons */
//     {
//         t_ray r_center = generate_camera_ray(&data->scene.cam, WIDTH/2, HEIGHT/2, WIDTH, HEIGHT);
//         trace_path(r_center, data->scene, MAX_DEPTH);

//         /* rayon direct vers le premier cylindre (si trouvé) */
//         for (int i = 0; i < data->scene.obj_count[MESH]; ++i)
//         {
//             if (data->scene.mesh[i].type == CY)
//             {
//                 t_vec3 target = data->scene.mesh[i].u_data.cylinder.location;
//                 t_vec3 dir = ft_normalize(ft_vec3_sub(target, data->scene.cam.location));
//                 t_ray r_to_cyl = (t_ray){ data->scene.cam.location, dir };
//                 trace_path(r_to_cyl, data->scene, MAX_DEPTH);
//                 break;
//             }
//         }
//     }

//     for (int y = 0; y < HEIGHT; y++)
//     {
//         for (int x = 0; x < WIDTH; x++)
//         {
//             t_ray ray = generate_camera_ray(&data->scene.cam, x, y, WIDTH, HEIGHT);
//             t_rgba color = trace_path(ray, data->scene, MAX_DEPTH);
//             uint32_t pixel = ft_rgba_to_uint(color);
//             mlx_put_pixel(img, x, y, pixel);
//         }
//     }

//     mlx_loop(mlx);
//     return 0;
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