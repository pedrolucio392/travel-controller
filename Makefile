main: src/main.cpp src/Cidade.cpp src/Passageiro.cpp src/Trajeto.cpp
	g++ -g -Iinclude src/main.cpp src/Cidade.cpp src/Passageiro.cpp src/Trajeto.cpp -o main

test: src/testes.cpp src/Cidade.cpp src/Passageiro.cpp src/Trajeto.cpp src/Transporte.cpp src/Viagem.cpp src/ControladorDeTransito.cpp
	g++ -g -Iinclude src/testes.cpp src/Cidade.cpp src/Passageiro.cpp src/Trajeto.cpp src/Transporte.cpp src/Viagem.cpp src/ControladorDeTransito.cpp -o run_testes
	./run_testes

doc:
	doxygen Doxyfile
	@echo "Documentação gerada! Abra html/index.html no navegador."

clean:
	rm -f main run_testes