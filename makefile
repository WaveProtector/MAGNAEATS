OBJ_dir = obj
OBJECTOS = main.o client.o driver.o memory.o process.o restaurant.o
main.o = main.h
client.o = client.h
driver.o = driver.h
memory.o = memory.h
process.o = process.h
restaurant.o = restaurant.h
CC = gcc
out: $(OBJECTOS)
      $(CC) $(addprefix $(OBJ_DIR)/,$(OBJECTOS)) -o bin/magnaeats
%.o: src/%.c $($@)
$(CC) -I include -o $(OBJ_dir)/$@ -c $<
