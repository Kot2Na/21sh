#include "internal_utilities.h"

int	iu_test(char **cmd)
{
	int	param_num;
	int res;

	param_num = 0;
	while (cmd[param_num])
		param_num++;
	if (param_num > 4)
	{
		ft_putendl("usage: test <operand> file || test file1 <operand> file2");
		return (EXIT_FAILURE);
	}
	res = iu_test_cmd_hadler(param_num, cmd);
	return (res);
}

int	iu_test_cmd_hadler(int param_num, char **cmd)
{
	if (param_num == 1)
		return (EXIT_FAILURE);
	if (param_num == 2)
	{
		return (iu_test_non_operand(cmd));
	}
	if (param_num == 3)
	{
		if (ft_strequ(cmd[1], "!"))
			return (!iu_test_non_operand(cmd + 1));
		else
			return (iu_test_operand_n_file(cmd));
	}
	if (param_num == 4)
	{
		if (ft_strequ(cmd[1], "!"))
			return (!iu_test_operand_n_file(cmd + 1));
		else
			return (iu_test_file_operand_file(cmd));
		
	}
	return (EXIT_FAILURE);
}

int	iu_test_non_operand(char **cmd)
{
	if (cmd[1] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	iu_test_operand_n_file(char **cmd)
{
	t_test_builtin	formula;

	if ((formula = iu_test_get_formula_single_operand(cmd[1])))
		return (formula(cmd));
	return (EXIT_FAILURE);
}

int	iu_test_file_operand_file(char **cmd)
{
	t_test_builtin	formula;

	if ((formula = iu_test_get_formula_compare_operand(cmd[2])))
		return (formula(cmd));
	return (EXIT_FAILURE);
}

t_test_builtin iu_test_get_formula_compare_operand(char *str)
{
	unsigned int						index;
	t_test_builtin						res;
	static const t_test_formula_discr	compare_operand_formula_list[] = 
	{
		{&iu_test_equality, "="},
		{&iu_test_not_equality, "!="},
		{&iu_test_eq, "-eq"},
		{&iu_test_ge, "-ge"},
		{&iu_test_gt, "-gt"},
		{&iu_test_lt, "-lt"},
		{&iu_test_ne, "-ne"},
		{&iu_test_ef, "-ef"},
		{&iu_test_nt, "-nt"},
		{&iu_test_ot, "-ot"}
	};
	index = 0;
	res = NULL;
	while (index < sizeof(compare_operand_formula_list) / sizeof(*compare_operand_formula_list))
	{
		if (ft_strequ(str, compare_operand_formula_list[index].name))
			res = compare_operand_formula_list[index].formula;
		index++;
	}
	return(res);
}

t_test_builtin	iu_test_get_formula_single_operand(char *str)
{
	unsigned int						index;
	t_test_builtin						res;
	static const t_test_formula_discr	single_operand_formula_list[] = 
	{
		{&iu_test_b, "-b"},
		{&iu_test_c, "-c"},
		{&iu_test_d, "-d"},
		{&iu_test_e, "-e"},
		{&iu_test_f, "-f"},
		{&iu_test_g, "-g"},
		{&iu_test_cap_g, "-G"},
		{&iu_test_h_and_cap_l, "-h"},
		{&iu_test_h_and_cap_l, "-L"},
		{&iu_test_k, "-k"},
		{&iu_test_cap_o, "-O"},
		{&iu_test_p, "-p"},
		{&iu_test_r, "-r"},
		{&iu_test_s, "-s"},
		{&iu_test_t, "-t"},
		{&iu_test_u, "-u"},
		{&iu_test_w, "-w"},
		{&iu_test_x, "-x"}
	};

	index = 0;
	res = NULL;
	while (index < sizeof(single_operand_formula_list) / sizeof(*single_operand_formula_list))
	{
		if (ft_strequ(str, single_operand_formula_list[index].name))
			res = single_operand_formula_list[index].formula;
		index++;
	}
	return(res);
}
