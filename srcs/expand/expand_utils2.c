/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:57:07 by togomez           #+#    #+#             */
/*   Updated: 2025/05/06 11:22:17 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

int	is_env(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] != '$')
		i++;
	return (s[i] != 0);
}

bool	is_whitespace(char c)
{
	return ((c >= 7 && c <= 13) || c == 32);
}

char	*ft_strjoin_char(char *s1, char c, bool free_data)
{
	int		tot_size;
	char	*newchain;
	int		i;

	tot_size = ft_strlen(s1) + 2;
	newchain = ft_calloc(tot_size, sizeof(char));
	i = 0;
	if (!newchain)
		return (NULL);
	while (s1[i])
	{
		newchain[i] = s1[i];
		i++;
	}
	newchain[i++] = c;
	newchain[i] = 0;
	if (free_data)
		free(s1);
	return (newchain);
}

int	env_var_exists(char *var, int len, t_env *envi)
{
	while (envi)
	{
		if (ft_strncmp(envi->name, var, len) == 0 && envi->name[len] == '\0')
			return (1);
		envi = envi->next;
	}
	return (0);
}
