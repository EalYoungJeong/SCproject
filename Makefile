all:Server Client

Server:svr.c
	gcc -o Server -g svr.c -lcrypto

Client:cli.c
	gcc -o Client -g cli.c
