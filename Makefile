OBJ_dir = obj
OBJECTOS = main.o client.o driver.o memory.o process.o restaurant.o

magnaeats: $(OBJECTOS)
	gcc $(addprefix $(OBJ_dir)/,$(OBJECTOS)) -o bin/magnaeats -lrt
main.o: src/main.c include/main.h
	gcc -Wall -g -I include -o obj/main.o -c src/main.c
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

