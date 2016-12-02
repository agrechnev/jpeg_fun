CC=gcc
# Set up the path to jpeg-9b library here
JDIR=d:\prog\jpeg-9b
LDFLAGS= -L$(JDIR)\.libs -ljpeg
CFLAGS= -I$(JDIR)
