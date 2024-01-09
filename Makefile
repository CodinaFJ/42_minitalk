#########################################################################################\
#		-MAKEFILE-																		#\
#		PROJECT: minitalk																#\
#########################################################################################

SERVER = $(BIN_DIR)server.out
CLIENT = $(BIN_DIR)client.out
NAME = minitalk

CC	= cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_PATH = ./lib/libft/
FT_PRINTF_PATH = ./lib/ft_printf/
LIBFT = $(LIBFT_PATH)/bin/libft.a
FT_PRINTF = $(FT_PRINTF_PATH)libftprintf.a
AR = ar rcs
RM = rm -rf

########################################################################################\
Directories
########################################################################################

HDR_DIR	=	./lib/
BIN_DIR = 	./bin/
OBJ_DIR =	$(BIN_DIR)obj/
SRC_DIR_SERVER	=	./src/server/
SRC_DIR_CLIENT	=	./src/client/

########################################################################################\
Sources & objects - Server
########################################################################################

FILES_SERVER	=	server			\
					server_signal	\
					server_data

SRCS_SERVER	=	$(addsuffix .c, $(FILES_SERVER))
OBJS_SERVER	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES_SERVER)))

########################################################################################\
Sources & objects - Client
########################################################################################

FILES_CLIENT	=	client			\
					client_comms	\
					client_ack		\
					client_data		\
					matrix			\
					to_binary

SRCS_CLIENT	=	$(addsuffix .c, $(FILES_CLIENT))
OBJS_CLIENT	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES_CLIENT)))

########################################################################################\
Colors
########################################################################################

DEF_COLOR = \033[0;39m
CUT = 		\033[K
R = 		\033[31;1m
G = 		\033[32;1m
Y = 		\033[33;1m
B = 		\033[34;1m
P = 		\033[35;1m
GR = 		\033[30;1m
END = 		\033[0m

########################################################################################\
Rules
########################################################################################

all: libft ft_printf server client

server: libft ft_printf $(SERVER)

client: libft ft_printf $(CLIENT)

libft: $(LIBFT)

ft_printf: $(FT_PRINTF)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(FT_PRINTF):
	@make -C $(FT_PRINTF_PATH)

$(SERVER): $(OBJS_SERVER)
	@$(CC) $(OBJS_SERVER) $(LIBFT) $(FT_PRINTF) -o $(SERVER)
	@echo "\n$(G)[$(NAME)] Server compilation finished!$(DEF_COLOR)-> $(SERVER)\n"

$(CLIENT): $(OBJS_CLIENT)
	@$(CC) $(OBJS_CLIENT) $(LIBFT) $(FT_PRINTF) -o $(CLIENT)
	@echo "\n$(G)[$(NAME)] Client compilation finished!$(DEF_COLOR)-> $(CLIENT)\n"

$(OBJ_DIR)%.o:$(SRC_DIR_SERVER)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(Y)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o:$(SRC_DIR_CLIENT)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(Y)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)
	@echo "$(R)[$(NAME)] Removed all $(OBJ_DIR)*.o$(DEF_COLOR)"

fclean: clean
	@$(RM) $(SERVER) $(CLIENT)
	@echo "$(R)[$(NAME)] Removed $(SERVER) and $(CLIENT)$(DEF_COLOR)\n"

clean_libs:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(FT_PRINTF_PATH)

fclean_libs:
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(FT_PRINTF_PATH)

re: fclean all

norminette:
	norminette $(SRC_DIR_CLIENT)
	norminette $(SRC_DIR_SERVER)

.PHONY: all bonus clean fclean re server client norminette