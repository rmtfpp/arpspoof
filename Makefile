GCC = gcc
CFLAGS = -Wall -Wextra
CGDB = -g

MAIN = src/main.c
PACKAGE_BUILD = src/arpr_build.c
PACKAGE_SEND = src/arpr_send.c
MAC_FIND = src/get_mac.c

TARGET = arpspoof

all: $(TARGET)

$(TARGET): $(MAIN) $(PACKAGE_BUILD) $(PACKAGE_SEND) $(MAC_FIND)
	$(GCC) $(CFLAGS) $(CGDB) -o $(TARGET) $(MAIN) $(PACKAGE_BUILD) $(PACKAGE_SEND) $(MAC_FIND)

clean:
	rm -f $(TARGET)