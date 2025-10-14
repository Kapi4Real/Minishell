/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:38:15 by togomez           #+#    #+#             */
/*   Updated: 2025/05/21 08:14:27 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	how_many_q(char *arg)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
			nb++;
		i++;
	}
	return (nb);
}

char	*slash_quotes(char *arg)
{
	int		nb_quotes;
	int		i;
	int		y;
	char	*result;

	nb_quotes = how_many_q(arg);
	i = 0;
	y = 0;
	if (!nb_quotes)
		return (arg);
	result = ft_calloc(ft_strlen(arg) + nb_quotes + 1, sizeof(char));
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
		{
			result[y] = '\\';
			y++;
		}
		result[y] = arg[i];
		y++;
		i++;
	}
	free(arg);
	return (result);
}

static void	update_quote_state(char c, char *quote)
{
	if (*quote == 0)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

char	*supp_quotes(char *s)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	if (!s)
		return (NULL);
	result = malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			update_quote_state(s[i], &quote);
		else
			result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
	free(s);
	return (result);
}
