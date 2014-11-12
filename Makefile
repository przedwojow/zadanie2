__start__: obj interp4face
	./interp4face

obj:
	mkdir obj

CPPFLAGS=-Wall -g -std=c++11 -pedantic -Iinc
LDFLAGS=-Wall

interp4face:  obj/libinterface.o obj/main.o obj/set4libinterfaces.o
	g++ ${LDFLAGS} -o interp4face   obj/libinterface.o\
                          obj/set4libinterfaces.o obj/main.o -ldl

obj/libinterface.o: src/libinterface.cpp inc/libinterface.hh inc/command.h
	g++ -c ${CPPFLAGS} -o obj/libinterface.o src/libinterface.cpp

obj/set4libinterfaces.o: src/set4libinterfaces.cpp inc/set4libinterfaces.hh\
                    inc/libinterface.hh
	g++ -c ${CPPFLAGS} -o obj/set4libinterfaces.o src/set4libinterfaces.cpp

obj/main.o: src/main.cpp inc/libinterface.hh inc/set4libinterfaces.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

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
 
