/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 07:51:36 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:21:08 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *s)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && quote == 0)
			quote = s[i];
		else if (quote == s[i])
			quote = 0;
		i++;
	}
	if (quote)
		return (0);
	return (1);
}
