/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   let_the_show_begin_vm.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:19:41 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 15:02:55 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		start_fight_vis2(t_virt *v, int size_mem, int player_max)
{
	if (v->mlx->stop)
	{
		send_argument_to_cl(v, v->opencl, 0);
		return ;
	}
	size_mem = MEM_SIZE;
	player_max = MAX_PLAYERS;
	ft_bzero(v->have_serf, size_mem * sizeof(bool));
	ft_bzero(v->serfs_live, (player_max + 1) * sizeof(cl_int));
	v->total_cycles++;
	v->cycles++;
	make_a_move(v, v->serf);
	if ((v->cycles == v->cycles_before_die) || (v->cycles_before_die <= 0))
		extermination_serfs(v);
	if (v->serf && (v->dump == v->total_cycles || v->dump == 0 ||
			v->d == v->total_cycles || v->d == 0))
		dump_map(v, 0, 0);
	if (v->total_cycles % v->mlx->cycle_per_frame == 0)
		send_argument_to_cl(v, v->opencl, 0);
}

int			start_fight_vis(t_virt *v)
{
	if (v->serf)
	{
		start_fight_vis2(v, 0, 0);
		usleep(v->mlx->sleep_after_frame);
	}
	else
	{
		if (v->show_winner)
		{
			winner_is(v, v->gamer);
			v->show_winner = false;
		}
		send_argument_to_cl(v, v->opencl, 0);
	}
	return (0);
}

void		let_the_show_begin(t_virt *v)
{
	mlx_loop_hook(v->mlx->mlx_ptr, start_fight_vis, v);
	mlx_hook(v->mlx->win_ptr, 2, 2, key_press, v);
	mlx_hook(v->mlx->win_ptr, 17, 17, say_good_buy, v);
	mlx_loop(v->mlx->mlx_ptr);
}
