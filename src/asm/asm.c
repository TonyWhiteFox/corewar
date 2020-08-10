/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainasm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:03:50 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/06/28 11:05:59 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <errno.h>

t_op			*get_op(char *name)
{
	size_t		i;

	i = 0;
	while (i < (sizeof(g_op_tab) / sizeof(t_op)))
	{
		if (!ft_strcmp(g_op_tab[i].name, name))
			return (&g_op_tab[i]);
		i++;
	}
	return (NULL);
}

static void		init_s(t_serv *s)
{
	errno = 0;
	s->fd = -1;
	s->fd_out = -1;
	s->flag = 0;
	s->i_line = 1;
	s->out_line = 0;
	s->filename = NULL;
	s->line = NULL;
	s->instr = NULL;
	s->last_instr = NULL;
	s->memguru = NULL;
	s->buff = ft_memguru(1, &s->memguru);
	s->header.magic = COREWAR_EXEC_MAGIC;
	s->header.prog_size = 0;
	ft_bzero(s->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(s->header.comment, COMMENT_LENGTH + 1);
	s->arg_labels = NULL;
	s->tokens = NULL;
}

static void		print_usage(void)
{
	ft_printf("Usage: ./asm <champion>.s [-a | -d | -i]\n");
	ft_printf("\t\t-a\tDump annotated program on standard output\n");
	ft_printf("\t\t-d\tDebug mode\n");
	ft_printf("\t\t-i\tPrint parsed instructions\n");
}

static t_serv	*read_file(char *file)
{
	size_t		len;
	t_serv		*s;

	if ((len = ft_strlen(file)) && file[len - 2] == '.' && file[len - 1] == 's')
	{
		if (!(s = malloc(sizeof(*s))))
			ft_error(ERR_MALLOC, s, ENOMEM);
		init_s(s);
		if (!(s->filename = ft_strdup(file)))
			ft_error(ERR_MALLOC, s, ENOMEM);
		ft_memguru_add(s->filename, &s->memguru);
		if ((s->fd = open(file, O_RDONLY)) == -1)
			ft_error(ERR_OPEN_FILE, s, errno);
		return (s);
	}
	write(2, "ERROR: Incorrect file name\n", 27);
	return (NULL);
}

int				main(int argc, char **argv)
{
	t_serv	*s;
	int		i;

	if (argc > 1 && (s = read_file(argv[1])))
	{
		i = 1;
		while (++i < argc)
		{
			if (!ft_strcmp(argv[i], "-a"))
				s->flag |= FLAG_DUMP;
			if (!ft_strcmp(argv[i], "-d"))
				s->flag |= FLAG_DEBUG;
			if (!ft_strcmp(argv[i], "-i"))
				s->flag |= FLAG_INSTR;
		}
		lexer(s);
		parser(s);
		output(s);
		ft_lstdel(&s->memguru, &ft_lstdel_content);
		free(s->line);
		free(s);
	}
	else
		print_usage();
	return (0);
}
