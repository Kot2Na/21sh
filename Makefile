# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 15:27:16 by tvanessa          #+#    #+#              #
#    Updated: 2020/12/15 02:53:34 by tvanessa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

debug := 1

Fsrcs := fsrcs
FH := fhdr
FHD := fhdir
FD := fdirs
SS := $(shell cat $(Fsrcs))
CHEADERS := $(shell cat $(FH))
SDIRS := $(shell cat $(FD))
OBJD := obj
SRCD := srcs
OBJS := $(notdir $(SS:.c=.o))
OBJSD := $(OBJS)

CC := clang
GCF := -g3 -Wall -Wextra -Werror
NAME := 42sh
LIBFT := lib/libft
LIBFTA := $(LIBFT)/libft.a
CFLAGS := -Wall -Wextra -Werror

# Compiller selection
ifdef gcc
CC := gcc
else ifdef clang
CC := clang
else ifdef cc
CC := $(cc)
endif

# Debug mode
ifeq ($(debug), 1)
CFLAGS := $(GCF)
endif
# CFLAGS += -I . -I $(LIBFT)/include -I include/
CFLAGS += $(addprefix -I, $(LIBFT))
CFLAGS += $(addprefix -I, $(shell cat $(FHD)))
CFS := -L $(LIBFT)/ -lft -ltermcap

vpath %.c $(SDIRS)
vpath %.o $(OBJD)
vpath %.h $(notdir $(CHEADERS))

all: $(LIBFT) $(OBJD) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(addprefix $(OBJD)/, $(OBJS)) $(CFS)
	@echo "\033[32mBinary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(OBJS):%.o:%.c $(CHEADERS)
	$(CC) $(CFLAGS) -c $< -o obj/$@
	@echo "\033[34m\033[1mCompilation of \033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

$(LIBFT):
	@echo "\033[34m\033[1mCompilation of \033[0m\033[36mLibft\033[1m"
	@make -C $(LIBFT) debug=$(debug)
	@echo "\033[34m done.\033[0m"

$(OBJD):
	@$(shell mkdir $(OBJD))

clean:
	@make -C $(LIBFT) clean
	@/bin/rm -fr $(OBJD)
	@echo "\033[31mObjects files removed.\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[31mBinary \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.SILENT: all $(NAME) $(OBJSD) $(LIBFT) clean fclean re

.PHONY: clean $(LIBFT) all
