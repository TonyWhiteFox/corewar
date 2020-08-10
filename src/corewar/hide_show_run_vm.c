/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide_show_run_vm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:13:32 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 12:33:47 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		spell_book_with_vars(t_virt *v, t_serf *serf, t_option *option)
{
	if (serf->spell == LD || serf->spell == LLD)
		make_ld(serf, option);
	else if (serf->spell == ADD || serf->spell == SUB)
		make_add_sub(serf, option);
	else if (serf->spell == AND || serf->spell == OR || serf->spell == XOR)
		make_and_or_xor(serf, option, 0);
	else if (serf->spell == ST)
		make_st(v, serf, option);
	else if (serf->spell == STI)
		make_sti(v, serf, option, 0);
	else if (serf->spell == AFF)
		make_aff(serf, option);
	else if (serf->spell == LDI || serf->spell == LLDI)
		make_ldi(v, serf, option, 0);
}

void		spell_book(t_virt *v, t_serf *serf)
{
	if (serf->spell == LIVE)
		make_live(v, serf, 0, 0);
	else if (serf->spell == ZJMP)
		make_zjmp(v, serf, 0);
	else if (serf->spell == FORK || serf->spell == LFORK)
		make_fork(v, serf, 0, 0);
	else if (clean_fill_check_option(v, serf, 0))
		spell_book_with_vars(v, serf, v->option);
}

void		multi_cust(t_virt *v, t_serf *serf)
{
	if (serf->left_to_cust == -1)
	{
		serf->pos = calс_new_pos(serf->pos + 1);
		serf->left_to_cust = 0;
		serf->spell = 0;
	}
	else
	{
		serf->left_to_cust--;
		if (serf->left_to_cust == 0)
			spell_book(v, serf);
	}
}

void		dump_map(t_virt *v, int i, int dump)
{
	if (v->dump > -1)
		dump = 32;
	else
		dump = 64;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if (i && i % dump == 0)
			ft_printf("\n%6.4#x : ", i);
		ft_printf("%.2x ", v->map[i]);
		++i;
	}
	ft_printf("\n");
	if (!v->vis)
		exit(0);
}

void		hide_show_run(t_virt *v)
{
	while (v->serf)
	{
		v->total_cycles++;
		v->cycles++;
		make_a_move(v, v->serf);
		if (v->cycles == v->cycles_before_die || v->cycles_before_die <= 0)
			extermination_serfs(v);
		if (v->serf && (v->dump == v->total_cycles || v->dump == 0 ||
				v->d == v->total_cycles || v->d == 0))
			dump_map(v, 0, 0);
	}
}
