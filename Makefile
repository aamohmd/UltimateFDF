# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 22:47:22 by aamohame          #+#    #+#              #
#    Updated: 2024/04/18 11:58:12 by aamohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 = fdf
CC			 = gcc
CFLAGS		 = -Wall -Werror -Wextra
RM			 = rm -f

LIB			 = lib/
LIBFT_DIR	 = $(LIB)UltimateLibft/
LIBFT		 = $(LIBFT_DIR)libft.a
MLX_DIR		 = $(LIB)minilibx/
MLX			 = $(MLX_DIR)libmlx.a

# Colors
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
YELLOW = \033[0;93m

SRCS		 = fdf.c fdf_utils.c map.c map_utils.c draw_map.c lib/UltimateGNL/get_next_line.c lib/UltimateGNL/get_next_line_utils.c
OBJS		 = $(SRCS:.c=.o)
INCS		 = fdf.h 

all: makelibs
	@$(MAKE) -s $(NAME)

makelibs:
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(MAKE) -s -C $(MLX_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -L $(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm $(OBJS) -o $(NAME) -framework OpenGL -framework AppKit
	@echo "$(GREEN)✨ FDF compiled!$(DEF_COLOR)"

%.o: %.c $(INCS)
	@echo "🍩 $(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW) FDF Objects Deleted!"
	@$(MAKE) clean -s -C $(LIBFT_DIR)
	@echo "$(YELLOW) Libft Objects Deleted!"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW) FDF Name Deleted!"
	@$(MAKE) fclean -s -C $(LIBFT_DIR)
	@echo "$(YELLOW) Libft Name Deleted!"
	@$(MAKE) clean -s -C $(MLX_DIR)
	@echo "$(YELLOW) minilibx Name Deleted!"

re:	fclean all

.PHONY:	all clean fclean re
