include ../param.inc
OBJS=main.o jpbuf.o jpio.o
jpcreate: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)
.c.o: 
	$(CC) $(CFLAGS) -c $<
clean:
	-rm jpcreate.exe jpcreate *.o core