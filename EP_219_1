import pandas as pd
import array as arr
import numpy as np
import matplotlib.pyplot as plt
f=pd.read_table('Complete_TAVG_daily.txt', sep='\s+',comment='%')
#dt=np.dtype([])
#print(f)
ar=f.values 
#ar1=f.values['Anomaly']
#print ar1
tfix= lambda t : t + 8.68
vtfix=np.vectorize(tfix)
ncolumn = vtfix(ar[:,5])
reshapencolumn= np.reshape(ncolumn, (ncolumn.size,1))
fnew=np.append(ar,reshapencolumn,axis=1)
x=reshapencolumn
a= input("enter the year:")
def f(a):
	i=1
	row=0
	rowstart=0
	rowend=0
	req=arr.array('d')
	while i>0:
		if (fnew[row][1]== a) and ((fnew[row][3]== 1) or (fnew[row][3]==15)):
				rowstart=row
				req.append(fnew[row][6])
		
		if (fnew[row][1]!= a) and (rowstart!=0):	
	    		#rowend=row-1
	    		break
		row=row+1	
	#req=fnew[rowstart : rowend+1,6] 	
	plt.xlabel('Temperature')
	plt.ylabel('No. of days')
	plt.title(a)
	plt.hist(req, bins=7, histtype='bar',rwidth=0.3)
	plt.show()
f(a)
