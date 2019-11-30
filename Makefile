# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atyrode <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/05 23:55:33 by atyrode           #+#    #+#              #
#    Updated: 2019/09/16 02:46:35 by atyrode          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###################################
#          Color codes            #
###################################

OFF    		= "\x1b[0m"
GREEN    	= "\x1b[32;01m"
RED 		= "\x1b[31;01m"
YELLOW		= "\x1b[33;01m"

###################################
#        Generic flags            #
###################################

PROJECT     = filler
NAME	    = atyrode.filler

LIBFT_PATH  = libft/
OBJ_PATH    = obj/
SRCS_PATH   = srcs/
INCL_PATH   = incl/

FLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I ./$(INCL_PATH) -I $(LIBFT_PATH)includes

SRCS_FILES  =  main.c \
				parser.c \
				solver.c \
				algorithm.c \
				utils.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_FILES))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_FILES:.c=.o))

###################################
#             Rules               #
###################################

all: $(NAME)

$(NAME): $(OBJ)

	@make -C $(LIBFT_PATH)
	@echo Libft $(GREEN)linked$(OFF) to the project.
	@gcc $(FLAGS) $(OBJ) $(INCLUDES) -L $(LIBFT_PATH) -lft -o $(NAME)
	@echo Compilation of $(NAME) $(GREEN)done.$(OFF)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c

	@echo Compilation of $(notdir $<) $(GREEN)done.$(OFF)
	@mkdir -p `dirname $@`
	@gcc -c -g $(FLAGS) $(INCLUDES) $< -o $@

clean:

	@make -C $(LIBFT_PATH) fclean
	@/bin/rm -rf $(OBJ_PATH)
	@echo $(YELLOW)Cleaning$(OFF) $(PROJECT) object files.

fclean: clean

	@/bin/rm -rf $(NAME)
	@echo $(YELLOW)Cleaning$(OFF) executable: $(NAME).

re: fclean all

###################################
#       	Utilities             #
###################################

.PHONY: all clean fclean re

debug_clean:
	rm -rf a.out.dSYM

debug: CFLAGS := -g
debug: re

test: all
	@assets/filler_vm -f assets/maps/map01 -p1 ./atyrode.filler -p2 assets/players/superjeannot.filler -s 2994

test_python: all
	@python3 ../filler_vm_py/filler_vm.py -f assets/maps/map00 -p1 ./atyrode.filler -p2 assets/players/abanlin.filler -s 404

# This allows us to print any variable of the makefile
print-%  : ; @echo $* = $($*)
