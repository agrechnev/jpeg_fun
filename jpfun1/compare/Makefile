include ../param.inc
OBJS=main.o jpbuf.o jpio.o
jpcompare: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
.c.o: 
	$(CC) $(CFLAGS) -c $<
clean:
	-rm jpompare.exe jpcompare *.o core