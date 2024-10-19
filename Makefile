# Değişkenler
CC = gcc
SDL_FLAGS = -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_image
CURL_FLAGS = -lcurl

# Hedefler
all: graph url

# graph hedefi
graph: graph.c
	$(CC) -o graph graph.c $(SDL_FLAGS)

# url hedefi
url: url.c
	$(CC) -o url url.c $(CURL_FLAGS)

# Temizleme komutu
clean:
	rm -f graph url
