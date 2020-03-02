TEMPLATE = app
MAKEFILE = makefile

QT =


DESTDIR     = bin/
OBJECTS_DIR = obj/

HEADERS += inc/*
SOURCES += src/*

INCLUDEPATH += inc/
INCLUDEPATH += /usr/include/freetype2

LIBS = -lGL -lglut -lGLEW -lSOIL -lfreetype


run.target   = run
run.depends  = $(TARGET)
run.commands = $(TARGET)
QMAKE_EXTRA_TARGETS += run

clean.target   = pristine
clean.depends  = distclean
clean.commands = $(DEL_DIR) bin obj
QMAKE_EXTRA_TARGETS += clean

install.target   = install
install.depends  =
install.commands = sudo pacman -Syu glut glew glm soil freetype2 --needed --noconfirm
QMAKE_EXTRA_TARGETS += install
