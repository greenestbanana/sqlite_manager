
OS = windows

ifeq ($(OS), windows)
  REMOVE = del
else 
  REMOVE = -rm
endif

bin\hello.exe : bin obj obj\main.o obj\SqliteConnection.o obj\SqliteDataSet.o obj\SqliteDataRow.o obj\sqlite3.o
	g++ obj\main.o obj\SqliteConnection.o obj\SqliteDataSet.o obj\SqliteDataRow.o obj\sqlite3.o -o bin\hello.exe
	
obj\main.o : src\main.cpp obj
	g++ -c src\main.cpp -o obj\main.o
	
obj\SqliteConnection.o : src\SqliteConnection.cpp obj
	g++ -c src\SqliteConnection.cpp -o obj\SqliteConnection.o
  
obj\SqliteDataSet.o : src\SqliteDataSet.cpp obj
	g++ -c src\SqliteDataSet.cpp -o obj\SqliteDataSet.o
	
obj\SqliteDataRow.o : src\SqliteDataRow.cpp obj
	g++ -c src\SqliteDataRow.cpp -o obj\SqliteDataRow.o
	
obj\sqlite3.o : src\sqlite\sqlite3.c obj
	gcc -c src\sqlite\sqlite3.c -o obj\sqlite3.o
	
bin :
	mkdir bin
	
obj : 
	mkdir obj
	
.PHONY : clean
clean : 
	$(REMOVE) obj\*.o
	
.PHONY : cleanall
cleanall : clean
	$(REMOVE) bin\*.exe