/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 07:51:36 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:21:08 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(const char *s, t_env *env)
{
	int		len;
	char	*result;
	char	*temp;

	len = ft_strlen(s);
	if (len < 2)
		return (ft_strdup(s));
	if (s[0] == '\'' && s[len - 1] == '\'')
		result = ft_substr(s, 1, len - 2);
	else if (s[0] == '"' && s[len - 1] == '"')
	{
		temp = ft_substr(s, 1, len - 2);
		result = expand_vars_in_string(temp, env);
		free(temp);
	}
	else
		result = expand_vars_in_string(ft_strdup(s), env);
	return (result);
}