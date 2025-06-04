CC = gcc
CFLAGS = -Iinclude \
         -I/opt/homebrew/Cellar/cjson/1.7.18/include

LDFLAGS = -L/opt/homebrew/Cellar/cjson/1.7.18/lib -lcjson -lpthread

SRCS = main.c src/for_uvicorn.c src/process_list.c src/logs.c
TARGET = rthread

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
