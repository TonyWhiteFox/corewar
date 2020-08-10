/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 09:36:51 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/02/29 19:18:00 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdlib.h>
# include "op.h"

# define ERR_OPEN_FILE		"ERROR: Can\'t open file"
# define ERR_MALLOC			"ERROR: Can\'t allocate memory"
# define ERR_READ_FILE		"ERROR: Incorrect input file"
# define ERR_EMPTY_FILE		"ERROR: Empty input file"
# define ERR_DOUBLE_LABEL	"ERROR: Excessive label delimiter, expected 1"
# define ERR_WRONG_LABEL	"ERROR: Incorrect label name"
# define ERR_WRONG_VALUE	"ERROR: Wrong value, number or label expected"
# define ERR_STR_SPLIT		"ERROR: Can\'t identify tokens in the line"
# define ERR_NAME_LEN		"ERROR: Incorrect program name"
# define ERR_NAME_DOUBLE	"ERROR: Double program name"
# define ERR_COMMENT_LEN	"ERROR: Incorrect program comment"
# define ERR_COMMENT_DBL	"ERROR: Double program comment"
# define ERR_PARSE_STRING	"ERROR: Incorrect string token"
# define ERR_CREATE_FILE	"ERROR: Can\'t create output file"
# define ERR_PARSE_ARG		"ERROR: Can\'t parse argument"
# define ERR_PARSE_ARG_NUM	"ERROR: Wrong number of arguments"
# define ERR_PARSE_ARG_TYPE	"ERROR: Incorrect argument type"
# define ERR_PARSE_DIR		"ERROR: STRING token expected after %"
# define ERR_ARG_NO			"ERROR: No instruction arguments"
# define ERR_ARG_OVFL		"ERROR: Too many arguments"
# define ERR_REG			"ERROR: Incorrect REGISTER argument value"
# define ERR_COMMAND		"ERROR: Undefined command"
# define READ_SIZE			4096
# define FLAG_DUMP			1
# define FLAG_DEBUG			2
# define FLAG_INSTR			4
# define HEX_CHARS			"0123456789abcdef"

typedef enum				e_type
{
	STRING,
	COMMENT,
	DIRECT,
	NUM,
	SEPARATOR,
	NEW_LINE,
	PROG_NAME,
	PROG_COMMENT,
	LABEL,
	LABEL_REF,
}							t_type;

typedef struct				s_token
{
	t_type					type;
	char					*content;
	struct s_token			*next;
}							t_token;

typedef union				u_bytes
{
	int						num;
	char					num1;
	short					num2;
	int						num4;
	unsigned char			unum1;
	unsigned short			unum2;
	unsigned int			unum4;
	unsigned char			bytes[4];
}							t_bytes;

typedef struct				s_serv
{
	int						fd;
	int						fd_out;
	int						flag;
	size_t					i_line;
	size_t					out_line;
	char					*filename;
	char					*line;
	char					*buff;
	char					*ptr1;
	char					*ptr2;
	struct s_list			*arg_labels;
	t_token					*tok_ptr;
	struct s_header			header;
	struct s_instr			*instr;
	struct s_instr			*last_instr;
	struct s_list			*memguru;
	struct s_token			*tokens;

}							t_serv;

typedef struct				s_arg
{
	t_arg_type				type;
	t_bytes					value;
	size_t					is_label;
	char					*token;
	size_t					code_size;
	t_bytes					code;
}							t_arg;

typedef struct				s_instr
{
	char					*label;
	struct s_op				*op;
	struct s_arg			args[3];
	unsigned char			acb;
	size_t					size;
	size_t					byte;
	struct s_instr			*next;
}							t_instr;

void						lexer(t_serv *s);
void						parser(t_serv *s);
void						output(t_serv *s);
void						ft_error(char *err, t_serv *s, int err_code);
void						*ft_memguru(size_t size, struct s_list **list);
void						*ft_memguru_add_arr(void **arr, size_t arr_size,
							struct s_list **list);
void						*ft_memguru_add(void *ptr, struct s_list **list);
t_instr						*init_instr(t_serv *s);
void						parse_num(t_serv *s);
void						parse_comment(t_serv *s);
void						parse_str(t_serv *s);
void						parse_command(t_serv *s);
void						add_token(t_serv *s, t_token *new);
t_token						*init_token(t_serv *s, t_type type, char *str,
							size_t len);
size_t						len_to_end(t_serv *s, char end);
int							get_offset(t_serv *s, t_instr *instr, char *label);
unsigned char				arg_coding_byte(t_instr *ptr);
void						print_arg(t_instr *ptr, int i);
void						print_dump(t_serv *s);
void						parse_reg(t_serv *s, int i);
void						parse_ind(t_serv *s, int i);
void						parse_dir(t_serv *s, int i);
void						parse_arg(t_serv *s, int i);
void						parse_arguments(t_serv *s);
void						parse_prog_comment(t_serv *s);
void						parse_prog_name(t_serv *s);
void						parse_label(t_serv *s);
int							parse_op(t_serv *s);
void						parse_string(t_serv *s);
t_op						*get_op(char *name);
void						add_instr(t_serv *s, t_instr *new);
void						print_instr(t_instr *ptr);
int							ft_atoi_base(char *nb, int base);
t_bytes						ft_atoi_check(char *nb);
void						print_instr_code(t_instr *instr, int pass);
unsigned int				swap_bytes(unsigned int num, size_t len);
void						parse_ref_label(t_serv *s);
void						code_labels(t_serv *s);
void						ft_lstdel_content(void *content, size_t size);
int							ft_is_bin(char *nb);
int							ft_is_hex(char *nb);
size_t						get_str_len(t_serv *s);
void						skip_whitespace(t_serv *s);

#endif
