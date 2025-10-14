/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 06:37:41 by togomez           #+#    #+#             */
/*   Updated: 2025/05/21 06:38:15 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

bool	needs_expansion(char *str)
{
	while (*str)
	{
		if (*str == '$' && (*(str + 1) == '?' || ft_isalnum(*(str + 1))))
			return (true);
		str++;
	}
	return (false);
}
