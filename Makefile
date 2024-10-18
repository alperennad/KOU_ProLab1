# Değişkenler
CC = gcc
SDL_FLAGS = `sdl2-config --cflags --libs` -lSDL2_image
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
