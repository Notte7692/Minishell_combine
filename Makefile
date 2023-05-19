############## NAME #############

NAME		= minishell


############ SOURCES ###########

PATH_SRCS	= srcs/
VPATH		= $(PATH_SRCS)
SRCS 		= $(wildcard $(PATH_SRCS)*.c)


########## VARIABLES ############

PATH_OBJS	= objs/
OBJS		= $(patsubst $(PATH_SRCS)/%.c, $(PATH_OBJS)/%.o, $(SRCS))
RM			= @rm -f
CC			= @cc
CFLAGS		= -Wall -Wextra -Werror -lreadline

############ REGLES #############

all		:	$(NAME)


$(NAME)	:	$(OBJS)
			@echo "\033[0;31;5m __   __  ___   __    _  ___   _______  __   __  _______  ___      ___     \033[0m"
			@echo "\033[0;31;5m|  |_|  ||   | |  |  | ||   | |       ||  | |  ||       ||   |    |   |    \033[0m"
			@echo "\033[0;31;5m|       ||   | |   |_| ||   | |  _____||  |_|  ||    ___||   |    |   |    \033[0m"
			@echo "\033[0;31;5m|       ||   | |       ||   | | |_____ |       ||   |___ |   |    |   |    \033[0m"
			@echo "\033[0;31;5m|       ||   | |  _    ||   | |_____  ||       ||    ___||   |___ |   |___ \033[0m"
			@echo "\033[0;31;5m| ||_|| ||   | | | |   ||   |  _____| ||   _   ||   |___ |       ||       |\033[0m"
			@echo "\033[0;31;5m|_|   |_||___| |_|  |__||___| |_______||__| |__||_______||_______||_______|\033[0m"
			@echo "\033[0;33mCompilation...\033[0m"
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
			@echo "\033[0;32mCompilation : OK.\033[0m"

# $(OBJS)	: 	$(PATH_OBJS)/%.o: $(PATH_SRCS)/%.c include/philo.h
# 			@mkdir -p $(PATH_OBJS)
# 			@$(CC) $(CFLAGS) -c $< -o $@

clean	:
			@echo "\033[0;33mClean...\033[0m"
			@$(RM) -rf $(PATH_OBJS)
			@echo "\033[0;32mClean : OK.\033[0m"

fclean	:	clean
			$(RM) $(NAME)

re		:		fclean all

.PHONY	:		all clean fclean re