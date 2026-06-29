main: src/main.cpp
	g++ -g -Iinclude src/main.cpp -o main

doc:
	doxygen Doxyfile
	@echo "Documentação gerada! Abra html/index.html no navegador."

clean:
	rm -f main