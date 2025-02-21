inverted_index.out : main.o common.o create_database.o diplay_database.o LL_operations.o save_database.o search_database.o update_database.o
	gcc main.o common.o create_database.o diplay_database.o LL_operations.o save_database.o search_database.o update_database.o -o inverted_index.out
main.o : main.c
	gcc -c main.c
common.o : common.c
	gcc -c common.c
create_database.o : create_database.c
	gcc -c create_database.c
diplay_database.o : diplay_database.c
	gcc -c diplay_database.c
LL_operations.o : LL_operations.c
	gcc -c LL_operations.c
save_database.o : save_database.c
	gcc -c save_database.c
search_database.o : search_database.c
	gcc -c search_database.c
update_database.o : update_database.c
	gcc -c update_database.c
clean :
	rm *.o *.out
