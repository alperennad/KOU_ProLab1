# Değişkenler
CC = gcc
CURL_FLAGS = -lcurl -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_image

# Hedefler
all: clean game

# url hedefi
game:
	$(CC) -o game graph.c url.c main.c json_parser.c battle_mechanics.c $(CURL_FLAGS)

# Temizleme komutu
clean:
	rm -rf game