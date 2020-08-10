/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 12:33:06 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 11:45:56 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			find_vis_or_dumps(int ac, char **av, t_virt *v, int i)
{
	if (ft_strequ(av[i], "-vis"))
	{
		if (v->vis)
			exit(ft_printf("Bag arguments!\nRun ./corewar for help\n"));
		v->vis = true;
		return (1);
	}
	if (((ft_strequ(av[i], "-dump") || ft_strequ(av[i], "-d")) && ((v->dump
		+ v->d) == -2)) && (i + 1 < ac) && ft_is_positive_number(av[i + 1]))
	{
		if (ft_strequ(av[i], "-dump"))
			v->dump = ft_atoi(av[i + 1]);
		else
			v->d = ft_atoi(av[i + 1]);
		if (v->d + v->dump > -2)
			return (2);
	}
	return (0);
}

void		check_program_args(int ac, char **av, t_virt *v, int i)
{
	if (ac < 2)
	{
		ft_printf("Use: ./corewar with arguments: {-vis or -dump (int) ");
		ft_printf("or -d (int)} {-n (int)} (Player_name).cor\n");
		ft_printf("\t-vis run visualization\n\t-d (int) or -dump (int) ");
		ft_printf("stop corwar after (int) cycles and print map\n\t-n");
		ft_printf(" (int) change start name for next player\n");
		exit(0);
	}
	init_start_params(v);
	while (i < ac)
	{
		v->temp = i;
		i += find_vis_or_dumps(ac, av, v, i);
		if (v->temp == i)
		{
			i += find_player(ac, av, v, i);
			if (v->temp == i)
				exit(ft_printf("Bag arguments!\nRun ./corewar for help\n"));
		}
	}
}
