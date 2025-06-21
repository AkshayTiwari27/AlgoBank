# Makefile: To compile the entire project easily.
# To use: Run `make` in the terminal in the project directory.

all: algobank

algobank: main.o BankSystem.o Graph.o FraudDetector.o Trie.o CreditSystem.o
	g++ main.o BankSystem.o Graph.o FraudDetector.o Trie.o CreditSystem.o -o algobank -std=c++17

main.o: main.cpp
	g++ -c main.cpp -std=c++17

BankSystem.o: BankSystem.cpp BankSystem.hpp
	g++ -c BankSystem.cpp -std=c++17

Graph.o: Graph.cpp Graph.hpp
	g++ -c Graph.cpp -std=c++17

FraudDetector.o: FraudDetector.cpp FraudDetector.hpp
	g++ -c FraudDetector.cpp -std=c++17

Trie.o: Trie.cpp Trie.hpp
	g++ -c Trie.cpp -std=c++17

CreditSystem.o: CreditSystem.cpp CreditSystem.hpp
	g++ -c CreditSystem.cpp -std=c++17

clean:
	rm -f *.o algobank