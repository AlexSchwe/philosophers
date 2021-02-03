# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 20:26:32 by user42            #+#    #+#              #
#    Updated: 2020/11/08 20:26:45 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

SRCDIR =	srcs
OBJDIR =	.obj
INCLUDES =	-I Includes/

SRCS = 	main.c \
		utils.c \
		utils_2.c \
		action.c \
		end_program.c \
		starting.c

OBJS =	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DPDCS =	$(OBJS:.o=.d)

CFLAGS = -Wall -Wextra -Werror -pthread -g3 -fsanitize=address -fno-omit-frame-pointer

opti:
	@make -j all

all :
	@make $(NAME)

-include $(DPDCS)

$(NAME) : $(OBJS)
	@printf "[$(NAME)] "
	gcc $(CFLAGS) -o $(NAME) ${OBJS}
	@echo Compiled $(NAME) successfully !

$(OBJDIR)/%.o : $(SRCDIR)/%.c | $(OBJDIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR) :
	@mkdir -p .obj

clean :
	@rm -rf $(OBJDIR)

fclean : clean
	@rm -rf $(NAME)

re :
	@make fclean
	@make opti