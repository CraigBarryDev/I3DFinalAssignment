LIBS = -lGL -lGLU -lglut -lm ./framework/libSOIL.a
CC = gcc
OBJECTS = framework/camera.o framework/geom/cube.o framework/collisions.o framework/geom/cylinder.o display.o framework/frameTimer.o frog.o framework/glGraphics.o init.o input.o framework/keys.o main.o framework/model.o framework/mouse.o framework/objLoader.o framework/particles.o framework/plane.o framework/projectileMotion.o framework/geom/projectileCurve.o framework/geom/skybox.o framework/geom/sphere.o framework/texture.o rendering.o framework/terrain.o framework/tree.o update.o framework/utils.o framework/vectorMath.o framework/vectors.o

all: $(OBJECTS)
	$(CC) $^ -o app $(LIBS) 
	./app
	clear

%.o: %.c
	$(CC) -c $< -o $@

remake:
	clear
	rm -f $(OBJECTS)
	rm -f app
	make all

clean: 
	rm -f $(OBJECTS)
	rm -f app
	rm -f *.objdata
