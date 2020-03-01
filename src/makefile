
all: compile link

compile: main.o Game.o Scene.o Quad.o Shader.o Text.o Texture.o TexturedQuad.o ShaderProgram.o

link: opengl.exe

run:
	(cd ../res ; ../bin/opengl.exe)

%.o : %.cpp
	g++ -c -Wall $< -I/usr/include/freetype2 -I../inc/ -o ../obj/$@

%.exe: main.o Game.o Scene.o Quad.o Shader.o Text.o Texture.o TexturedQuad.o ShaderProgram.o
	g++ -o ../bin/$@ ../obj/* -lglut -lGL -lGLEW -lfreetype -lSOIL

clean:
	rm -rfv ../bin/*
	rm -rfv ../obj/*
