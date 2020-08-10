/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:05:32 by mmanhack          #+#    #+#             */
/*   Updated: 2020/06/28 11:05:34 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "op.h"
#include <errno.h>

t_instr			*init_instr(t_serv *s)
{
	t_instr		*new;
	int			i;

	i = -1;
	if (!(new = ft_memguru(sizeof(*new), &s->memguru)))
		ft_error(ERR_MALLOC, s, ENOMEM);
	new->label = NULL;
	new->op = NULL;
	while (++i < 3)
	{
		new->args[i].code_size = 0;
		new->args[i].is_label = 0;
		new->args[i].type = 0;
		new->args[i].value.num = 0;
		new->args[i].token = NULL;
	}
	new->byte = 0;
	new->acb = 0;
	new->size = 0;
	new->next = NULL;
	return (new);
}

static void		set_size(t_serv *s, t_instr *ptr)
{
	int			i;

	ptr->byte = s->header.prog_size;
	if (ptr && ptr->op)
	{
		ptr->size++;
		ptr->size += ptr->op->is_acb;
		i = -1;
		while (++i < 3)
			ptr->size += ptr->args[i].code_size;
		s->header.prog_size += ptr->size;
	}
}

void			add_instr(t_serv *s, t_instr *new)
{
	t_instr		*ptr;

	if (!s->instr)
		s->instr = new;
	else
	{
		ptr = s->instr;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	if (new->op && new->op->is_acb)
		new->acb = arg_coding_byte(new);
	set_size(s, new);
	if (s->flag & FLAG_INSTR)
		print_instr(s->last_instr);
}

void			parse_arguments(t_serv *s)
{
	int			i;

	i = -1;
	s->tok_ptr = s->tok_ptr->next;
	if (!s->tok_ptr || s->tok_ptr->type == NEW_LINE)
		ft_error(ERR_ARG_NO, s, EINVAL);
	while (s->tok_ptr && s->tok_ptr->type != NEW_LINE)
	{
		if (++i > s->last_instr->op->args_num - 1)
			ft_error(ERR_ARG_OVFL, s, EINVAL);
		parse_arg(s, i);
		if (s->tok_ptr && s->tok_ptr->type == SEPARATOR && s->tok_ptr->next &&
		s->tok_ptr->next->type != NEW_LINE && s->tok_ptr->next->type != COMMENT)
			s->tok_ptr = s->tok_ptr->next;
		else if (s->tok_ptr && s->tok_ptr->type == COMMENT)
			s->tok_ptr = s->tok_ptr->next;
		else if (!s->tok_ptr || s->tok_ptr->type == NEW_LINE)
			break ;
		else
			ft_error(ERR_PARSE_ARG, s, EINVAL);
	}
	add_instr(s, s->last_instr);
	s->last_instr = NULL;
}

void			parser(t_serv *s)
{
	s->tok_ptr = s->tokens;
	while (s->tok_ptr)
	{
		if (s->tok_ptr->type == PROG_NAME)
			parse_prog_name(s);
		else if (s->tok_ptr->type == NEW_LINE && s->last_instr)
		{
			add_instr(s, s->last_instr);
			s->last_instr = NULL;
		}
		else if (s->tok_ptr->type == PROG_COMMENT)
			parse_prog_comment(s);
		else if (s->tok_ptr->type == LABEL)
			parse_label(s);
		else if (s->tok_ptr->type == STRING)
			parse_string(s);
		else if (s->tok_ptr->type == COMMENT)
		{
			s->tok_ptr = s->tok_ptr->next;
			continue;
		}
		s->tok_ptr = (s->tok_ptr ? s->tok_ptr->next : NULL);
	}
	code_labels(s);
}
