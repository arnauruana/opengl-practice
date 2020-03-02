# opengl-practice

Practice of all-in-one OpneGL problems for VJ-FIB.


## Setup

1. Install packages `make` and `qt5-base`.
2. Install packages `glut`, `glew`, `glm`, `soil` and `freetype2`

Command (Arch Linux):

~~~bash
sudo pacman -Syu make qt5-base --needed --noconfirm && qmake && make install && make pristine
~~~


## Build

1. Generate `makefile`
2. Compile project and generate binary

Command:

~~~bash
qmake && make
~~~


## Run

1. Execute the binary file

Command:

~~~bash
make run
~~~


## Cleanup

1. Delete generated files and directories

Command:

~~~bash
make pristine
~~~
