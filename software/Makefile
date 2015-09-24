
MYSQLDIR = /usr/local

OBJS =  obj/dect.o obj/cfgfile.o obj/server.o obj/sql.o obj/dlc.o obj/nwk.o
OBJS += obj/terminal.o
OBJS += obj/nwk-mm.o obj/nwk-cc.o
OBJS += obj/g726.o obj/g711.o obj/sip.o
OBJS += obj/iwu-panasonic.o obj/iwu-siemens.o

INCLUDES = -I/usr/local/include -I$(MYSQLDIR)/include
LIBS = -L/usr/local/lib -L$(MYSQLDIR)/lib/mysql -lmysqlclient -lcrypt -lz -losip2 -losipparser2 -lortp

all: dect.exe


dect.exe: $(OBJS)
	gcc $(OBJS) $(LIBS) -o dect.exe
	strip dect.exe

obj/%.o: src/%.c
	gcc $(INCLUDES) -c -o $@ $<
