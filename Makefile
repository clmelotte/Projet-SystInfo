compile : ./src/C/Philosophe.c ./src/C/ProducteurConsommateur.c ./src/C/LecteurEcrivain.c
	@gcc -w -std=c99 -o philo ./src/C/Philosophe.c -lpthread 
	@chmod a+x philo
	@gcc -w -std=c99 -o prodCons ./src/C/ProducteurConsommateur.c -lpthread
	@chmod a+x prodCons
	@gcc -w -std=c99 -o lectEcr ./src/C/LecteurEcrivain.c -lpthread
	@chmod a+x lectEcr
clean :
	@rm -fv philo
	@rm -fv prodCons
	@rm -fv lectEcr
	@rm -fv asmProd
	@rm -fv asmPhilo
	@rm -fv asmLect
	@rm -fv asmProdVT
	@rm -fv asmPhiloVT
	@rm -fv asmLectVT
	@rm -fv testAsm
	@rm -fv testAsmVT
	@rm -fv testAsmBOff
timeTests:
	@make compile
	@bash ./timeTestPhilo
	@bash ./timeTestProdCons
	@bash ./timeTestLectEcr
	@make clean
plotStats: ./src/Python/timeStats.py ./src/Python/compareTimeStats.py ./src/Python/AsmTestsTimeStats.py
	@python ./src/Python/timeStats.py
asmCompile: ./src/C/AsmProdCons.c ./src/C/AsmPhilo.c ./src/C/AsmLectEcr.c ./src/C/AsmMu.c ./src/C/AsmSem.c
	@gcc -w -std=c99 -o asmProd ./src/C/AsmProdCons.c ./src/C/AsmMu.c ./src/C/AsmSem.c -lpthread -fasm
	@chmod a+x asmProd
	@gcc -w -std=c99 -o asmPhilo ./src/C/AsmPhilo.c ./src/C/AsmMu.c -lpthread -fasm
	@chmod a+x asmPhilo
	@gcc -w -std=c99 -o asmLect ./src/C/AsmLectEcr.c ./src/C/AsmMu.c -lpthread -fasm
	@chmod a+x asmLect
asmTestsCompile: ./src/C/TestAsmMu.c ./src/C/AsmMu.c ./src/C/TestAsmMuVT.c ./src/C/AsmMuVT.c ./src/C/TestAsmMuBOff.c ./src/C/AsmMuBOff.c
	@gcc -w -std=c99 -o testAsm ./src/C/TestAsmMu.c ./src/C/AsmMu.c -lpthread -fasm
	@chmod a+x testAsm
	@gcc -w -std=c99 -o testAsmVT ./src/C/TestAsmMuVT.c ./src/C/AsmMuVT.c -lpthread -fasm
	@chmod a+x testAsmVT
	@gcc -w -std=c99 -o testAsmBOff ./src/C/TestAsmMuBOff.c ./src/C/AsmMuBOff.c -lpthread -fasm
	@chmod a+x testAsmBOff
asmVTCompile: ./src/C/AsmVTProdCons.c ./src/C/AsmVTPhilo.c ./src/C/AsmVTLectEcr.c ./src/C/AsmMuVT.c ./src/C/AsmSem.c
	@gcc -w -std=c99 -o asmProdVT ./src/C/AsmVTProdCons.c ./src/C/AsmMuVT.c ./src/C/AsmSem.c -lpthread -fasm
	@chmod a+x asmProdVT
	@gcc -w -std=c99 -o asmPhiloVT ./src/C/AsmVTPhilo.c ./src/C/AsmMuVT.c -lpthread -fasm
	@chmod a+x asmPhiloVT
	@gcc -w -std=c99 -o asmLectVT ./src/C/AsmVTLectEcr.c ./src/C/AsmMuVT.c -lpthread -fasm
	@chmod a+x asmLectVT
compileAll: 
	@make compile
	@make asmTestsCompile
	@make asmCompile
	@make asmVTCompile
