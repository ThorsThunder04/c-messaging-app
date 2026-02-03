CC=gcc
FLAGS=-Wall

BINS=bin/client bin/server

all: client

client: client.c
	$(CC) $(FLAGS) client.c -o client