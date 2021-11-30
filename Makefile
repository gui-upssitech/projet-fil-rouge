test_indexation_image: src/test_indexation_image.c src/indexation_image.c inc/indexation_image.h src/toolbox.c inc/toolbox.h
	gcc -c src/toolbox.c -Wall
	gcc -c src/indexation_image.c -Wall
	gcc -c src/test_indexation_image.c -Wall
	mv ./*.o ./obj
	gcc -o ./app/test_indexation_image.out ./obj/test_indexation_image.o ./obj/toolbox.o ./obj/indexation_image.o -Wall

test_display_console: src/test_display_console.c src/display.c inc/display.h src/toolbox.c inc/toolbox.h
	gcc -c src/toolbox.c -Wall
	gcc -c src/display.c -Wall
	gcc -c src/test_display_console.c -Wall
	mv ./*.o ./obj
	gcc -o ./app/test_display_console.out ./obj/test_display_console.o ./obj/display.o ./obj/toolbox.o