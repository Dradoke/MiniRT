#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Project Name
NAME			=	minirt

# Compiler Setting
CC				=	gcc
CFLAG			=	-Wall -Wextra -Werror -g3 -O3 -march=native -ffast-math

# Directory
INC_DIR			=	include/
LIB_DIR			=	lib/
OBJ_DIR			=	obj/
SRC_DIR			=	src/

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Source File
SRC				=	$(addprefix src/, \
					$(DEBUG) \
					$(HOOKS) \
					$(PARSER) \
					$(RENDER) \
					$(UTILS) \
					$(PATH_TRACER) \
					minirt.c \
					)
PATH_TRACER		=	$(addprefix path_tracer/, \
					$(SIMPLE_TRACER) \
					ft_vec3_utils1.c \
					hit_cylinder_utils.c \
					hit_cylinder_utils2.c \
					hit_meshes.c \
					hit_world.c \
					ft_vec3_utils2.c \
					pt_utils.c \
					ray_utils.c \
					rgba_utils.c \
					rgba_utils2.c \
					)

SIMPLE_TRACER	=	$(addprefix simple_tracer/, \
					st_utils.c \
					st_utils2.c \
					st_utils3.c \
					st.c \
					)

DEBUG			=	$(addprefix debug/, \
					see_data.c \
					)

HOOKS			=	$(addprefix hooks/, \
					hooks.c \
					keys.c \
					mouse.c \
					)

PARSER			=	$(addprefix parser/, \
					ft_lst_to_arr.c \
					ft_parser.c \
					ft_transform_utils.c \
					parse_mesh.c \
					parse_unique.c \
					parse_value_1.c \
					parse_value_2.c \
					)

RENDER			=	$(addprefix render/, \
					cam_utils.c \
					cam.c \
					projection.c \
					render.c \
					$(PATH_TRACER) \
					)

PATH_TRACER		=	$(addprefix path_tracer/, \
					$(SIMPLE_TRACER) \
					ft_vec3_utils1.c \
					hit_cylinder_utils.c \
					hit_cylinder_utils2.c \
					hit_meshes.c \
					hit_triangle_utils.c \
					hit_world.c \
					ft_vec3_utils2.c \
					pt_utils.c \
					ray_utils.c \
					rgba_utils.c \
					rgba_utils2.c \
					)

SIMPLE_TRACER	=	$(addprefix simple_tracer/, \
					st_utils.c \
					st_utils2.c \
					st_utils3.c \
					st.c \
					)

DEBUG			=	$(addprefix debug/, \
					see_data.c \
					)

HOOKS			=	$(addprefix hooks/, \
					hooks.c \
					keys.c \
					mouse.c \
					)

PARSER			=	$(addprefix parser/, \
					ft_lst_to_arr.c \
					ft_parser.c \
					ft_transform_utils.c \
					parse_mesh.c \
					parse_unique.c \
					parse_value_1.c \
					parse_value_2.c \
					)

RENDER			=	$(addprefix render/, \
					cam_utils.c \
					cam.c \
					projection.c \
					render.c \
					)

UTILS			=	$(addprefix utils/, \
					ft_error.c \
					matrix.c \
					matrix2.c \
					matrix3.c \
					vector1.c \
					vector2.c \
					)

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Object File
OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Include Flag
IFLAG			=	$(addprefix -I, \
					$(INC_DIR) \
					$(LIBFT_DIR)/include \
					$(MLX42_DIR)/include/MLX42 \
					)

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Library Path & File
LIBFT_DIR		=	$(LIB_DIR)libft/
LIBFT			=	$(LIBFT_DIR)libft.a
MLX42_DIR		=	$(LIB_DIR)MLX42/
MLX42			=	$(MLX42_DIR)/build/libmlx42.a

# Library Dependencies for MLX42
MLX_DEPS		=	-ldl -lglfw -pthread -lm

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# All Target
all: $(NAME)

# LibFT Make Rule
$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

# MLX42 Make Rule
$(MLX42):
	@[ -d "$(MLX42_DIR)/.git" ] || git clone --depth 1 https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR)
	@cd $(MLX42_DIR) && git pull --rebase --autostash 2>/dev/null || true
	@cd $(MLX42_DIR) && git submodule update --init --recursive
	@cmake -S $(MLX42_DIR) -B $(MLX42_DIR)/build
	@cmake --build $(MLX42_DIR)/build -j4

# Main Target
$(NAME): $(MLX42) $(OBJ) $(LIBFT) 
	@$(CC) $(CFLAG) $(OBJ) $(LIBFT) $(MLX42) $(MLX_DEPS) -o $(NAME)
	@echo "Welcome $@ ! 🤩🤙"

# Object File Compilation Rule
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAG) $(IFLAG) -c $< -o $@
	@echo "Good Morning $(notdir $@) ! 👋😇"

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Mandatory Target
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@rm -rf $(MLX42_DIR)/build
	@echo "See You Soon $(OBJ_DIR) And Your Content... 🤧💔"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "Bye-Bye $(NAME) ! 🥺💋"

re: fclean all

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Phony Target
.PHONY: all clean fclean re
