#include "minirt.h"
#include <stdio.h>

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

static void	see_vec3(t_vec3 vec, char *name, int indent)
{
	int	i;

	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%s%s:%s (%.3f, %.3f, %.3f)\n", CYAN, name, RESET,
		vec.x, vec.y, vec.z);
}

static void	see_rgba(t_rgba color, char *name, int indent)
{
	int	i;

	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%s%s:%s R:%d G:%d B:%d A:%d %s(0x%08X)%s\n",
		YELLOW, name, RESET, color.r, color.g, color.b, color.a,
		MAGENTA, color.color, RESET);
}

static void	see_ambient_light(t_ambient_light *al, int indent)
{
	int	i;

	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%s[AMBIENT LIGHT]%s @%p\n", BOLD GREEN, RESET, (void *)al);
	i = 0;
	while (i++ < indent + 1)
		printf("  ");
	printf("%sBrightness:%s %.2f\n", CYAN, RESET, al->brightness);
	see_rgba(al->color, "Color", indent + 1);
}

static void	see_mat4(t_mat4 mat, char *name, int indent)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%s%s:%s\n", CYAN, name, RESET);
	i = -1;
	while (++i < 4)
	{
		k = 0;
		while (k++ < indent + 1)
			printf("  ");
		j = -1;
		while (++j < 4)
			printf("%7.3f ", mat[i][j]);
		printf("\n");
	}
}

static char	*get_cam_mode_name(t_ui8 mode)
{
	if (mode == STANDING)
		return ("STANDING");
	else if (mode == PLANE)
		return ("PLANE");
	return ("UNKNOWN");
}

static void	see_camera(t_cam *cam, int indent)
{
	int	i;

	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%s[CAMERA]%s @%p\n", BOLD GREEN, RESET, (void *)cam);
	see_mat4(cam->transform, "Transform", indent + 1);
	i = 0;
	while (i++ < indent + 1)
		printf("  ");
	printf("%sMode:%s %s\n", CYAN, RESET, get_cam_mode_name(cam->mode));
	see_vec3(cam->location, "Location", indent + 1);
	see_vec3(cam->rotation, "Rotation", indent + 1);
	i = 0;
	while (i++ < indent + 1)
		printf("  ");
	printf("%sAOV:%s %d\n", CYAN, RESET, cam->aov);
}

static void	see_point_light(t_point_light *light, int indent, int idx)
{
	int	i;

	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%s[POINT LIGHT #%d]%s @%p\n", BOLD GREEN, idx, RESET,
		(void *)light);
	see_vec3(light->location, "Location", indent + 1);
	i = 0;
	while (i++ < indent + 1)
		printf("  ");
	printf("%sBrightness:%s %.2f\n", CYAN, RESET, light->brightness);
	see_rgba(light->color, "Color", indent + 1);
}

static void	see_sphere(t_sphere *sp, int indent)
{
	int	i;

	see_vec3(sp->location, "Location", indent);
	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%sDiameter:%s %.2f\n", CYAN, RESET, sp->diameter);
	see_rgba(sp->color, "Color", indent);
}

static void	see_plane(t_plane *pl, int indent)
{
	see_vec3(pl->location, "Location", indent);
	see_vec3(pl->rotation, "Rotation", indent);
	see_rgba(pl->color, "Color", indent);
}

static void	see_cylinder(t_cylinder *cy, int indent)
{
	int	i;

	see_vec3(cy->location, "Location", indent);
	see_vec3(cy->rotation, "Rotation", indent);
	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%sDiameter:%s %.2f\n", CYAN, RESET, cy->diameter);
	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%sHeight:%s %.2f\n", CYAN, RESET, cy->height);
	see_rgba(cy->color, "Color", indent);
}

static void	see_triangle(t_triangle *tr, int indent)
{
	see_vec3(tr->vertex1, "Vertex1", indent);
	see_vec3(tr->vertex2, "Vertex2", indent);
	see_vec3(tr->vertex3, "Vertex3", indent);
	see_rgba(tr->color, "Color", indent);
}

static void	see_mesh_data(t_mesh *mesh, int indent)
{
	if (mesh->type == SP)
		see_sphere(&mesh->u_data.sphere, indent);
	else if (mesh->type == PL)
		see_plane(&mesh->u_data.plane, indent);
	else if (mesh->type == CY)
		see_cylinder(&mesh->u_data.cylinder, indent);
	else if (mesh->type == TR)
		see_triangle(&mesh->u_data.triangle, indent);
}

