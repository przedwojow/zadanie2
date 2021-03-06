__start__: obj __plugin__ interp4face
	 rlwrap -pyellow -w 200 -S'Twoj wybor (? - menu): ' ./interp4face

obj:
	mkdir obj

__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -g -std=c++11 -pedantic -Iinc
LDFLAGS=-Wall

interp4face:  obj/libinterface.o obj/main.o obj/set4libinterfaces.o obj/scene.o  obj/robotface.o\
	      obj/lacze_do_gnuplota.o obj/Wektor2D.o obj/xmlparser4scene.o obj/metodyMain.o \
	      obj/Oko_robotface.o obj/Usta_robotface.o obj/Brew_robotface.o
	g++ ${LDFLAGS} -o interp4face   obj/libinterface.o obj/xmlparser4scene.o obj/scene.o\
			  obj/lacze_do_gnuplota.o obj/Wektor2D.o obj/metodyMain.o  obj/robotface.o\
			  obj/Oko_robotface.o obj/Usta_robotface.o obj/Brew_robotface.o\
                          obj/set4libinterfaces.o obj/main.o -ldl -lxerces-c

obj/libinterface.o: src/libinterface.cpp inc/libinterface.hh inc/command.h
	g++ -c ${CPPFLAGS} -o obj/libinterface.o src/libinterface.cpp

obj/set4libinterfaces.o: src/set4libinterfaces.cpp inc/set4libinterfaces.hh\
                    inc/libinterface.hh
	g++ -c ${CPPFLAGS} -o obj/set4libinterfaces.o src/set4libinterfaces.cpp

obj/main.o: src/main.cpp inc/metodyMain.h
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

obj/Wektor2D.o: src/Wektor2D.cpp inc/Wektor2D.hh 
	g++ ${CPPFLAGS} -c -o obj/Wektor2D.o src/Wektor2D.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++ ${CPPFLAGS} -c -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/xmlparser4scene.o: src/xmlparser4scene.cpp inc/xmlparser4scene.hh
	g++ -c ${CPPFLAGS} -o obj/xmlparser4scene.o src/xmlparser4scene.cpp

obj/metodyMain.o: src/metodyMain.cpp inc/metodyMain.h inc/libinterface.hh inc/set4libinterfaces.hh\
	    inc/lacze_do_gnuplota.hh inc/Wektor2D.hh inc/scene.hh inc/robotface.h
	g++ -c ${CPPFLAGS} -o obj/metodyMain.o src/metodyMain.cpp

obj/scene.o: src/scene.cpp inc/scene.hh inc/command.h inc/libinterface.hh\
	    inc/set4libinterfaces.hh
	g++ ${CPPFLAGS} -c -o obj/scene.o src/scene.cpp

obj/robotface.o: src/robotface.cpp inc/robotface.h inc/command.h inc/lacze_do_gnuplota.hh\
	    inc/Wektor2D.hh inc/robotfaceInterface.h inc/Wektor2D.hh
	g++ ${CPPFLAGS} -c -o obj/robotface.o src/robotface.cpp

obj/Oko_robotface.o: src/Oko_robotface.cpp inc/robotface.h inc/command.h inc/lacze_do_gnuplota.hh\
	    inc/Wektor2D.hh inc/robotfaceInterface.h inc/Wektor2D.hh
	g++ ${CPPFLAGS} -c -o obj/Oko_robotface.o src/Oko_robotface.cpp

obj/Usta_robotface.o: src/Usta_robotface.cpp inc/robotface.h inc/command.h inc/lacze_do_gnuplota.hh\
	    inc/Wektor2D.hh inc/robotfaceInterface.h inc/Wektor2D.hh
	g++ ${CPPFLAGS} -c -o obj/Usta_robotface.o src/Usta_robotface.cpp

obj/Brew_robotface.o: src/Brew_robotface.cpp inc/robotface.h inc/command.h inc/lacze_do_gnuplota.hh\
	    inc/Wektor2D.hh inc/robotfaceInterface.h inc/Wektor2D.hh
	g++ ${CPPFLAGS} -c -o obj/Brew_robotface.o src/Brew_robotface.cpp

clean:
	rm -f obj/* interp4face core*

doc:
	cd ./dox;  make
	@echo
	@echo  "  Dokumentacja zostala umieszczona w katalogu dox/doc/html"
	@echo

cleandoc:
	cd ./dox;  make clean
	@echo 
	@echo  "  Dokumentacja zostala usunieta"
	@echo


clean_all: clean cleandoc
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  doc   - powoduje generowanie dokumentacji"
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  cleandoc - usuwa wygenerowana dokumentacje"
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo "  make doc       # generuje dokumentacje w doc/html"
	@echo
 
