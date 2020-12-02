import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

dataTS= pd.read_csv('timesAsmTest.csv')
dataTS=dataTS.to_numpy()
dataTS=np.delete(dataTS,5,1)
TSMean=np.sum(dataTS,axis=1)/5
TSStd=np.std(dataTS,axis=1)

dataTTS= pd.read_csv('timesAsmTestVT.csv')
dataTTS=dataTTS.to_numpy()
dataTTS=np.delete(dataTTS,5,1)
TTSMean=np.sum(dataTTS,axis=1)/5
TTSStd=np.std(dataTTS,axis=1)

n=np.arange(1,17)

plt.plot(n,TSMean,'-r',label='Moyenne Test-Set')
plt.plot(n,TSStd,'ro',label='écart-type Test-Set')
plt.plot(n,TTSMean,'-b',label='Moyenne Test-Test-Set')
plt.plot(n,TTSStd,'bo',label='écart-type Test-Test-Set')
plt.xlabel('n of threads')
plt.ylabel('time taken in seconds')
plt.legend(loc='upper left')
plt.show()