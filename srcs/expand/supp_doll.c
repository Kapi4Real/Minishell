/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_doll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 06:37:41 by togomez           #+#    #+#             */
/*   Updated: 2025/05/21 06:38:15 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	is_quote(char c, char *quote)
{
	if (*quote == 0 && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

static void	handle_dollar(char *s, int *i, char quote, t_dollar *d)
{
	if (s[*i] == '$' && quote != '\'')
	{
		if (s[*i + 1] == '?' || ft_isalnum(s[*i + 1]) || s[*i + 1] == '_')
		{
			d->result[d->y++] = s[(*i)++];
			return ;
		}
		if (s[*i + 1] == '\'' || s[*i + 1] == '"')
			(*i)++;
	}
	if (s[*i])
		d->result[d->y++] = s[(*i)++];
}

char	*supp_dollars(char *s)
{
	int			i;
	t_dollar	d;
	char		quote;

	quote = 0;
	d.result = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!d.result)
		return (NULL);
	i = 0;
	d.y = 0;
	while (s[i])
	{
		is_quote(s[i], &quote);
		handle_dollar(s, &i, quote, &d);
	}
	free(s);
	return (d.result);
}*/
