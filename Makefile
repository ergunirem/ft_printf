# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: icikrikc <icikrikc@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/19 09:07:29 by ergunirem     #+#    #+#                  #
#    Updated: 2020/12/25 19:14:40 by icikrikc      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SOURCE_FILES =		ft_printf.c \
					struct_functions.c \


GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m

OBJ_FILES = $(SOURCE_FILES:.c=.o)
HEADER_FILES = ft_printf.h
LIB_PATH = ./libft
LIBRARY = ./libft/libft.a
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(MAKE) -C $(LIB_PATH)
	ar -rcs $@ $^ $(LIBRARY)
	ar -q $(LIBRARY) $(OBJ_FILES)
	cp $(LIBRARY) $(NAME)

%.o: %.c $(HEADER_FILES)
	@echo "$(GREEN)Compiling:$(NORMAL)"
	$(CC) -c $(CFLAGS) -o $@ $<

bonus: all

clean:
	@echo "$(RED)Removing all object files...$(NORMAL)"
	rm -f $(OBJ_FILES)
	@echo "$(GREEN)Succesfully removed all object files!$(NORMAL)"

fclean: clean
	@echo "$(RED)Removing libftprintf.a...$(NORMAL)"
	rm -f $(NAME)
	@echo "$(GREEN)Successfully removed libftprintf.a!$(NORMAL)"

re: fclean all

.PHONY: all clean fclean re
