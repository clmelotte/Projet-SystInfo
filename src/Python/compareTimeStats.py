import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from os.path import dirname, abspath

path=dirname(dirname(dirname(abspath(__file__))))

#posix timings

dataPhilo= pd.read_csv(path+'/results/timesPhilo.csv')
dataPhilo=dataPhilo.to_numpy()
dataPhilo=np.delete(dataPhilo,5,1)
philoMean=np.sum(dataPhilo,axis=1)/5
philoStd=np.std(dataPhilo,axis=1)

dataProdCons= pd.read_csv(path+'/results/timesProdCons.csv')
dataProdCons=dataProdCons.to_numpy()
dataProdCons=np.delete(dataProdCons,5,1)
PCMean=np.sum(dataProdCons,axis=1)/5
PCStd=np.std(dataProdCons,axis=1)

dataLectEcr= pd.read_csv(path+'/results/timesLectEcr.csv')
dataLectEcr=dataLectEcr.to_numpy()
dataLectEcr=np.delete(dataLectEcr,5,1)
LEMean=np.sum(dataLectEcr,axis=1)/5
LEStd=np.std(dataLectEcr,axis=1)

#test and set timings

dataPhiloA= pd.read_csv(path+'/results/timesAsmPhilo.csv')
dataPhiloA=dataPhiloA.to_numpy()
dataPhiloA=np.delete(dataPhiloA,5,1)
philoAMean=np.sum(dataPhiloA,axis=1)/5
philoAStd=np.std(dataPhiloA,axis=1)

dataProdA= pd.read_csv(path+'/results/timesAsmProd.csv')
dataProdA=dataProdA.to_numpy()
dataProdA=np.delete(dataProdA,5,1)
prodAMean=np.sum(dataProdA,axis=1)/5
prodAStd=np.std(dataProdA,axis=1)

dataLectA= pd.read_csv(path+'/results/timesAsmLect.csv')
dataLectA=dataLectA.to_numpy()
dataLectA=np.delete(dataLectA,5,1)
lectAMean=np.sum(dataLectA,axis=1)/5
lectAStd=np.std(dataLectA,axis=1)

#test and test and set timings

dataPhiloAVT= pd.read_csv(path+'/results/timesAsmPhiloVT.csv')
dataPhiloAVT=dataPhiloAVT.to_numpy()
dataPhiloAVT=np.delete(dataPhiloAVT,5,1)
philoAVTMean=np.sum(dataPhiloAVT,axis=1)/5
philoAVTStd=np.std(dataPhiloAVT,axis=1)

dataProdAVT= pd.read_csv(path+'/results/timesAsmProdVT.csv')
dataProdAVT=dataProdAVT.to_numpy()
dataProdAVT=np.delete(dataProdAVT,5,1)
prodAVTMean=np.sum(dataProdAVT,axis=1)/5
prodAVTStd=np.std(dataProdAVT,axis=1)

dataLectAVT= pd.read_csv(path+'/results/timesAsmLectVT.csv')
dataLectAVT=dataLectAVT.to_numpy()
dataLectAVT=np.delete(dataLectAVT,5,1)
lectAVTMean=np.sum(dataLectAVT,axis=1)/5
lectAVTStd=np.std(dataLectAVT,axis=1)



n=np.arange(1,17)
nPC=np.arange(2,17)
fig, (philo, pc, le) = plt.subplots(1,3,figsize=(15,8))
plt.subplots_adjust(left=0.1,right=0.9,wspace = 0.2)

philo.plot(n,philoMean,'-r',label='Moyenne posix')
philo.plot(n,philoStd,'ro',label='écart-type posix')
philo.plot(n,philoAMean,'-b',label='Moyenne Test-Set')
philo.plot(n,philoAStd,'bo',label='écart-type Test-Set')
philo.plot(n,philoAVTMean,'-g',label='Moyenne Test-Test-Set')
philo.plot(n,philoAVTStd,'go',label='écart-type Test-Test-Set')
philo.set(xlabel='n of threads',ylabel='time taken in seconds')
philo.set_xticks(n)
philo.legend(loc='upper left')
philo.set_title("Problème des philosophes")

pc.plot(nPC,PCMean,'-r',label='Moyenne posix')
pc.plot(nPC,PCStd,'ro',label='écart-type posix')
pc.plot(nPC,prodAMean,'-b',label='Moyenne Test-Set')
pc.plot(nPC,prodAStd,'bo',label='écart-type Test-Set')
pc.plot(nPC,prodAVTMean,'-g',label='Moyenne Test-Test-Set')
pc.plot(nPC,prodAVTStd,'go',label='écart-type Test-Test-Set')
pc.set(xlabel='n of threads')
pc.set_xticks(n)
pc.legend(loc='upper right')
pc.set_title("Problème Producteurs-Consommateurs")

le.plot(n,LEMean,'-r',label='Moyenne posix')
le.plot(n,LEStd,'ro',label='écart-type posix')
le.plot(n,lectAMean,'-b',label='Moyenne Test-Set')
le.plot(n,lectAStd,'bo',label='écart-type Test-Set')
le.plot(n,lectAVTMean,'-g',label='Moyenne Test-Test-Set')
le.plot(n,lectAVTStd,'go',label='écart-type Test-Test-Set')
le.set(xlabel='n of threads')
le.set_xticks(n)
le.legend(loc='upper left')
le.set_title("Problème Lecteurs-Ecrivains")
plt.show()