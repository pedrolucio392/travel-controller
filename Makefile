main: src/main.cpp src/Cidade.cpp src/Passageiro.cpp
	g++ -g -Iinclude src/main.cpp src/Cidade.cpp src/Passageiro.cpp -o main

test: src/testes.cpp src/Cidade.cpp src/Passageiro.cpp
	g++ -g -Iinclude src/testes.cpp src/Cidade.cpp src/Passageiro.cpp -o run_testes
	./run_testes

doc:
	doxygen Doxyfile
	@echo "Documentação gerada! Abra html/index.html no navegador."

clean:
	rm -f main run_testes