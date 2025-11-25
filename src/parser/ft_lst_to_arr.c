#include "minirt.h"

static void	compute_transform_matrices(t_node *node, t_mat4 *trans_m,
                t_mat4 *rot_m, t_mat4 *scale_m)
{
    t_vec3	scale_vec;
    t_vec3	trans_vec;
    t_f32	r;
    t_f32	h;

    trans_vec = node->u_data.sphere.location;
    *trans_m = mat4_translation(trans_vec);
    *rot_m = mat4_identity();
    if (node->type == SP)
    {
        r = node->u_data.sphere.diameter / 2.0f;
        scale_vec = (t_vec3){{r, r, r}};
    }
    else if (node->type == CY)
    {
        r = node->u_data.cylinder.diameter / 2.0f;
        h = node->u_data.cylinder.height / 2.0f;
        scale_vec = (t_vec3){{r, h, r}};
    }
    else
        scale_vec = (t_vec3){{1.0f, 1.0f, 1.0f}};
    *scale_m = mat4_scaling(scale_vec);
}

static void	build_transform(t_node *node, t_mat4 *out_transform,
                t_mat4 *out_inv_transform)
{
    t_mat4	trans_m;
    t_mat4	rot_m;
    t_mat4	scale_m;
    t_mat4	inv_trans_m;
    t_mat4	inv_scale_m;

    compute_transform_matrices(node, &trans_m, &rot_m, &scale_m);

    inv_trans_m = mat4_translation((t_vec3){{
        -node->u_data.sphere.location.x,
        -node->u_data.sphere.location.y,
        -node->u_data.sphere.location.z
    }});

    inv_scale_m = mat4_scaling((t_vec3){{
        1.0f / scale_m.m[0][0],
        1.0f / scale_m.m[1][1],
        1.0f / scale_m.m[2][2]
    }});

    *out_transform = mat4_multiply(trans_m, mat4_multiply(rot_m, scale_m));
    *out_inv_transform = mat4_multiply(inv_scale_m, inv_trans_m);
}

static void	add_mesh(t_node *node, t_scene *scene, int idx)
{
    t_mesh *m;

    if (!scene || !scene->mesh)
        return ;
    m = &scene->mesh[idx];
    m->type = node->type;
    ft_memcpy(&m->u_data, &node->u_data, sizeof(m->u_data));
    build_transform(node, &m->transform, &m->inv_transform);
}

/* Transforme la parse_list en tableaux dans scene sans écrire hors-borne,
   et copie ambient / camera / lights */
t_bool	ft_lst_to_arr(t_data *data)
{
    t_list	*cur;
    int		mesh_count;
    int		light_count;
    int		i;
    int		li;

    if (!data)
        return (false);
    /* compter meshes et lights */
    mesh_count = 0;
    light_count = 0;
    cur = data->parse_list;
    while (cur)
    {
        t_node *n = (t_node *)cur->content;
        if (!n)
        {
            cur = cur->next;
            continue;
        }
        if (n->type == SP || n->type == PL || n->type == CY || n->type == TR)
            mesh_count++;
        if (n->type == L)
            light_count++;
        cur = cur->next;
    }
    data->scene.obj_count[MESH] = mesh_count;
    data->scene.obj_count[LIGHT] = light_count;
    /* allouer tableaux */
    if (mesh_count > 0)
    {
        data->scene.mesh = ft_calloc(mesh_count * sizeof(t_mesh));
        if (!data->scene.mesh)
            return (false);
    }
    else
        data->scene.mesh = NULL;
    if (light_count > 0)
    {
        data->scene.light = ft_calloc(light_count * sizeof(t_point_light));
        if (!data->scene.light)
            return (false);
    }
    else
        data->scene.light = NULL;
    /* remplir */
    i = 0;
    li = 0;
    cur = data->parse_list;
    while (cur)
    {
        t_node *n = (t_node *)cur->content;
        if (!n)
        {
            cur = cur->next;
            continue;
        }
        if (n->type == A)
            data->scene.ambient_light = n->u_data.ambient_light;
        else if (n->type == C)
            data->scene.cam = n->u_data.cam;
        else if (n->type == L && data->scene.light && li < light_count)
        {
            data->scene.light[li] = n->u_data.point_light;
            li++;
        }
        else if ((n->type == SP || n->type == PL || n->type == CY || n->type == TR)
                && data->scene.mesh && i < mesh_count)
        {
            add_mesh(n, &data->scene, i);
            i++;
        }
        cur = cur->next;
    }
    return (true);
}
