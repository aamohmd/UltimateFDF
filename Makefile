# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 22:47:22 by aamohame          #+#    #+#              #
#    Updated: 2024/05/04 19:44:09 by aamohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 = fdf
BONUS_NAME	 = fdf_bonus
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

SRCS		 = fdf.c fdf_utils.c map.c map_utils.c draw_map.c draw_map_utils.c bresenham.c lib/UltimateGNL/get_next_line.c lib/UltimateGNL/get_next_line_utils.c
BONUS_SRCS	 = bonus/fdf_bonus.c bonus/fdf_utils_bonus.c bonus/map_bonus.c bonus/map_utils_bonus.c bonus/draw_map_bonus.c bonus/draw_map_utils_bonus.c \
				bonus/fdf_movement_bonus.c bonus/bresenham_bonus.c bonus/crazy_bonus.c bonus/rotate_bonus.c lib/UltimateGNL/get_next_line.c lib/UltimateGNL/get_next_line_utils.c
OBJS		 = $(SRCS:.c=.o)
BONUS_OBJS	 = $(BONUS_SRCS:.c=.o)
INCS		 = inc/fdf.h inc/define.h inc/map.h
INCS_BONUS	 = inc/fdf_bonus.h inc/define_bonus.h inc/map_bonus.h

all: makelibs
	@$(MAKE) -s $(NAME)
	@$(MAKE) -s $(MLX_DIR)

makelibs:
	@$(MAKE) -s -C $(LIBFT_DIR)

bonus: makelibs
	@$(MAKE) -s $(BONUS_NAME)

$(BONUS_NAME) : $(BONUS_OBJS) $(INCS_BONUS)
	@$(CC) $(CFLAGS) -L $(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm $(BONUS_OBJS) -o $(BONUS_NAME) -framework OpenGL -framework AppKit
	@echo "$(GREEN)✨ FDF bonus compiled!$(DEF_COLOR)"

$(NAME): $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) -L $(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lm $(OBJS) -o $(NAME) -framework OpenGL -framework AppKit
	@echo "$(GREEN)✨ FDF compiled!$(DEF_COLOR)"

%.o: %.c
	@echo "🍩 $(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW) FDF Objects Deleted!"
	@$(RM) $(BONUS_OBJS)
	@echo "$(YELLOW) FDF Bonus Objects Deleted!"
	@$(MAKE) clean -s -C $(LIBFT_DIR)
	@echo "$(YELLOW) Libft Objects Deleted!"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW) FDF Name Deleted!"
	@$(RM) $(BONUS_NAME)
	@echo "$(YELLOW) FDF bonus Name Deleted!"
	@$(MAKE) fclean -s -C $(LIBFT_DIR)
	@echo "$(YELLOW) Libft Name Deleted!"
	@$(MAKE) clean -s -C $(MLX_DIR)
	@echo "$(YELLOW) minilibx Name Deleted!"

re:	fclean all

.PHONY:	all clean fclean re