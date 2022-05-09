NAME = cub3D

# Paths

SRC_PATH = src/
LIB_PATH = lib/
OBJ_PATH = obj/
TEST_PATH = test/

# Names

SRC_NAME =	main.c \
			draw_pixel.c \
			draw.c \
			mouse_gun.c \
			mouse_gun_utils.c \
			map.c \
			utils.c \
			math_extensions.c \
			raycasting.c \
			movement.c \
			calc_distance.c \
			calc_distance_utils.c \
			parsing/parsing.c \
			parsing/clean_line.c \
			parsing/measure_map.c \
			parsing/parse_header_infos.c \
			parsing/check_map.c \
			parsing/utils.c \
			debug.c \
			init.c \
			memory.c \
			key_handling.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

TEST_SRC_NAME =	test_main.cpp \

TEST_HEADER_NAME =	test_utils.h \

# Files
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
TEST_SRC = $(addprefix $(TEST_PATH),$(TEST_SRC_NAME))
TEST_HEADER = $(addprefix $(TEST_PATH), $(TEST_HEADER_NAME))

# Flags

CXX = g++
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT_FLAGS = $(LIB_PATH)libft/libft.a -I$(LIB_PATH)/libft
TEST_FLAGS	= -pthread -lgtest

# Flags mlx for Linux and MacOS

UNAME=$(shell uname)
ifeq ($(UNAME), Linux)
	MLXFLAGS = -L$(LIB_PATH)mlx -lmlx -L/usr/lib -I$(LIB_PATH)mlx -lXext -lX11 -lm -lz
else
	MLXFLAGS = -L$(LIB_PATH)mlx -lmlx -framework OpenGL -framework AppKit -lm
endif

ifeq ($(MAKECMDGOALS),test)
	CFLAGS += -g -D TESTING
endif
ifeq ($(MAKECMDGOALS),testinc)
	CFLAGS += -g -D TESTING
endif

all: $(NAME)

PRE: 
	@echo 'pre exec'
	@make -C $(LIB_PATH)/libft/ --no-print-directory
	@make -C $(LIB_PATH)/mlx/ --no-print-directory

$(NAME): PRE $(OBJ)
	@echo "Build $(NAME)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) $(MLXFLAGS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(SRC_PATH) -o $@ -c $<

clean:
	@make clean -C $(LIB_PATH)libft/ --no-print-directory
	@echo "Delete cube3d/$(OBJ_PATH)"
	@rm -rf $(OBJ_PATH) db

fclean:	clean
	@make fclean -C $(LIB_PATH)libft/ --no-print-directory
	@echo "Delete cube3d/$(NAME)"
	@rm -f $(NAME) db

test: PRE $(OBJ) $(SRC) $(TEST_SRC) $(TEST_HEADER)
	@make -C $(LIB_PATH)/libft/ --no-print-directory
	$(CXX) -g -D TESTING -o $(NAME)_test $(OBJ) $(TEST_SRC) $(TEST_FLAGS) -I./$(SRC_PATH) $(LIBFT_FLAGS) $(TEST_FLAGS) -lm

re:	fclean all

.PHONY: all clean fclean re mlx libft db
