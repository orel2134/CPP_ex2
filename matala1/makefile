CC = gcc
AR = ar
CFLAGS = -g -Wall
LDFLAGS = -lm
OBJECTS_LOOP_BASIC = basicClassification.o advancedClassificationLoop.o
OBJECTS_RECURSIVE_BASIC = basicClassification.o advancedClassificationRecursion.o

all: mains maindloop maindrec

maindrec: main.o recursived
	$(CC) $(CFLAGS) -o maindrec $(OBJECTS_RECURSIVE_BASIC) -L. -lclassrec $(LDFLAGS)

maindloop: main.o loopd
	$(CC) $(CFLAGS) -o maindloop $(OBJECTS_LOOP_BASIC) -L. -lclassloops $(LDFLAGS)

mains: main.o recursives
	$(CC) $(CFLAGS) -o mains $(OBJECTS_RECURSIVE_BASIC) -L. -lclassrec $(LDFLAGS)

loops: $(OBJECTS_LOOP_BASIC)
	$(AR) -rcs libclassloops.a $(OBJECTS_LOOP_BASIC)

loopd: $(OBJECTS_LOOP_BASIC)
	$(CC) -fPIC -shared $(OBJECTS_LOOP_BASIC) -o libclassloops.so 

recursives: $(OBJECTS_RECURSIVE_BASIC)
	$(AR) -rcs libclassrec.a $(OBJECTS_RECURSIVE_BASIC)

recursived: $(OBJECTS_RECURSIVE_BASIC)
	$(CC) -fPIC -shared $(OBJECTS_RECURSIVE_BASIC) -o libclassrec.so 

main.o: main.c NumClass.h
	$(CC) $(CFLAGS) -c main.c

basicClassification.o: basicClassification.c NumClass.h
	$(CC) $(CFLAGS) -c basicClassification.c 

advancedClassificationLoop.o: advancedClassificationLoop.c NumClass.h
	$(CC) $(CFLAGS) -c advancedClassificationLoop.c

advancedClassificationRecursion.o: advancedClassificationRecursion.c NumClass.h
	$(CC) $(CFLAGS) -c advancedClassificationRecursion.c

clean:
	rm -f *.o *.a *.so mains maindloop maindrec
	