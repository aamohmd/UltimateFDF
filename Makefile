# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamohame <aamohame@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 22:47:22 by aamohame          #+#    #+#              #
#    Updated: 2024/04/11 05:01:23 by aamohame         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 = fdf
CC			 = gcc
CFLAGS		 = -Wall -Werror -Wextra
RM			 = rm -f
MAKE		 = make

LIB			 = lib/
LIBFT_DIR	 = $(LIB)UltimateLibft/
LIBFT		 = $(LIBFT_DIR)libft.a

# Colors
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
YELLOW = \033[0;93m

SRCS		 = fdf.c lib/UltimateGNL/get_next_line.c lib/UltimateGNL/get_next_line_utils.c
OBJS		 = $(SRCS:.c=.o)
INCS		 = fdf.h 

all: makelibs
	@$(MAKE) -s $(NAME)

makelibs:
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -L $(LIBFT_DIR) $(OBJS) -o $(NAME) -lft
	@echo "$(GREEN)✨ FDF compiled!$(DEF_COLOR)"

%.o: %.c $(INCS)
	@echo "🍩 $(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(MAKE) clean -s -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -s -C $(LIBFT_DIR)

re:	fclean all

.PHONY:	all clean fclean re
