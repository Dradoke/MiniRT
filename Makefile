#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Project Name
NAME			=	minirt

# Compiler Setting
CC				=	cc
CFLAG			=	-Wall -Wextra -Werror -g3

# Directory
INC_DIR			=	include/
LIB_DIR			=	lib/
OBJ_DIR			=	obj/
SRC_DIR			=	src/

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Source File
SRC				=	$(addprefix src/, \
					minirt.c \
					restir/restir_utils.c \
					restir/light_sampling.c \
					$(UTILS) \
					)

UTILS			=	$(addprefix utils/, \
					)

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Object File
OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Include Flag
IFLAG			=	$(addprefix -I, \
					$(INC_DIR) \
					$(LIBFT_DIR)/include \
					)
# 					$(MLX42_DIR)/include \

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# Library Path & File
LIBFT_DIR		=	$(LIB_DIR)libft/
LIBFT			=	$(LIBFT_DIR)libft.a
# MLX42_DIR		=	$(LIB_DIR)MLX42/
# MLX42			=	$(MLX42_DIR)/build/libmlx42.a

# Library Dependencies for MLX42
MLX_DEPS		=	-ldl -lglfw -pthread

#•••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••

# All Target
all: $(NAME)

# LibFT Make Rule
$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

# MLX42 Make Rule
$(MLX42):
	@cmake $(MLX42_DIR) -B $(MLX42_DIR)/build && make -C $(MLX42_DIR)/build -j4

# Main Target
# $(MLX42)
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAG) $(OBJ) $(LIBFT) -o $(NAME) -lm
# 	$(MLX42) $(MLX_DEPS)
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
