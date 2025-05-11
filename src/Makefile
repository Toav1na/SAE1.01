main.exe:
	gcc -Wall main.c etudiants/Etudiants.c jury/jury.c respStage/responsable.c -o main.exe
clean:
	rm main.exe
r:
	./main.exe
doc:
	rm -rf ../doxygen/html; cd ../; doxygen
cleanDoc:
	rm -rf ../doxygen/html