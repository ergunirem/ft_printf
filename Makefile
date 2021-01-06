# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: icikrikc <icikrikc@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/19 09:07:29 by ergunirem     #+#    #+#                  #
#    Updated: 2021/01/06 17:14:13 by icikrikc      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SOURCE_FILES =		ft_printf.c \
					struct_functions.c \
					handle_arguments.c \
					handle_types_other.c \
					handle_types_int.c \
					parse_flags.c \
					print_funcs.c

GREEN = \033[38;5;2m
NORMAL = \033[38;5;255m
RED = \033[38;5;1m
BLUE = \033[38;5;4m

OBJ_FILES = $(SOURCE_FILES:.c=.o)
HEADER_FILE = ft_printf.h
LIBRARY = libft/libft.a
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBRARY) $(OBJ_FILES)
	cp $< $@
	ar -rc $@ $(OBJ_FILES)

%.o: %.c $(HEADER_FILE)
	@echo "$(GREEN)Compiling:$(NORMAL)"
	$(CC) $(CFLAGS) -c $<

$(LIBRARY):
	make bonus -C libft

clean:
	@echo "$(RED)Removing all object files...$(NORMAL)"
	make clean -C libft
	rm -f $(OBJ_FILES)
	@echo "$(GREEN)Succesfully removed all object files!$(NORMAL)"

fclean: clean
	@echo "$(RED)Removing libftprintf.a...$(NORMAL)"
	rm -f $(LIBRARY)
	rm -f $(NAME)
	@echo "$(GREEN)Successfully removed libftprintf.a!$(NORMAL)"

re: fclean all

.PHONY: all clean fclean re
