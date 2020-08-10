/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_2_vm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:26:45 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 11:57:27 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		make_ld(t_serf *serf, t_option *option)
{
	if (((option->var_type[0] == DIR) || (option->var_type[0] == IND))
			&& (option->var_type[1] == REG))
	{
		serf->reg[option->variable[1]] = option->variable[0];
		set_jump(serf, serf->reg[option->variable[1]]);
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		make_add_sub(t_serf *serf, t_option *option)
{
	if ((option->var_type[0] == REG) && (option->var_type[1] == REG) &&
			(option->var_type[2] == REG))
	{
		if (serf->spell == ADD)
			serf->reg[option->variable[2]] = serf->reg[option->variable[1]]
				+ serf->reg[option->variable[0]];
		else if (serf->spell == SUB)
			serf->reg[option->variable[2]] = serf->reg[option->variable[0]]
				- serf->reg[option->variable[1]];
		set_jump(serf, serf->reg[option->variable[2]]);
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}

void		make_and_or_xor(t_serf *serf, t_option *option, int save_var)
{
	save_var = option->variable[2];
	write_reg(serf, option, 0);
	if (option->var_type[2] == REG)
	{
		if (serf->spell == AND)
			serf->reg[save_var] = option->variable[0] & option->variable[1];
		else if (serf->spell == OR)
			serf->reg[save_var] = option->variable[0] | option->variable[1];
		else if (serf->spell == XOR)
			serf->reg[save_var] = option->variable[0] ^ option->variable[1];
		set_jump(serf, serf->reg[save_var]);
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + option->total_len);
}
