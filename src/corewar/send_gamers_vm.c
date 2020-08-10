/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_gamers_vm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 14:46:40 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 19:08:23 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		memory_error(void)
{
	ft_putendl("Memory not availeable!");
	exit(0);
}

void		create_serf(t_virt *v, t_serf *surf, int i)
{
	if (!(surf = (t_serf *)malloc(sizeof(t_serf))))
		memory_error();
	ft_bzero(surf, sizeof(t_serf));
	surf->next = NULL;
	surf->last_live_cycle = 0;
	if (!(surf->reg = (int *)malloc(sizeof(int) * REG_NUMBER)))
		memory_error();
	while (i < 16)
	{
		surf->reg[i] = 0;
		i++;
	}
	if (!v->serf)
		v->serf = surf;
	else
	{
		surf->next = v->serf;
		v->serf = surf;
	}
}

void		get_start_pos_and_first_serf(t_virt *v, t_gamer *gamer,
										int start_pos, int i)
{
	while (gamer)
	{
		create_serf(v, NULL, 0);
		i = 0;
		while (i < gamer->size)
		{
			v->map[(start_pos + i) % MEM_SIZE] = gamer->code[i];
			v->log[(start_pos + i) % MEM_SIZE] = gamer->num;
			i++;
		}
		v->serf->reg[0] = -(gamer->num);
		v->serf->creater_no = gamer->num;
		v->serf->id = v->last_serf_id;
		v->last_serf_id += 1;
		v->serf->pos = start_pos;
		start_pos += MEM_SIZE / v->total_gamers;
		gamer = gamer->next;
	}
}

void		send_gamers(t_virt *v)
{
	if (v->total_gamers == 0)
		exit(ft_printf("No gamers!\nRun ./corewar for help\n"));
	if (v->gamer->num > v->total_gamers)
		exit(ft_printf("Maximal player num = sum players!\n"));
	gamer_buble_sorting(v, v->gamer, v->gamer, v->gamer);
	while (v->gamer->num < 0)
	{
		if (v->total_gamers == 1)
			v->gamer->num = 1;
		find_last_negative_player(v, v->gamer, NULL);
		gamer_buble_sorting(v, v->gamer, v->gamer, v->gamer);
	}
	gamer_on_show(v->gamer);
	get_start_pos_and_first_serf(v, v->gamer, 0, 0);
}
