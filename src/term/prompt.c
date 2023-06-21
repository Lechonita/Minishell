/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bebigel <bebigel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:00:31 by lechon            #+#    #+#             */
/*   Updated: 2023/06/21 11:48:54 by bebigel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	catch_ctrl_d(t_bigshell *data)
{
	char	buf[1];

	buf[0] = 0;
	if (!data)
		return ;
	if (read(STDIN, buf, 0) == 0)
	{
		ft_putstr_fd("ctrl D \n", 2);
		ft_free_all(data);
		exit(0);
	}
}

void	ft_save_history(t_bigshell *data, char *input, int count)
{
	if (!data || !input)
		return ;
	data->history[count] = ft_strdup(input);
	if (!data->history[count])
		return ;
}


int main() {
    char buffer[256];
    ssize_t bytesRead;

    printf("Entrez du texte (appuyez sur Ctrl+D pour quitter) :\n");

    while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        // Traitez les caractères lus ici
        // ...

        // Lire le caractère suivant
    }

    printf("Fin du programme.\n");
    return 0;
}




void	ft_readline(t_bigshell *data)
{
	char	*input;
	int		count;

	count = 0;
	data->history = ft_calloc(50, sizeof(char *));
	set_signal();
	while (1)
	{
		input = readline("$ ");
		if (!ft_strncmp(input, "exit", 4) && ft_strlen(input) == 4)
			break ;
		// printf("input = %s\n", input);
		if (input[0] != '\0')
		{
			add_history(input);
			ft_save_history(data, input, count);
			count++;
		}
		// else if (read(STDIN, input, 0) == EOF)
		// {
		// 	ft_putstr_fd("ctrl D \n", 2);
		// 	ft_free_all(data);
		// 	exit(0);
		// }
		free(input);
	}
	free(input);
}
