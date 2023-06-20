/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:32:09 by paulorod          #+#    #+#             */
/*   Updated: 2023/06/19 16:30:15 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*Count characters that the server received
Once it prints the count exit the client*/
void	signal_handler(int signum)
{
	if (signum == SIGUSR2)
	{
		ft_printf("%sServer received message.%s\n", GREEN, RESET);
		exit(0);
	}
}

/*Send the string to the server by converting the characters to binary
SIGUSR1 = 0s & SIGUSR2 = 1s*/
void	send_data(int pid, char *str)
{
	int		i;
	int		j;
	char	c;

	j = 0;
	while (str[j])
	{
		i = 8;
		c = str[j++];
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			pause();
		}
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		pause();
	}
}

/*Initialize client*/
int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc != 3)
	{
		ft_printf("%sInvalid number of arguments!%s\n", RED, RESET);
		return (1);
	}
	ft_printf("Sending \"%s%s%s\" to server %s%s%s\n",
		YELLOW, argv[2], RESET,
		CYAN, argv[1], RESET);
	server_pid = ft_atoi(argv[1]);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	send_data(server_pid, argv[2]);
	while (true)
		pause();
	return (0);
}
