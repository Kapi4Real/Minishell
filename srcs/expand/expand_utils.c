/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:57:07 by togomez           #+#    #+#             */
/*   Updated: 2025/05/06 11:22:17 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

t_list	*ft_lstnew_empty(void)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = malloc(1);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	((char *)new->content)[0] = '\0';
	new->next = NULL;
	return (new);
}

bool	is_delimiter(char c)
{
	if (ft_isalnum(c))
		return (false);
	if (c == '_')
		return (false);
	return (true);
}
