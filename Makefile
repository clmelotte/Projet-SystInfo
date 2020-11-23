compile : Philosophe.c producteurConsommateur.c LecteurEcrivain.c
	gcc -w -std=c99 -o philo Philosophe.c -lpthread -lm
	chmod a+x philo
	gcc -w -std=c99 -o prodCons producteurConsommateur.c -lpthread -lm
	chmod a+x prodCons
	gcc -w -std=c99 -o lectEcr LecteurEcrivain.c -lpthread -lm
	chmod a+x lectEcr
clean :
	rm -fv philo
	rm -fv prodCons
	rm -fv lectEcr
testPhilo :
	./philo 2
testProdCons :
	./prodCons 2 2
testLesctEcr:
	./lectEcr 2 2
runTest:
	@make -s testLesctEcr testProdCons -j3