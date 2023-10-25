CC:=cc
TARGET:=main
CFLAGS:=-g -Wall -std=c17 -fsanitize=address
RFLAGS:=-std=c17 -DNDEBUG -O3
CFILES:=main.c

.PHONY: clean
.PHONY: install

debug: $(CFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(CFILES)

release: $(CFILES)
	$(CC) $(RFLAGS) -o $(TARGET) $(CFILES)

install:
	sudo cp -i $(TARGET) /bin/$(TARGET)

uninstall:
	sudo rm -i /bin/$(TARGET)

clean:
	rm $(TARGET)
