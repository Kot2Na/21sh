# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/16 21:51:15 by student           #+#    #+#              #
#    Updated: 2020/12/23 08:22:20 by tvanessa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME						:=	42sh

SRC_MAIN					:=	main.c

SRC_INIT					:=	init.c\
									init_env.c\
									init_structs.c

SRC_INPUT					:=	input.c\
									input_getch.c\
									input_mode_term.c\
									input_init.c\
									input_cursor_pos.c\
									input_termcap.c\
									input_common.c\
									input_error.c\
									input_greeting.c\
									input_greet_init.c\
									input_process_key_press.c\
									input_refresh_screen.c\
									input_move_cursor.c\
									input_common_screen.c\
									input_key_tools.c\
									input_parse_page_keys.c\
									input_parse_keys_shift_words.c\
									input_copy_paste_cut.c\
									input_ctr_keys.c\
									input_additional_modes.c\
									input_quote.c\
									input_search_key_char.c\
									input_change_win.c\
									input_ctr_t.c\
									input_set_of_instr_for_getch.c\
									input_history.c\
									input_bonus_instr.c\
									input_wrapper_func.c\
									input_heredoc.c

SRC_IU						:=	iu_cd_home_dir.c\
									iu_cd.c\
									iu_echo.c\
									iu_getenv.c\
									iu_pwd.c\
									iu_setenv.c\
									iu_unsetenv.c\
									iu_init_var_env.c\
									operation_env.c\
									sh21_env.c\
									work_env.c\
									exit_with_code.c\
									iu_type.c\
									iu_get_flags.c\
									iu_get_posix_options.c

SRC_HIST					:=	history_init.c\
									history_fill_flist.c\
									history_find_history.c\
									history_move.c\
									history_del.c

SRC_PARSER					:=	parser.c\
									parser_list.c\
									parser_find_delimiter.c\
									parser_common.c\
									parser_args.c\
									parser_quotes.c\
									parser_skip_delimiter.c\
									pars_find_stream.c\
									pars_add_lst_stream.c\
									parser_find_flags_stream.c\
									parser_fill_point_args.c\
									parser_skipminus.c\
									pars_insert_tilda.c\
									pars_stream_in_lis.c\
									parse_write_prev.c\
									pars_write_next_stream.c\
									pars_write_amper_args_after_stream.c\
									parser_find_ampersand.c\
									parser_check_ampersand.c\
									parser_get_count_args_heredoc.c\
									parser_check_dollar.c\

SRC_EXEC					:=	check_choice.c\
									check_run.c\
									close_and_open_std.c\
									create_file.c\
									dup_fd_and_close.c\
									error_system.c\
									free_pars_list.c\
									free_pipe_list.c\
									new_or_open_file.c\
									new_pipe_list.c\
									redirect_stream.c\
									run_ampersant.c\
									run_exec.c\
									run_pipe.c\
									stream_and_file.c\
									stream_close_fd.c\
									stream_save_std.c\
									write_this_dir.c\
									check_cmd.c\
									cmd_false.c\
									cmd_true.c\
									run_cmd.c\
									exec_env.c\
									free_befor_exec.c\
									exec_dup_stream.c\
									signal_handler.c\
									exec_next_list.c\
									exec_fill_way_for_path.c\
									exec_redirect_heredoc.c\
									pars_dollar_env.c\
									pars_dollar_shift_args.c

SRCS						:=	$(SRC_MAIN)\
									$(SRC_INIT)\
									$(SRC_INPUT)\
									$(SRC_IU)\
									$(SRC_HIST)\
									$(SRC_PARSER)\
									$(SRC_EXEC)

OBJS						:=	$(SRCS:.c=.o)

DIR_SRC						:=	./src/
DIR_INIT					:=	$(DIR_SRC)init/
DIR_INPUT					:=	$(DIR_SRC)input/

DIRS_INPUT					:=	$(DIR_INPUT)\
									$(DIR_INPUT)additional_modes/\
									$(DIR_INPUT)bonus/\
									$(DIR_INPUT)greeting/\
									$(DIR_INPUT)screen/\
									$(DIR_INPUT)termcap/\
									$(DIR_INPUT)heredoc\

