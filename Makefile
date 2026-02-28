# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvachon <mvachon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/03 12:48:15 by mvachon           #+#    #+#              #
#    Updated: 2025/12/03 12:48:15 by mvachon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = hotrace
CXX = cc
CXXFLAGS = -Wall -Wextra -Werror

SRCS = main.c

HEADERS = 

OBJDIR = obj
OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(OBJDIR)/%.o: %.cpp $(HEADERS)
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "$(GREEN)✓ Compiled: $<$(RESET)"


clean:
	@rm -rf $(OBJDIR)
	@echo "$(RED)✗ Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✗ $(NAME) removed$(RESET)"

re: fclean all

run : all
	@./hotrace

.PHONY: all clean fclean re run
