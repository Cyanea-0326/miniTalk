SERVER = server
CLIENT = client

CFLAGS = -Wall -Werror -Wextra $(FT_PRINTF_A) $(LIBFT_A)
FLAGS = -Wall -Werror -Wextra 

FT_PRINTF_A =  ./ft_printf/ft_printf.a 
LIBFT_A = ./ft_printf/includes/libft/libft.a

$(FT_PRINTF): $(LIBFT)
	make -C ./ft_printf

$(LIBFT): 
	make -C ./ft_printf/includes/libft

all:
	@make -C ./ft_printf/includes/libft
	@make -C ./ft_printf
	@gcc $(CFLAGS) ./server.c -o $(SERVER)
	@gcc $(CFLAGS) ./client.c -o $(CLIENT)
	@echo "\033[31mS\033[0m\033[32me\033[0m\033[33mr\033[0m\033[34mv\033[0m\033[35me\033[0m\033[36mr\033[0m \033[31mA\033[0m\033[32mn\033[0m\033[33md\033[0m \033[34mC\033[0m\033[35ml\033[0m\033[36mi\033[0m\033[31me\033[0m\033[32mn\033[0m\033[33mt\033[0m \033[34mA\033[0m\033[35mr\033[0m\033[36me\033[0m \033[31mR\033[0m\033[32me\033[0m\033[33ma\033[0m\033[34md\033[0m\033[35my\033[0m!"

clean:
	rm -f $(SERVER) $(CLIENT)

fclean: clean
	make -C ./ft_printf fclean

re: fclean all