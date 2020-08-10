/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main_vm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 21:04:13 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 13:22:31 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		only_one_will_be_left_alive(t_virt *v)
{
	v->player_num_last_say_life = v->total_gamers;
	if (v->vis)
		let_the_show_begin(v);
	else
		hide_show_run(v);
}

int			main(int ac, char **av)
{
	t_virt	*v;

	if (!(v = (t_virt *)malloc(sizeof(t_virt))))
	{
		ft_putendl("Memory not available!!");
		exit(0);
	}
	check_program_args(ac, av, v, 1);
	send_gamers(v);
	if (v->vis)
		heat_visual(v);
	only_one_will_be_left_alive(v);
	winner_is(v, v->gamer);
	exit(0);
}
