all: gushare

gushare: main.o configuration.o mainwindow.o confwindow.o
	g++ -g configuration.o mainwindow.o main.o confwindow.o -o gushare `pkg-config gtkmm-3.0 --cflags --libs`
main.o: main.cpp 
	g++ -g -c main.cpp -o main.o `pkg-config gtkmm-3.0 --cflags --libs`
mainwindow.o:mainwindow.cpp mainwindow.h
	g++ -g -c mainwindow.cpp -o mainwindow.o -Wall `pkg-config gtkmm-3.0 --cflags --libs`
configuration.o: configuration.cpp configuration.h
	g++ -g -c configuration.cpp -o configuration.o `pkg-config gtkmm-3.0 --cflags --libs`
confwindow.o:confwindow.cpp confwindow.h
	g++ -g -c confwindow.cpp -o confwindow.o -Wall `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm *.o
	rm gushare
