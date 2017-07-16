CMP = g++ -std=c++11 -lX11
MAIN = snake
CLASS = snakeboard
EXEC = playsnake

$(EXEC): $(MAIN).o $(CLASS).o gfxnew.o
	$(CMP) $(MAIN).o $(CLASS).o gfxnew.o -o $(EXEC)

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp -o $(MAIN).o

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(CLASS).cpp -o $(CLASS).o

clean:
	rm $(CLASS).o $(MAIN).o
	rm $(EXEC)
