GCC = gcc
CFLAGS = -Wall -Wextra
CGDB = -g

MAIN = main.c
PACKAGE_BUILD = arpr_build.c
PACKAGE_SEND = arpr_send.c

TARGET = arpspoof

all: $(TARGET)

$(TARGET): $(MAIN) $(PACKAGE_BUILD) $(PACKAGE_SEND)
	$(GCC) $(CFLAGS) $(CGDB) -o $(TARGET) $(MAIN) $(PACKAGE_BUILD) $(PACKAGE_SEND)

clean:
	rm -f $(TARGET)