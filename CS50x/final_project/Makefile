LIBS=-D_DEFAULT_SOURCE -D_XOPEN_SOURCE=600 -lncursesw  -Wl,-O1,--sort-common,--as-needed,-z,relro,-z,now 
hellomake: main.c 
	gcc -g $(LIBS) main.c -o out

