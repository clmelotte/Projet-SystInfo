compile : Philosophe.c ProducteurConsommateur.c LecteurEcrivain.c
	@gcc -w -std=c99 -o philo Philosophe.c -lpthread 
	@chmod a+x philo
	@gcc -w -std=c99 -o prodCons ProducteurConsommateur.c -lpthread
	@chmod a+x prodCons
	@gcc -w -std=c99 -o lectEcr LecteurEcrivain.c -lpthread
	@chmod a+x lectEcr
clean :
	@rm -fv philo
	@rm -fv prodCons
	@rm -fv lectEcr
	@rm -fv asmProd
	@rm -fv asmPhilo
	@rm -fv asmLect
	@rm -fv testAsm
	@rm -fv testAsmVT
timeTests:
	@make compile
	@bash ./timeTestPhilo
	@bash ./timeTestProdCons
	@bash ./timeTestLectEcr
	@make clean
plotStats:
	@python timeStats.py
asmCompile: AsmProdCons.c AsmPhilo.c AsmLectEcr.c AsmMu.c AsmSem.c
	gcc -w -std=c99 -o asmProd AsmProdCons.c AsmMu.c AsmSem.c -lpthread -fasm
	chmod a+x asmProd
	gcc -w -std=c99 -o asmPhilo AsmPhilo.c AsmMu.c -lpthread -fasm
	chmod a+x asmPhilo
	gcc -w -std=c99 -o asmLect AsmLectEcr.c AsmMu.c -lpthread -fasm
	chmod a+x asmLect
asmTestsCompile: TestAsmMu.c AsmMu.c TestAsmMuVT.c AsmMuVT.c
	gcc -w -std=c99 -o testAsm TestAsmMu.c AsmMu.c -lpthread -fasm
	chmod a+x testAsm
	gcc -w -std=c99 -o testAsmVT TestAsmMuVT.c AsmMuVT.c -lpthread -fasm
	chmod a+x testAsmVT
