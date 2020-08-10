/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memguru.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/02 14:49:42 by mmanhack          #+#    #+#             */
/*   Updated: 2020/04/02 14:49:46 by mmanhack         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "asm.h"
#include "libft.h"

void	*ft_memguru_add(void *ptr, t_list **list)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(*new))))
		return (NULL);
	new->content = ptr;
	new->content_size = sizeof(ptr);
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		new->next = *list;
		*list = new;
	}
	return (new->content);
}

void	*ft_memguru_add_arr(void **arr, size_t arr_size, t_list **list)
{
	size_t		i;
	void		*ret;

	i = 0;
	while (i < arr_size)
	{
		if (!(ret = ft_memguru_add(arr[i++], list)))
			return (NULL);
	}
	if (!(ret = ft_memguru_add(arr, list)))
		return (NULL);
	return (ret);
}

void	*ft_memguru(size_t size, t_list **list)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(*new))))
		return (NULL);
	if (!(new->content = (void *)ft_memalloc(size)))
		return (NULL);
	new->content_size = size;
	new->next = NULL;
	if (!*list)
		*list = new;
	else
	{
		new->next = *list;
		*list = new;
	}
	return (new->content);
}

int		ft_is_bin(char *nb)
{
	size_t		i;

	i = ft_strlen(nb);
	if (i > 2 && nb[0] == '0' && nb[1] == 'b' && ft_isnumber(&nb[2]))
		return (1);
	errno = EDOM;
	return (0);
}

int		ft_is_hex(char *nb)
{
	size_t		i;

	i = ft_strlen(nb);
	if (i > 2 && nb[0] == '0' && (nb[1] == 'x' || nb[1] == 'X'))
	{
		nb = &nb[1];
		while (*(++nb))
		{
			if (!ft_strchr(HEX_CHARS, *nb))
			{
				errno = EDOM;
				return (0);
			}
		}
		return (1);
	}
	errno = EDOM;
	return (0);
}
