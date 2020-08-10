/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 23:06:06 by mmanhack          #+#    #+#             */
/*   Updated: 2020/07/03 23:06:10 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

void				print_arg_code(t_instr *ptr, int i, int pass)
{
	unsigned char		len;
	t_arg				arg;

	len = 0;
	arg = ptr->args[i];
	if (arg.type == T_REG)
		ft_printf("%-18d", arg.code.num);
	else if (pass == 2)
		ft_printf("%-18d", arg.value.num);
	else if (arg.type == T_IND
			|| (arg.type == T_DIR && ptr->op->reduced_dir_size))
	{
		ft_printf("%-4u", arg.code.bytes[0]);
		ft_printf("%-4u", arg.code.bytes[1]);
		ft_printf("          ");
	}
	else if (arg.type == T_DIR)
	{
		while (len < 4)
			ft_printf("%-4u", ptr->args[i].code.bytes[len++]);
		ft_printf("  ");
	}
}

void				print_arg(t_instr *ptr, int i)
{
	if (ptr->args[i].type == T_DIR || ptr->args[i].type == T_REG)
	{
		if (ptr->args[i].type == T_DIR)
			write(1, "%", 1);
		else if (ptr->args[i].type == T_REG)
			write(1, "r", 1);
		if (ptr->args[i].is_label)
			ft_printf(":%-16s", ptr->args[i].token);
		else
			ft_printf("%-17d", ptr->args[i].value);
	}
	else if (ptr->args[i].is_label)
		ft_printf(":%-17s", ptr->args[i].token);
	else
		ft_printf("%-18d", ptr->args[i].value);
}

void				print_instr(t_instr *ptr)
{
	int		j;

	if (ptr)
	{
		if (ptr->label)
			ft_printf("%-11d:    %s:\n", ptr->byte, ptr->label);
		if (ptr->op)
		{
			ft_printf("%-5d(%-3d) :        ", ptr->byte, ptr->size);
			ft_printf("%-10s", ptr->op->name);
			j = -1;
			while (++j < 3 && ptr->args[j].type)
				print_arg(ptr, j);
			ft_printf("\n");
		}
	}
}

void				print_instr_code(t_instr *instr, int pass)
{
	int			j;

	ft_printf("                    ");
	ft_printf("%-4u", instr->op->code);
	ft_printf("%-6.u", instr->acb);
	j = -1;
	while (++j < 3 && instr->args[j].type)
		print_arg_code(instr, j, pass);
	ft_printf("\n");
}

void				print_dump(t_serv *s)
{
	t_instr		*ptr;

	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", s->header.prog_size);
	ft_printf("Name : \"%s\"\n", s->header.prog_name);
	ft_printf("Comment : \"%s\"\n\n", s->header.comment);
	ptr = s->instr;
	while (ptr)
	{
		print_instr(ptr);
		if (ptr->op)
		{
			print_instr_code(ptr, 1);
			print_instr_code(ptr, 2);
			ft_printf("\n");
		}
		ptr = ptr->next;
	}
}
