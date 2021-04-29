import pandas as pd
import os

try: 
	imagesPath = '/Users/head/Desktop/eMNIST/K/'
	originalCSV = '/Users/head/Documents/GitHub/LPeDNN/hasy-data-labels-capital-letters.csv'
	#csvPath = '/Users/head/Documents/GitHub/LPeDNN/hasyv2-min_v1.1/hasy-data-labels-capital-letterss.csv'
	savePath = '/Users/head/Documents/GitHub/LPeDNN/hasyv2-min_v1.1/hasy-data-labels-capital-letters.csv'
	df = pd.read_csv(originalCSV)
	#df = df.drop(['Unnamed: 0', 'Unnamed: 0.1', 'Unnamed: 0.1.1', 'Unnamed: 0.1.1.1', 'Unnamed: 0.1.1.1.1', 'Unnamed: 0.1.1.1.1.1.1.1.1.1'], axis=1)
	#df = df.drop(['Unnamed: 0.1.1.1.1.1'], axis=1)
	df = df.drop(['Unnamed: 0.1'], axis=1)
	df.to_csv(savePath, index=False)

except FileNotFoundError:
	print('Provided image path is not found')