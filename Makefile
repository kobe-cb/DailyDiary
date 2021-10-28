#Program: Diary makefile

#Variables
FLAGS = -g -W -Wall -Werror -ansi -pedantic
OBJS = Diary.o Entry.o Genre.o Topic.o User.o

#Targets

all: main.cpp $(OBJS)
	g++ $(FLAGS) -o DailyDiary.out main.cpp $(OBJS) -std=c++11

allWindows: main.cpp $(OBJS)
	g++ $(FLAGS) -o DailyDiary.exe main.cpp $(OBJS) -std=c++11

Diary.o: Diary.cpp Diary.h
	g++ $(FLAGS) -c Diary.cpp -std=c++11

Entry.o: Entry.cpp Entry.h
	g++ $(FLAGS) -c Entry.cpp -std=c++11

Genre.o: Genre.cpp Genre.h
	g++ $(FLAGS) -c Genre.cpp -std=c++11

Topic.o: Topic.cpp Topic.h
	g++ $(FLAGS) -c Topic.cpp -std=c++11
User.o: User.cpp User.h
	g++ $(FLAGS) -c User.cpp -std=c++11

clean:
	rm -rf *~ *.o DailyDiary.out DailyDiary.exe