IDIR = include
LDIR = C:/sdl2/lib
ODIR = output

LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -static-libgcc -static-libstdc++ -Wl,-subsystem,windows

CC = g++
CFLAGS = -I$(IDIR) -L$(LDIR)
DEPS = gfx.h maths.h game.h animation.h gamestructs.h player.h sword.h characterlist.h collision.h hitbox.h ingameui.h input.h menu.h particle.h swordlist.h viewport.h button.h

%.o: %.c $(DEPS)
	$(CC) -c -o $(ODIR) $(CFLAGS)

main: src/*.cpp
	$(CC)  -o $(ODIR)/game src/*.cpp $(CFLAGS) $(LIBS)

clean:
	rm -f $(ODIR)/*.*