
SRCDIR = ./src
OBJDIR = ./obj

CC = m68k-elf-gcc
LD = m68k-elf-ld

CCFLAGS = -nostdinc -pedantic -I./include -I./src -m528x -fno-builtin -Wmissing-declarations -Wmissing-prototypes
LDFLAGS = -T fw.ld -Map ld.map --oformat binary
ROMFLAGS = -T fwrom.ld -Map ldrom.map --oformat binary

OBJS = $(OBJDIR)/main.o $(OBJDIR)/fec.o $(OBJDIR)/eeprom.o $(OBJDIR)/romfs.o
OBJS = $(OBJS) $(OBJDIR)/timer.o $(OBJDIR)/qspi.o $(OBJDIR)/module.o

OBJS = $(OBJS) $(OBJDIR)/stdlib.o $(OBJDIR)/printf.o $(OBJDIR)/string.o $(OBJDIR)/fifo.o
OBJS = $(OBJS) $(OBJDIR)/malloc.o

OBJS = $(OBJS) $(OBJDIR)/nbuf.o $(OBJDIR)/if.o $(OBJDIR)/ip.o $(OBJDIR)/arp.o
OBJS = $(OBJS) $(OBJDIR)/icmp.o $(OBJDIR)/tcp.o $(OBJDIR)/udp.o
OBJS = $(OBJS) $(OBJDIR)/rtp.o $(OBJDIR)/tftp.o

OBJS = $(OBJS) $(OBJDIR)/telnet.o $(OBJDIR)/terminal.o

OBJS = $(OBJS) $(OBJDIR)/kxt.o
OBJS = $(OBJS) $(OBJDIR)/sip.o $(OBJDIR)/g726.o

OBJS = $(OBJS) $(OBJDIR)/dect-main.o $(OBJDIR)/dect-mac.o $(OBJDIR)/dect-server.o
OBJS = $(OBJS) $(OBJDIR)/lsic.o

FOBJS = $(OBJDIR)/start.o $(OBJDIR)/flash.o

all: fwrom.bin

fw.bin: $(OBJS) $(FOBJS)
	$(LD) $(LDFLAGS) -o $@ $(FOBJS) $(OBJS)

fwrom.bin: $(OBJS) $(FOBJS)
	$(LD) $(ROMFLAGS) -o $@ $(OBJS)
	cat ./mkromfs/romfs.bin >> fwrom.bin
	cp -f ./fwrom.bin ../bdm/fwrom.bin

$(OBJDIR)/start.o: $(SRCDIR)/start.s
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/start.s

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/main.c

$(OBJDIR)/fec.o: $(SRCDIR)/fec.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/fec.c

$(OBJDIR)/eeprom.o: $(SRCDIR)/eeprom.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/eeprom.c

$(OBJDIR)/flash.o: $(SRCDIR)/flash.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/flash.c

$(OBJDIR)/timer.o: $(SRCDIR)/timer.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/timer.c

$(OBJDIR)/qspi.o: $(SRCDIR)/qspi.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/qspi.c

$(OBJDIR)/module.o: $(SRCDIR)/module.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/module.c

$(OBJDIR)/romfs.o: $(SRCDIR)/romfs.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/romfs.c


$(OBJDIR)/stdlib.o: $(SRCDIR)/libc/stdlib.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/libc/stdlib.c

$(OBJDIR)/printf.o: $(SRCDIR)/libc/printf.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/libc/printf.c

$(OBJDIR)/string.o: $(SRCDIR)/libc/string.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/libc/string.c

$(OBJDIR)/fifo.o: $(SRCDIR)/libc/fifo.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/libc/fifo.c

$(OBJDIR)/malloc.o: $(SRCDIR)/libc/malloc.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/libc/malloc.c


$(OBJDIR)/nbuf.o: $(SRCDIR)/network/nbuf.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/network/nbuf.c

$(OBJDIR)/if.o: $(SRCDIR)/network/if.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/network/if.c

$(OBJDIR)/ip.o: $(SRCDIR)/network/ip.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/network/ip.c

$(OBJDIR)/arp.o: $(SRCDIR)/network/arp.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/network/arp.c

$(OBJDIR)/icmp.o: $(SRCDIR)/network/icmp.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/network/icmp.c

$(OBJDIR)/tcp.o: $(SRCDIR)/network/tcp.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/network/tcp.c

$(OBJDIR)/udp.o: $(SRCDIR)/network/udp.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/network/udp.c

$(OBJDIR)/rtp.o: $(SRCDIR)/network/rtp.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/network/rtp.c

$(OBJDIR)/tftp.o: $(SRCDIR)/network/tftp.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/network/tftp.c


$(OBJDIR)/telnet.o: $(SRCDIR)/network/telnet.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/network/telnet.c

$(OBJDIR)/terminal.o: $(SRCDIR)/term/terminal.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/term/terminal.c


$(OBJDIR)/kxt.o: $(SRCDIR)/dphone/kxt.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/dphone/kxt.c


$(OBJDIR)/sip.o: $(SRCDIR)/voip/sip.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/voip/sip.c

$(OBJDIR)/g726.o: $(SRCDIR)/voip/g726.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/voip/g726.c


$(OBJDIR)/dect-main.o: $(SRCDIR)/mod-dect/dect-main.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/mod-dect/dect-main.c

$(OBJDIR)/dect-mac.o: $(SRCDIR)/mod-dect/dect-mac.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/mod-dect/dect-mac.c

$(OBJDIR)/dect-server.o: $(SRCDIR)/mod-dect/dect-server.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/mod-dect/dect-server.c


$(OBJDIR)/lsic.o: $(SRCDIR)/mod-lsic/lsic.c
	$(CC) $(CCFLAGS) -c -o $@ $(SRCDIR)/mod-lsic/lsic.c
