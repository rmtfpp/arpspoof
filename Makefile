GCC = gcc
CFLAGS = -Wall -Wextra
CGDB = -g

MAIN = src/main.c
PACKAGE_BUILD = src/arpr_build.c
PACKAGE_SEND = src/arpr_send.c

TARGET = arpspoof

all: $(TARGET)

$(TARGET): $(MAIN) $(PACKAGE_BUILD) $(PACKAGE_SEND)
	$(GCC) $(CFLAGS) $(CGDB) -o $(TARGET) $(MAIN) $(PACKAGE_BUILD) $(PACKAGE_SEND)

clean:
	rm -f $(TARGET)