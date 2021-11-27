NAME = minirt

CC = gcc

HEADERS_PATH = ./includes/

INCLUDES = -I$(HEADERS_PATH) 

CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

DIR = $(shell pwd)

DIRSRC = sources
WAIT = 2

GREEN ='\033[0;32m'
RED ='\033[0;31m'

MLX_OPENGL_PATH = ./minilibx_opengl
MLX_LINUX_PATH = ./minilibx_linux
MLX_WINDOWS_PATH = ./minilibx_windows

MLX_PATH = 

FRAMEWORKS = 

LINKS = 

UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
	MLX_PATH = $(MLX_OPENGL_PATH)
	MLX_NAME = libmlx.a
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
	LINKS = -L$(MLX_PATH)/
	FRAMEWORKS += -framework OpenGL -framework Appkit
	INCLUDES += -I$(MLX_OPENGL_PATH)
	LOAD_DYLIB = install_name_tool -change $(MLX_NAME) $(DIR)/$(MLX_LIB) $(NAME)
	SRC = $(addprefix $(DIRSRC)/, \
			check_error.c get_next_line.c light.c cylinder.c \
		  plane.c sphere.c init.c lists1.c \
		  lists2.c \
		  mini_rt.c utils.c utils2.c utils3.c \
		  utils4.c no_leaks.c pars_amb.c pars_cam.c \
		  pars_cyl.c pars_light.c pars_pl.c \
		  pars_sp.c raytrace.c keys_macos.c)
endif

ifeq ($(UNAME),Linux)
	MLX_PATH = $(MLX_LINUX_PATH)
	MLX_NAME = libmlx.a
	INCLUDES += -I$(MLX_LINUX_PATH)
	LINKS += -L$(MLX_PATH) -lXext -lX11 -lxcb -lXau -lXdmcp -lm
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
	SRC = $(addprefix $(DIRSRC)/, \
			check_error.c get_next_line.c light.c cylinder.c \
		  plane.c sphere.c init.c lists1.c \
		  lists2.c \
		  mini_rt.c utils.c utils2.c utils3.c \
		  utils4.c no_leaks.c pars_amb.c pars_cam.c \
		  pars_cyl.c pars_light.c pars_pl.c \
		  pars_sp.c raytrace.c keys_linux.c)
endif

ifeq ($(OS),Windows_NT)
	MLX_PATH = $(MLX_WINDOWS_PATH)
	MLX_NAME = libmlx.a
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
	LINKS = -L"$(MLX_PATH)/SDL/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image \
	-lSDL2_mixer -lSDL2_ttf  -lmingw32 -lSDL2main -luser32 -lgdi32 -lwinmm -ldxguid
	INCLUDES += -I$(MLX_WINDOWS_PATH)/includes
	LOAD_DYLIB = cp $(MLX_PATH)/*.dll ../
	SRC = $(addprefix $(DIRSRC)/, \
			check_error.c get_next_line.c light.c cylinder.c \
		  plane.c sphere.c init.c lists1.c \
		  lists2.c \
		  mini_rt.c utils.c utils2.c utils3.c \
		  utils4.c no_leaks.c pars_amb.c pars_cam.c \
		  pars_cyl.c pars_light.c pars_pl.c \
		  pars_sp.c raytrace.c keys_windows.c)
endif

OBJDIR = obj

OBJ = $(SRC:$(DIRSRC)/%.c= $(OBJDIR)/%.o)

OBJ_PATHS = $(OBJDIR) $(shell ls -R $(DIRSRC) | grep / | sed 's/://g' | sed 's/src/$(OBJDIR)/g')

HEADERS = $(addprefix $(HEADERS_PATH), \
 mini_rt.h)

all: $(NAME) $(HEADERS) $(WAIT)
	@echo "$(GREEN)______________________________________________________"
	@echo "$(GREEN)~####~~##~~##~~####~~~####~~#####~~~####~~~####~~~~###"
	@echo "$(GREEN)##~~~~~##~~##~##~~##~##~~##~##~~~~~##~~~~~##~~~~~~~###"
	@echo "$(GREEN)~####~~##~~##~##~~~~~##~~~~~####~~~~####~~~####~~~~###"
	@echo "$(GREEN)~~~~##~##~~##~##~~##~##~~##~##~~~~~~~~~##~~~~~##"
	@echo "$(GREEN)~####~~~####~~~####~~~####~~#####~~~####~~~####~~~~###"
	@echo "$(GREEN)______________________________________________________"
$(NAME): $(MLX_LIB) $(OBJ)
	
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(MLX_LIB) -o $(NAME) $(LINKS) $(FRAMEWORKS)
	@$(LOAD_DYLIB)

$(MLX_LIB):
	@echo "COMPILING MLX"
	@$(MAKE) -C $(MLX_PATH)/

$(OBJDIR)/%.o: $(DIRSRC)/%.c $(WAIT) $(HEADERS) $(MLX_LIB) 
	@mkdir -p $(OBJ_PATHS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 
$(WAIT):
	@echo "$(GREEN)____________________________________________________________________"
	@echo "$(GREEN)~####~~~####~~##~~~#~#####~~######~##~~~~~######~##~~##~~####~~~~###"
	@echo "$(GREEN)##~~##~##~~##~###~##~##~~##~~~##~~~##~~~~~~~##~~~###~##~##~~~~~~~###"
	@echo "$(GREEN)##~~~~~##~~##~##~#~#~#####~~~~##~~~##~~~~~~~##~~~##~###~##~###~~~###"
	@echo "$(GREEN)##~~##~##~~##~##~~~#~##~~~~~~~##~~~##~~~~~~~##~~~##~~##~##~~##"
	@echo "$(GREEN)~####~~~####~~##~~~#~##~~~~~######~######~######~##~~##~~####~~~~###"
	@echo "$(GREEN)____________________________________________________________________"
clean:
	@echo "$(RED)_______________________________________________________________________"
	@echo "$(RED)#####~~#####~~##~~~~~#####~~######~#####  ~####~~#####~~######~~~~~~###"
	@echo "$(RED)##~~##~##~~~~~##~~~~~##~~~~~~~##~~~##     ##~~##~##~~##~~~~~##~~~~~~###"
	@echo "$(RED)##~~##~####~~~##~~~~~####~~~~~##~~~####   ##~~##~#####~~~~~~##~~~~~~###"
	@echo "$(RED)##~~##~##~~~~~##~~~~~##~~~~~~~##~~~##     ##~~##~##~~##~##~~##"
	@echo "$(RED)#####~~#####~~######~#####~~~~##~~~#####  ~####~~#####~~~####~~~~~~~###"
	@echo "$(RED)_______________________________________________________________________"
	@$(RM) $(OBJ)

fclean:
	@echo "$(RED)____________________________________________________________________"
	@echo "$(RED)#####~~#####~~##~~~~~#####~~######~#####  ~####~~##~~~~~##~~~~~~~###"
	@echo "$(RED)##~~##~##~~~~~##~~~~~##~~~~~~~##~~~##     ##~~##~##~~~~~##~~~~~~~###"
	@echo "$(RED)##~~##~####~~~##~~~~~####~~~~~##~~~####   ######~##~~~~~##~~~~~~~###"
	@echo "$(RED)##~~##~##~~~~~##~~~~~##~~~~~~~##~~~##     ##~~##~##~~~~~##"
	@echo "$(RED)#####~~#####~~######~#####~~~~##~~~#####  ##~~##~######~######~~~###"
	@echo "$(RED)____________________________________________________________________"
	@$(RM) $(NAME) $(OBJ)

re: fclean all	

.PHONY: all re clean fclean
