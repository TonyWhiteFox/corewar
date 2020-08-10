/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   winner_is_vm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 13:23:12 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 12:36:07 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		winner_is(t_virt *v, t_gamer *gamer)
{
	while (gamer->num != v->player_num_last_say_life)
		gamer = gamer->next;
	ft_printf("Contestant %i, \"%s\", has won !\n", gamer->num, gamer->name);
	v->is_end = TRUE;
}

int			say_good_buy(t_virt *v)
{
	exit(0);
	v += 0;
	return (0);
}

int			key_press(int key, t_virt *v)
{
	if (key == 53)
		say_good_buy(v);
	if (key == 24 && v->mlx->cycle_per_frame < 99)
	{
		if (v->mlx->sleep_after_frame == 0)
			v->mlx->cycle_per_frame += 1;
		else
			v->mlx->sleep_after_frame -= 1000;
	}
	if (key == 27)
	{
		if (v->mlx->cycle_per_frame > 1)
			v->mlx->cycle_per_frame -= 1;
		else
			v->mlx->sleep_after_frame += 1000;
	}
	if (key == 49)
		v->mlx->stop = !v->mlx->stop;
	return (0);
}
