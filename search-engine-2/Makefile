CC = gcc

SRCDIR = src
INCDIR = inc
OBJDIR = obj
APPDIR = app
BRIDIR = bridge

CFLAGS = -I$(INCDIR) -g -W -Wall

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h 
	mkdir -p app/ bridge/ obj/ descriptors/audio descriptors/image descriptors/text results/
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm ./obj/*.o


##########################################################################################
#                                      tests                                             #
##########################################################################################
test_indexation_text: $(OBJ) src/test/test_indexation_text.c
	gcc -c src/test/test_indexation_text.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(APPDIR)/$@ $^ $(CFLAGS)

test_indexation_image: $(OBJ) src/test/test_indexation_image.c
	gcc -c src/test/test_indexation_image.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(APPDIR)/$@ $^ $(CFLAGS)

test_indexation_audio: $(OBJ) src/test/test_indexation_audio.c
	gcc -c src/test/test_indexation_audio.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(APPDIR)/$@ $^ $(CFLAGS)

test_display_console: $(OBJ) src/test/test_display_console.c
	gcc -c src/test/test_display_console.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(APPDIR)/$@ $^ $(CFLAGS)

test_login_admin: $(OBJ) src/test/test_login_admin.c
	gcc -c src/test/test_login_admin.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(APPDIR)/$@ $^ $(CFLAGS)

test_config_admin: $(OBJ) src/test/test_config_admin.c
	gcc -c src/test/test_config_admin.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(APPDIR)/$@ $^ $(CFLAGS)

test_comparison_image: $(OBJ) src/test/test_comparison_image.c
	gcc -c src/test/test_comparison_image.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(APPDIR)/$@ $^ $(CFLAGS)	

test_comparison_audio: $(OBJ) src/test/test_comparison_audio.c
	gcc -c src/test/test_comparison_audio.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(APPDIR)/$@ $^ $(CFLAGS)	


##########################################################################################
#                                      bridge                                            #
##########################################################################################
indexing : $(OBJ) src/bridge/indexing.c
	gcc -c src/bridge/indexing.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(BRIDIR)/$@ $^ $(CFLAGS)	

searcher_text: $(OBJ) src/bridge/searcher_text.c
	gcc -c src/bridge/searcher_text.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(BRIDIR)/$@ $^ $(CFLAGS)	

searcher_image: $(OBJ) src/bridge/searcher_image.c
	gcc -c src/bridge/searcher_image.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(BRIDIR)/$@ $^ $(CFLAGS)	

searcher_audio : $(OBJ) src/bridge/searcher_audio.c
	gcc -c src/bridge/searcher_audio.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(BRIDIR)/$@ $^ $(CFLAGS)	

log : $(OBJ) src/bridge/log.c
	gcc -c src/bridge/log.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(BRIDIR)/$@ $^ $(CFLAGS)	

parameters : $(OBJ) src/bridge/parameters.c
	gcc -c src/bridge/parameters.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(BRIDIR)/$@ $^ $(CFLAGS)	

descriptor_view : $(OBJ) src/bridge/descriptor_view.c
	gcc -c src/bridge/descriptor_view.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(BRIDIR)/$@ $^ $(CFLAGS)	

##########################################################################################
#                                        main                                            #
##########################################################################################
main: $(OBJ) src/release/main.c
	gcc -c src/release/main.c $(CFLAGS)
	mv ./*.o ./obj
	$(CC) -o $(APPDIR)/$@ $^ $(CFLAGS)	