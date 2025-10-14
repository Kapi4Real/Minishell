/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 06:22:51 by togomez           #+#    #+#             */
/*   Updated: 2025/05/21 08:16:04 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include <stdbool.h>

static bool	split_here(char quote, bool is_var, int i, char *s)
{
	if (quote)
	{
		if (s[i] == quote)
			return (true);
		return (false);
	}
	if (is_var)
	{
		if (s[i] == '$' || is_delimiter(s[i]))
			return (true);
		return (false);
	}
	if (is_whitespace(s[i]))
		return (true);
	return (false);
}

static void	handle_quote(char *s, int i, char *quote)
{
	if (s[i] == '\'' || s[i] == '"')
	{
		if (*quote == s[i])
			*quote = 0;
		else if (*quote == 0)
			*quote = s[i];
	}
}

static int	process_char(char *s, int i, t_list **tmp, char quote)
{
	t_list	*new;
	char	*new_content;

	if (!quote && split_here(quote, (s[0] == '$' && (s[1] == '?' \
		|| !is_delimiter(s[1]))), i, s))
	{
		new = ft_lstnew_empty();
		if (!new)
			return (i);
		ft_lstadd_back(tmp, new);
		*tmp = (*tmp)->next;
	}
	else
	{
		new_content = ft_strjoin_char((*tmp)->content, s[i], true);
		if (new_content)
			(*tmp)->content = new_content;
	}
	return (i + 1);
}

t_list	*split_in_lst(char *s)
{
	t_list	*first;
	t_list	*tmp;
	char	quote;
	int		i;

	if (!s || !*s)
		return (NULL);
	first = ft_lstnew_empty();
	if (!first)
		return (NULL);
	tmp = first;
	i = 0;
	quote = 0;
	while (s[i])
	{
		handle_quote(s, i, &quote);
		if (s[i] == '\'' || s[i] == '"')
		{
			i++;
			continue ;
		}
		i = process_char(s, i, &tmp, quote);
	}
	return (first);
}