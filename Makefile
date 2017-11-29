PROGRAMS = SNAPtest CDHtest CSGtest CRtest CPtest QUERYtest

CFLAGS = -g -std=c99 -Wall -Werror

programs: $(PROGRAMS)

SNAPtest: SNAP.o
	$(CC) -o $@ $^
CDHtest: CDH.o
	$(CC) -o $@ $^
CSGtest: CSG.o
	$(CC) -o $@ $^
CRtest: CR.o
	$(CC) -o $@ $^
CPtest: CP.o
	$(CC) -o $@ $^

QUERYtest: query.o
	$(CC) -o $@ $^

clean:
	-rm $(PROGRAMS) *.o