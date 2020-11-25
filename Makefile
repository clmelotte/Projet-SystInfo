compile : Philosophe.c ProducteurConsommateur.c LecteurEcrivain.c
	@gcc -w -std=c99 -o philo Philosophe.c -lpthread -lm
	@chmod a+x philo
	@gcc -w -std=c99 -o prodCons ProducteurConsommateur.c -lpthread -lm
	@chmod a+x prodCons
	@gcc -w -std=c99 -o lectEcr LecteurEcrivain.c -lpthread -lm 
	@chmod a+x lectEcr
clean :
	@rm -fv philo
	@rm -fv prodCons
	@rm -fv lectEcr
	@rm -fv asmProd
timeTests:
	@make compile
	@bash ./timeTestPhilo
	@bash ./timeTestProdCons
	@bash ./timeTestLectEcr
	@make clean
plotStats:
	@python timeStats.py
asmCompile:
	gcc -w -std=c99 -o asmProd AsmProdCons.c AsmMu.c -lpthread -lm -fasm
	chmod a+x asmProd
