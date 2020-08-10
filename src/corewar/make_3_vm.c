/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_3_vm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:30:01 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 11:58:03 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			make_live(t_virt *v, t_serf *serf, int i, int t_dir)
{
	char		dir[4];

	while (i < 4)
	{
		dir[3 - i] = v->map[calс_new_pos(serf->pos + 1 + i)];
		i++;
	}
	t_dir = *((int *)dir);
	v->life_in_die_cycle++;
	serf->last_live_cycle = v->total_cycles;
	if (t_dir < 0 && (ft_abs(t_dir) <= v->total_gamers))
	{
		v->player_num_last_say_life = ft_abs(t_dir);
		v->live_log[serf->pos] = v->total_cycles * 10 +
								v->player_num_last_say_life;
	}
	serf->spell = 0;
	serf->pos = calс_new_pos(serf->pos + 4 + 1);
}

void			make_zjmp(t_virt *v, t_serf *serf, int t_dir)
{
	t_dir = find_num(v, serf, 1, 2);
	if (serf->jump)
		serf->pos = calс_new_pos(serf->pos + t_dir % IDX_MOD);
	else
		serf->pos = calс_new_pos(serf->pos + 3);
	serf->spell = 0;
}

void			make_fork(t_virt *v, t_serf *serf, int i, int dir)
{
	dir = find_num(v, serf, 1, 2);
	if (serf->spell == FORK)
		dir %= IDX_MOD;
	create_serf(v, NULL, 0);
	v->serf->pos = calс_new_pos(serf->pos + dir);
	v->serf->last_live_cycle = serf->last_live_cycle;
	while (i < 16)
	{
		v->serf->reg[i] = serf->reg[i];
		i++;
	}
	v->last_serf_id++;
	v->serf->id = v->last_serf_id;
	v->serf->jump = serf->jump;
	v->serf->creater_no = serf->creater_no;
	serf->pos = calс_new_pos(serf->pos + 3);
	serf->spell = 0;
}
