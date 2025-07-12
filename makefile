PA6: driver.o
	g++ driver.o -o PA6

driver.o: driver.cpp binarysearchtree.h binarytree.h linkedtreenode.h tree.h
	g++ -c driver.cpp

clean:
	rm *.o PA6