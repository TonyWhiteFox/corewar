/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_arg_quantity_usage_vm.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:02:07 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 11:58:33 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			g_arg_quantity[17] = {NUM_ARG, 1, 2, 2,
	3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1};

void		calc_option_len(t_serf *serf, t_option *option, int i)
{
	while (i < 3)
	{
		option->var_len[i] = spell_dir_size(option->var_type[i], serf->spell);
		i++;
	}
	i = 0;
	while (i < g_arg_quantity[serf->spell])
	{
		option->total_len += spell_dir_size(option->var_type[i], serf->spell);
		i++;
	}
}

bool		check_valid_reg(t_serf *serf, t_option *option, int i)
{
	while (i < g_arg_quantity[serf->spell])
	{
		if (option->var_type[i] == REG)
		{
			option->variable[i]--;
			if (option->variable[i] < 0 || option->variable[i] > 15)
				return (false);
		}
		i++;
	}
	return (true);
}

bool		check_var_types(t_serf *serf, t_option *option)
{
	if (g_arg_quantity[serf->spell] == 1 && !option->var_type[0])
		return (false);
	if (g_arg_quantity[serf->spell] == 2 && (!option->var_type[0]
											|| !option->var_type[1]))
		return (false);
	if (g_arg_quantity[serf->spell] == 3 && (!option->var_type[0]
											|| !option->var_type[1]
			|| !option->var_type[2]))
		return (false);
	return (true);
}
