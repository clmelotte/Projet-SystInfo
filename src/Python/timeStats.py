import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from os.path import dirname, abspath

path=dirname(dirname(dirname(abspath(__file__))))

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

n=np.arange(1,17)
nPC=np.arange(2,17)
fig, (philo, pc, le) = plt.subplots(1,3,figsize=(15,8))
plt.subplots_adjust(left=0.1,right=0.9,wspace = 0.2)

philo.plot(n,philoMean,'-r',label='Moyenne')
philo.plot(n,philoStd,'ro',label='écart-type')
philo.set(xlabel='n of threads',ylabel='time taken in seconds')
philo.set_xticks(n)
philo.legend(loc='upper right')
philo.set_title("Problème des philosophes")

pc.plot(nPC,PCMean,'-b',label='Moyenne')
pc.plot(nPC,PCStd,'bo',label='écart-type')
pc.set(xlabel='n of threads')
pc.set_xticks(n)
pc.legend(loc='upper right')
pc.set_title("Problème Producteurs-Consommateurs")

le.plot(n,LEMean,'-g',label='Moyenne')
le.plot(n,LEStd,'go',label='écart-type')
le.set(xlabel='n of threads')
le.set_xticks(n)
le.legend(loc='upper right')
le.set_title("Problème Lecteurs-Ecrivains")
plt.show()
