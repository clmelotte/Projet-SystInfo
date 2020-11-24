import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

dataPhiloDf= pd.read_csv('timesPhilo.csv')
philo1=dataPhiloDf['1'].to_numpy()
philo2=dataPhiloDf['2'].to_numpy()
philo3=dataPhiloDf['3'].to_numpy()
philo4=dataPhiloDf['4'].to_numpy()
philo5=dataPhiloDf['5'].to_numpy()
dataPhilo=np.array([philo1,philo2,philo3,philo4,philo5])
philoMean=np.sum(dataPhilo,axis=0)/5
philoStd=np.std(dataPhilo,axis=0)
dataProdConsDf= pd.read_csv('timesProdCons.csv',sep=',')
PC1=dataProdConsDf['1'].to_numpy()
PC2=dataProdConsDf['2'].to_numpy()
PC3=dataProdConsDf['3'].to_numpy()
PC4=dataProdConsDf['4'].to_numpy()
PC5=dataProdConsDf['5'].to_numpy()
dataProdCons=np.array([PC1,PC2,PC3,PC4,PC5])
PCMean=np.sum(dataProdCons,axis=0)/5
PCStd=np.std(dataProdCons,axis=0)
dataLectEcrDf= pd.read_csv('timesLectEcr.csv',sep=',')
LE1=dataLectEcrDf['1'].to_numpy()
LE2=dataLectEcrDf['2'].to_numpy()
LE3=dataLectEcrDf['3'].to_numpy()
LE4=dataLectEcrDf['4'].to_numpy()
LE5=dataLectEcrDf['5'].to_numpy()
dataLectEcr=np.array([LE1,LE2,LE3,LE4,LE5])
LEMean=np.sum(dataLectEcr,axis=0)/5
LEStd=np.std(dataLectEcr,axis=0)
#print(philoMean,philoStd,PCMean,PCStd,LEMean,LEStd)

n=np.arange(2,18)
fig, (philo, pc, le) = plt.subplots(1,3,figsize=(15,8))
plt.subplots_adjust(left=0.1,right=0.9,wspace = 0.2)

philo.plot(n,philoMean,'-r',label='Moyenne')
philo.plot(n,philoStd,'ro',label='écart-type')
philo.set(xlabel='n of threads',ylabel='time taken in seconds')
philo.set_xticks(n)
philo.legend(loc='upper right')
philo.set_title("Problème des philosophes")

pc.plot(n,PCMean,'-b',label='Moyenne')
pc.plot(n,PCStd,'bo',label='écart-type')
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
