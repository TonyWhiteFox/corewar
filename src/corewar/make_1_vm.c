/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_1_vm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:25:11 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 11:51:30 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		make_sti(t_virt *v, t_serf *serf, t_option *option, int save_var)
{
	save_var = option->variable[0];
	write_reg(serf, option, 0);
	if ((option->var_type[2] == REG || option->var_type[2] == DIR)
			&& option->var_type[0] == REG)
		change_map(v, serf, serf->reg[save_var], serf->pos
				+ (option->variable[1] + option->variable[2]) % IDX_MOD);
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		make_st(t_virt *v, t_serf *serf, t_option *option)
{
	if (option->var_type[0] == REG && option->var_type[1] == REG)
		serf->reg[option->variable[1]] = serf->reg[option->variable[0]];
	if (option->var_type[0] == REG && option->var_type[1] == IND)
		change_map(v, serf, serf->reg[option->variable[0]],
				serf->pos + option->variable[1] % IDX_MOD);
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		make_aff(t_serf *serf, t_option *option)
{
	if (option->var_type[0] == REG)
	{
		write_reg(serf, option, 0);
		if (AFF_OP)
			ft_putchar((char)option->variable[0]);
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		make_ldi(t_virt *v, t_serf *serf, t_option *option, int save_var)
{
	save_var = option->variable[2];
	write_reg(serf, option, 0);
	if ((option->var_type[1] == REG || option->var_type[1] == DIR)
		&& option->var_type[2] == REG)
	{
		if (serf->spell == LDI)
			serf->reg[save_var] = find_num(v, serf,
				(option->variable[0] + option->variable[1]) % IDX_MOD, 4);
		else if (serf->spell == LLDI)
		{
			serf->reg[save_var] = find_num(v, serf,
				option->variable[0] + option->variable[1], 4);
			set_jump(serf, serf->reg[save_var]);
		}
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}
