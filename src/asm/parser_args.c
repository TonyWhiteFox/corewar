/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 22:49:53 by mmanhack          #+#    #+#             */
/*   Updated: 2020/07/03 22:49:57 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "libft.h"
#include "asm.h"
#include <errno.h>

void	parse_reg(t_serv *s, int i)
{
	t_bytes			value;

	if (!(s->last_instr->op->args_types[i] & T_REG))
		ft_error(ERR_PARSE_ARG_TYPE, s, EINVAL);
	value = ft_atoi_check(&s->tok_ptr->content[1]);
	s->last_instr->args[i].token = s->tok_ptr->content;
	s->last_instr->args[i].type = T_REG;
	s->last_instr->args[i].value = value;
	s->last_instr->args[i].code_size = 1;
	s->last_instr->args[i].code = value;
	s->tok_ptr = s->tok_ptr->next;
}

void	parse_ind(t_serv *s, int i)
{
	t_bytes			value;
	t_list			*new;

	if (!(s->last_instr->op->args_types[i] & T_IND))
		ft_error(ERR_PARSE_ARG_TYPE, s, EINVAL);
	new = NULL;
	s->last_instr->args[i].type = T_IND;
	s->last_instr->args[i].code_size = IND_SIZE;
	if (s->tok_ptr->type == LABEL_REF)
	{
		s->last_instr->args[i].is_label = 1;
		s->last_instr->args[i].token = s->tok_ptr->content;
		if (!(new = ft_memguru(sizeof(*new), &s->memguru)))
			ft_error(ERR_MALLOC, s, ENOMEM);
		new->content = s->last_instr;
		ft_lstadd(&s->arg_labels, new);
	}
	else
	{
		value = ft_atoi_check(s->tok_ptr->content);
		s->last_instr->args[i].value = value;
		s->last_instr->args[i].code.unum4 =
				swap_bytes(value.unum4, IND_SIZE);
	}
	s->tok_ptr = s->tok_ptr->next;
}

void	parse_dir_value(t_serv *s, int i)
{
	t_list		*new;
	t_arg		*arg;

	new = NULL;
	arg = &s->last_instr->args[i];
	if (s->tok_ptr && (s->tok_ptr->type == NUM || s->tok_ptr->type == STRING ||
		s->tok_ptr->type == LABEL_REF))
	{
		arg->token = s->tok_ptr->content;
		if (s->tok_ptr->type == NUM)
			arg->value = ft_atoi_check(s->tok_ptr->content);
		else if (s->tok_ptr->type == STRING && (ft_isnumber(s->tok_ptr->content)
		|| ft_is_hex(s->tok_ptr->content) || ft_is_bin(s->tok_ptr->content)))
			arg->value = ft_atoi_check(s->tok_ptr->content);
		else if (s->tok_ptr->type == LABEL_REF)
		{
			arg->is_label = 1;
			if (!(new = ft_memguru(sizeof(*new), &s->memguru)))
				ft_error(ERR_MALLOC, s, ENOMEM);
			new->content = s->last_instr;
			ft_lstadd(&s->arg_labels, new);
		}
	}
	else
		ft_error(ERR_PARSE_ARG, s, EINVAL);
}

void	parse_dir(t_serv *s, int i)
{
	t_arg		*arg;

	if (!(s->last_instr->op->args_types[i] & T_DIR))
		ft_error(ERR_PARSE_ARG_TYPE, s, EINVAL);
	arg = &s->last_instr->args[i];
	arg->type = T_DIR;
	arg->code_size = (s->last_instr->op->reduced_dir_size ?
			DIR_SIZE / 2 : DIR_SIZE);
	s->tok_ptr = s->tok_ptr->next;
	parse_dir_value(s, i);
	arg->code.unum4 = swap_bytes(arg->value.unum4, arg->code_size);
	s->tok_ptr = s->tok_ptr->next;
}

void	parse_arg(t_serv *s, int i)
{
	if (s->tok_ptr->type == DIRECT)
		parse_dir(s, i);
	else if (s->tok_ptr->type == STRING && s->tok_ptr->content[0] == REG_CHAR)
		parse_reg(s, i);
	else if (s->tok_ptr->type == NUM || s->tok_ptr->type == LABEL_REF
			|| s->tok_ptr->type == STRING)
		parse_ind(s, i);
	else
		ft_error(ERR_PARSE_ARG, s, EINVAL);
}
