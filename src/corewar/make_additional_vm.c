/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_additional_vm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:28:03 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 11:49:42 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		write_reg(t_serf *serf, t_option *option, int i)
{
	while (i < 3)
	{
		if (option->var_type[i] == REG)
			option->variable[i] = serf->reg[option->variable[i]];
		i++;
	}
}

void		fill_vars(t_virt *v, t_serf *serf, t_option *o, int i)
{
	if (o->var_type[0])
		o->variable[0] = find_num(v, serf, 2, o->var_len[0]);
	if (o->var_type[1])
		o->variable[1] = find_num(v, serf, 2 + o->var_len[0], o->var_len[1]);
	if (o->var_type[2])
		o->variable[2] = find_num(v, serf, 2 + o->var_len[0] + o->var_len[1],
			o->var_len[2]);
	while (serf->spell != ST && i < 3)
	{
		if (o->var_type[i] == IND)
		{
			if (serf->spell == LLD)
				o->variable[i] = find_num(v, serf, o->variable[i],
											LLD_READ_SIZE);
			else
				o->variable[i] = find_num(v, serf, o->variable[i] % IDX_MOD, 4);
		}
		i++;
	}
}

bool		clean_fill_check_option(t_virt *v, t_serf *serf,
									unsigned char temp_ch)
{
	ft_bzero(v->option->var_type, sizeof(int) * 3);
	ft_bzero(v->option->var_len, sizeof(int) * 3);
	ft_bzero(v->option->variable, sizeof(int) * 3);
	v->option->total_len = 2;
	temp_ch = v->map[calс_new_pos(serf->pos + 1)];
	v->option->var_type[0] = (temp_ch / 128) + ((temp_ch % 128) / 64) * 2;
	v->option->var_type[1] = (temp_ch % 64) / 32 + ((temp_ch % 32) / 16) * 2;
	v->option->var_type[2] = (temp_ch % 16) / 8 + ((temp_ch % 8) / 4) * 2;
	calc_option_len(serf, v->option, 0);
	fill_vars(v, serf, v->option, 0);
	if (!(check_valid_reg(serf, v->option, 0) &&
			check_var_types(serf, v->option)))
	{
		serf->pos = calс_new_pos(serf->pos + v->option->total_len);
		return (false);
	}
	return (true);
}

void		change_map(t_virt *v, t_serf *serf, int reg, int copy_in_pos)
{
	int		i;
	char	*temp_ch;

	temp_ch = (char *)(&reg);
	i = 0;
	while (i < 4)
	{
		v->map[calс_new_pos(copy_in_pos + i)] = temp_ch[3 - i];
		v->log[calс_new_pos(copy_in_pos + i)] = serf->creater_no
							+ v->total_cycles * 10;
		i++;
	}
}
