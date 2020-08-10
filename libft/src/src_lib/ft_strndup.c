/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldonnor- <ldonnor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 13:01:34 by ldonnor-          #+#    #+#             */
/*   Updated: 2020/07/11 13:01:37 by ldonnor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*str;
	int		j;

	j = 0;
	if (!(str = (char *)malloc(sizeof(char) * (n + 1))))
		return (0);
	str[n] = 0;
	while (j < n)
	{
		if (s1[j])
			str[j] = s1[j];
		else
			str[j] = 0;
		++j;
	}
	return (str);
}
