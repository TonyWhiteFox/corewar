/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start_params_vm.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 12:57:11 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 19:07:29 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		close_fd_send_error_close(t_virt *v, char *error_text)
{
	close(v->fd);
	exit(ft_printf("%s\n", error_text));
}

void		init_start_params2(t_virt *v)
{
	v->life_in_die_cycle = 0;
	v->cycles_before_die = CYCLE_TO_DIE;
	v->without_abbreviations = 0;
	v->hardcore = false;
	v->have_serf = (bool *)malloc(sizeof(bool) * MEM_SIZE);
	ft_bzero(v->have_serf, sizeof(bool) * MEM_SIZE);
	v->live_log = (cl_int *)malloc(sizeof(cl_int) * MEM_SIZE);
	ft_bzero(v->live_log, sizeof(cl_int) * MEM_SIZE);
	v->serfs_live = (cl_int *)malloc(sizeof(cl_int) * (MAX_PLAYERS + 1));
	if (!v->have_serf || !v->live_log || !v->serfs_live)
		memory_error();
	v->alter_total_cycles = 0;
	v->is_end = false;
	v->show_winner = true;
}

void		init_start_params(t_virt *v)
{
	v->d = -1;
	v->dump = -1;
	v->vis = false;
	v->total_gamers = 0;
	v->gamer = NULL;
	v->serf = NULL;
	v->map = (cl_uchar *)malloc(sizeof(cl_uchar) * MEM_SIZE);
	ft_bzero(v->map, sizeof(cl_uchar) * MEM_SIZE);
	v->log = (cl_uint *)malloc(sizeof(cl_uint) * MEM_SIZE);
	ft_bzero(v->log, sizeof(cl_uint) * MEM_SIZE);
	v->last_serf_id = 0;
	v->total_cycles = 0;
	v->cycles = 0;
	v->option = (t_option *)malloc(sizeof(t_option));
	ft_bzero(v->option, sizeof(t_option));
	v->option->var_type = (int *)malloc(sizeof(int) * 3);
	v->option->var_len = (int *)malloc(sizeof(int) * 3);
	v->option->variable = (int *)malloc(sizeof(int) * 3);
	if (!v->map || !v->log || !v->option || !v->option->var_type ||
		!v->option->var_len || !v->option->variable)
		memory_error();
	init_start_params2(v);
}

void		gamer_on_show(t_gamer *gamer)
{
	ft_printf("Introducing contestants...\n");
	while (gamer)
	{
		ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n",
				gamer->num, gamer->size, gamer->name, gamer->comment);
		gamer = gamer->next;
	}
}
