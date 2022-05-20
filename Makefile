OBJ_dir = obj
OBJECTOS = main.o client.o driver.o memory.o process.o restaurant.o configuration.o stats.o synchronization.o metime.o mesignal.o log.o

magnaeats: $(OBJECTOS)
	gcc $(addprefix $(OBJ_dir)/,$(OBJECTOS)) -o bin/magnaeats -lrt -lpthread
main.o: src/main.c include/main.h
	gcc  -g -I include -o obj/main.o -c src/main.c
client.o: src/client.c include/client.h
	gcc -Wall -g -I include -o obj/client.o -c src/client.c
driver.o: src/driver.c include/driver.h
	gcc -Wall -g -I include -o obj/driver.o -c src/driver.c
memory.o: src/memory.c include/memory.h
	gcc -Wall -g -I include -o obj/memory.o -c src/memory.c 
process.o: src/process.c include/process.h
	gcc -Wall -g -I include -o obj/process.o -c src/process.c
restaurant.o: src/restaurant.c include/restaurant.h
	gcc -Wall -g -I include -o obj/restaurant.o -c src/restaurant.c
configuration.o: src/configuration.c include/configuration.h
	gcc -Wall -g -I include -o obj/configuration.o -c src/configuration.c
stats.o: src/stats.c include/stats.h
	gcc -Wall -g -I include -o obj/stats.o -c src/stats.c
synchronization.o: src/synchronization.c include/synchronization.h
	gcc -Wall -g -I include -o obj/synchronization.o -c src/synchronization.c
metime.o: src/metime.c include/metime.h
	gcc -Wall -g -I include -o obj/metime.o -c src/metime.c
mesignal.o: src/mesignal.c include/mesignal.h
	gcc -Wall -g -I include -o obj/mesignal.o -c src/mesignal.c
log.o: src/log.c include/log.h
	gcc -Wall -g -I include -o obj/log.o -c src/log.c