static char	*get_type_name(t_type type)
{
	if (type == NONE)
		return ("NONE");
	else if (type == A)
		return ("AMBIENT");
	else if (type == C)
		return ("CAMERA");
	else if (type == L)
		return ("LIGHT");
	else if (type == SP)
		return ("SPHERE");
	else if (type == PL)
		return ("PLANE");
	else if (type == CY)
		return ("CYLINDER");
	else if (type == TR)
		return ("TRIANGLE");
	return ("UNKNOWN");
}

static void	see_mesh(t_mesh *mesh, int indent, int idx)
{
	int	i;

	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%s[MESH #%d - %s]%s @%p\n", BOLD BLUE, idx,
		get_type_name(mesh->type), RESET, (void *)mesh);
	see_mat4(mesh->transform, "Transform", indent + 1);
	see_mat4(mesh->inv_transform, "Inv Transform", indent + 1);
	see_mesh_data(mesh, indent + 1);
}

static void	see_lights(t_scene *scene, int indent)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%s--- Lights (%d) ---%s\n", BOLD, scene->obj_count[LIGHT],
		RESET);
	j = -1;
	while (++j < scene->obj_count[LIGHT])
		see_point_light(&scene->light[j], indent + 1, j);
}

static void	see_meshes(t_scene *scene, int indent)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%s--- Meshes (%d) ---%s\n", BOLD, scene->obj_count[MESH], RESET);
	j = -1;
	while (++j < scene->obj_count[MESH])
		see_mesh(&scene->mesh[j], indent + 1, j);
}

static void	see_scene(t_scene *scene, int indent)
{
	int	i;

	i = 0;
	while (i++ < indent)
		printf("  ");
	printf("%s=== SCENE ===%s @%p\n", BOLD YELLOW, RESET, (void *)scene);
	see_ambient_light(&scene->ambient_light, indent + 1);
	see_camera(&scene->cam, indent + 1);
	see_lights(scene, indent + 1);
	see_meshes(scene, indent + 1);
}

static void	print_flag(char *name, t_bool value)
{
	if (value)
		printf("%s%s:ON%s", GREEN, name, RESET);
	else
		printf("%s%s:OFF%s", RED, name, RESET);
}

static void	see_flags(t_data *data)
{
	printf("  %sflags:%s [", CYAN, RESET);
	print_flag("RMB", data->flags[RMB]);
	printf(", ");
	print_flag("FISHEYE", data->flags[FISHEYE]);
	printf(", ");
	print_flag("NEED_RENDER", data->flags[NEED_RENDER]);
	printf("]\n");
}

static void	see_keys_row(t_data *data, int start, int end)
{
	char	*key_names[11];
	int		i;

	key_names[0] = "Q";
	key_names[1] = "W";
	key_names[2] = "E";
	key_names[3] = "A";
	key_names[4] = "S";
	key_names[5] = "D";
	key_names[6] = "P";
	key_names[7] = "C";
	key_names[8] = "SPACE";
	key_names[9] = "CTRL";
	i = start - 1;
	while (++i < end)
	{
		if (i > start)
			printf(", ");
		print_flag(key_names[i], data->keys[i]);
	}
}

static void	see_keys(t_data *data)
{
	printf("  %skeys:%s [", CYAN, RESET);
	see_keys_row(data, 0, 6);
	printf("]\n");
	printf("        [");
	see_keys_row(data, 6, KEY_COUNT);
	printf("]\n");
}

static void	see_mouse_data(t_data *data)
{
	printf("  %slast_pos:%s [%.2f, %.2f]\n", CYAN, RESET,
		data->last_pos[0], data->last_pos[1]);
	printf("  %smouse_delta:%s dx=%.2f, dy=%.2f\n", CYAN, RESET,
		data->mouse_dx, data->mouse_dy);
	printf("  %slast_resize_time:%s %.3f\n", CYAN, RESET,
		data->last_resize_time);
}

void	see_data(t_data *data)
{
	printf("\n%s╔════════════════════════════════════════╗%s\n",
		BOLD MAGENTA, RESET);
	printf("%s║        DEBUG: t_data STRUCTURE         ║%s\n",
		BOLD MAGENTA, RESET);
	printf("%s╚════════════════════════════════════════╝%s\n\n",
		BOLD MAGENTA, RESET);
	printf("%s[t_data]%s @%p\n", BOLD RED, RESET, (void *)data);
	printf("  %smlx:%s @%p\n", CYAN, RESET, (void *)data->mlx);
	printf("  %simg:%s @%p\n", CYAN, RESET, (void *)data->img);
	printf("  %sparse_list:%s @%p\n", CYAN, RESET, (void *)data->parse_list);
	see_flags(data);
	see_keys(data);
	see_mouse_data(data);
	printf("\n");
	see_scene(&data->scene, 1);
	printf("\n%s════════════════════════════════════════%s\n\n",
		BOLD MAGENTA, RESET);
}
