Comment utiliser:
Ce projet est muni d'un Makefile, cela veux dire que vous pouvez rapidement effectuer toutes les tâches qu'il est capable d'effectuer en appelant depuis le directory dans lequel se trouve ce readme la commande 'make' suivis d'un mot-clé.

Les différent mot-clés et les actions qui leurs sont liées sont:

-'posixCompile','asmCompile','asmVTCompile': permettent de compiler respectivement les version posix, test-and-set et test-test-and-set des trois problèmes du philosophe, des lecteurs-ecrivains et des producteurs-consommateurs.

-'asmTestsCompile' : permet de compiler les codes de tests crée pour nos code ASMs

-'compileAll' : permet de tout compiler

-'clean' : permet d'effacer tous les executables créés par nos commandes de compilation

-'plotStats' : permet d'executer un script python faisant un plot des statistiques récoltées, des statistiques de test sont déja pré-fournies dans le dossier "results"

!!!ATTENTION!!! ci dessous se trouve les commmandes permettant de ré-executer les script bash effectuant les tests temporels. Sachez que si vous les utilisez, il prendrons pour certains beaucoup de temps à s'executer. Et que si vous commencez l'execution, il vous faudra la laisser terminer afin que les nouvelles statistiques soient complètes. Si vous interrompez leur execution, cela rendra les fonction de plot inutilisable.

-'timePosixTests','timeAsmTests','timeVTTests' : permettent d'executer respectivement les version posix, test-and-set et test-test-and-set des scripts de testing temporels

-'timeTestAsmTest' : permet d'executer les tests temporels pour les codes de test pour nos ASMs

-'timeTestAll' : Lance l'execution de tous les tests temporels

