test_indexation_image: src/test_indexation_image.c src/indexation_image.c inc/indexation_image.h src/toolbox.c inc/toolbox.h
	gcc -c src/toolbox.c -Wall
	gcc -c src/indexation_image.c -Wall
	gcc -c src/test_indexation_image.c -Wall
	mv ./*.o ./obj
	gcc -o ./app/test_indexation_image.out ./obj/test_indexation_image.o ./obj/toolbox.o ./obj/indexation_image.o -Wall

test_display_console: src/admin.c inc/admin.h src/test_display_console.c src/console.c inc/console.h src/toolbox.c inc/toolbox.h
	gcc -c src/admin.c -Wall
	gcc -c src/toolbox.c -Wall
	gcc -c src/console.c -Wall
	gcc -c src/test_display_console.c -Wall
	mv ./*.o ./obj
	gcc -o ./app/test_display_console.out ./obj/admin.o ./obj/test_display_console.o ./obj/console.o ./obj/toolbox.o

test_login_admin: src/test_login_admin.c src/admin.c inc/admin.h src/console.c inc/console.h src/toolbox.c inc/toolbox.h
	gcc -c src/admin.c -Wall
	gcc -c src/toolbox.c -Wall
	gcc -c src/console.c -Wall
	gcc -c src/test_login_admin.c -Wall
	mv ./*.o ./obj
	gcc -o ./app/test_login_admin.out ./obj/test_login_admin.o ./obj/console.o ./obj/toolbox.o ./obj/admin.o