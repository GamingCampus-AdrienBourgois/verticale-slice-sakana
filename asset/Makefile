# Nom du fichier exécutable
TARGET = mon_programme

# Compilateur
CC = g++

# Drapeaux de compilation
CFLAGS = -Wall -std=c++17

# Bibliothèques de la SFML à lier
SFML_LINK = -lsfml-graphics -lsfml-window -lsfml-system

# Tous les fichiers sources à compiler
SOURCES = *.cpp

# Règle pour tout compiler
all: $(TARGET)

re: clean $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(SFML_LINK)

clean:
	rm -f $(TARGET)

.PHONY: all clean