DIR_IU						:=	$(DIR_SRC)internal_utilities/

DIR_ENV						:=	$(DIR_IU)iu_env/

DIR_HIST					:=	$(DIR_SRC)history/
DIR_PARSER					:=	$(DIR_SRC)parser/

DIR_EXEC					:=	$(DIR_SRC)exec/

DIRS_EXEC					:=	$(DIR_EXEC)\
									$(DIR_EXEC)cmd/\

DIRS_SRC					:=	$(DIR_SRC)\
									$(DIR_INIT)\
									$(DIRS_INPUT)\
									$(DIR_IU)\
									$(DIR_ENV)\
									$(DIR_HIST)\
									$(DIR_PARSER)\
									$(DIRS_EXEC)\


MAIN_HEADERS				:=	sh.h\
									gl.h\
									history.h\
									internal_utilities.h\
									sh_bonus.h\
									sh_init.h\
									sh_limits.h\
									sh_struct.h

INPUT_HEADERS				:=	input_error.h\
									input_greeting.h\
									input_init.h\
									input_macros.h\
									input_parse_key.h\
									input_termcap.h

PARSER_HEADERS				:=	parser.h

EXEC_HEADERS				:=	exec.h

HEADERS						:=	$(MAIN_HEADERS)\
									$(INPUT_HEADERS)\
									$(PARSER_HEADERS)\
									$(EXEC_HEADERS)

DIR_INCLUDE					:=	./include/
DIR_INCLUDE_INPUT			:=	$(DIR_INCLUDE)input/
DIR_INCLUDE_PARSER			:=	$(DIR_INCLUDE)parser/

DIRS_INCLUDE				:=	$(DIR_INCLUDE)\
									$(DIR_INCLUDE_INPUT)\
									$(DIR_INCLUDE_PARSER)


LIBFT						:=	libft.a
DIR_LIBFT					:=	./lib/libft/
DIR_LIBFT_INCLUDE			:=	$(DIR_LIBFT)include/


CFLAGS						:=	-g -Wall -Wextra -Werror
DIR_OBJ						:=	./obj/
OBJS_WITH_PATH				:=	$(addprefix $(DIR_OBJ), $(OBJS))
PATH_HEADERS				:=	$(addprefix -I , $(DIRS_INCLUDE) $(DIR_LIBFT_INCLUDE))
PATH_LIBFT					:=	$(addprefix $(DIR_LIBFT), $(LIBFT))


REMOVE						:=	rm -rf
MAKE_LIBFT					:=	make -C $(DIR_LIBFT)
MAKE_CLEAN_LIBFT			:=	make -C $(DIR_LIBFT) clean
MAKE_FCLEAN_LIBFT			:=	make -C $(DIR_LIBFT) fclean
CC							:=	clang

vpath	%.c	$(DIRS_SRC)
vpath	%.o	$(DIR_OBJ)
vpath	%.h	$(DIRS_INCLUDE)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS_WITH_PATH) $(PATH_LIBFT) -o $@ -ltermcap
	@echo "\033[32mBinary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(OBJS):%.o:%.c $(HEADERS) | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $(DIR_OBJ)$@ $(PATH_HEADERS)
	@echo "\033[34m\033[1mCompilation of \033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

$(LIBFT):
	$(MAKE_LIBFT)

$(DIR_OBJ):
	mkdir -p $@

clean:
	$(REMOVE) $(OBJS_WITH_PATH)
	$(REMOVE) $(DIR_OBJ)
	$(MAKE_CLEAN_LIBFT)
	@echo "\033[31mObjects files removed.\033[0m"

fclean: clean
	$(REMOVE) $(NAME)
	$(MAKE_FCLEAN_LIBFT)
	@echo "\033[31mBinary \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

echo:
	echo $(DIRS_EXEC)

.SILENT: all $(NAME) $(OBJS) $(LIBFT) $(DIR_OBJ) clean fclean re
