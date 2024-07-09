# Makefile per il progetto ATdot

# Compilatore
CC = g++

# Opzioni di compilazione
CFLAGS = -std=c++11 -Wall

# Librerie
LIBS = -lncurses

# Directory dei file sorgente e degli header
SRC_DIR = .
INCLUDE_DIR = src/include

# Nome del tuo eseguibile
TARGET = ATdot

# Lista di tutti i file sorgente
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Lista di tutti i file oggetto
OBJS = $(SRCS:.cpp=.o)

# Percorso per la compilazione degli oggetti
%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -MMD -MP -c $< -o $@

# Regola per la compilazione del programma
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -o $@ $(LIBS)

# Include le dipendenze generate automaticamente
-include $(OBJS:.o=.d)

.PHONY: clean

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(TARGET)
