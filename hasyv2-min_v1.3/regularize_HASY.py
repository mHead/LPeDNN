import pandas as pd
import os

try: 

	originalCSV = '/Users/head/Documents/GitHub/LPeDNN/hasyv2-min_v1.3/hasy-data-labels-capital-letters.csv'
	#csvPath = '/Users/head/Documents/GitHub/LPeDNN/hasyv2-min_v1.1/hasy-data-labels-capital-letterss.csv'
	savePath = '/Users/head/Documents/GitHub/LPeDNN/hasyv2-min_v1.3/hasy-data-labels-capital-letters-withMNISTmapping.csv'
	
	cnt = 0
	#tot = len(os.listdir(imagesPath))
	data = []
	df = pd.read_csv(originalCSV, index_col=0)
	tot= (len(df))
	pathString = 'hasy-capital-letters-imgs/'

	for index, row in df.iterrows():
		#inputPath = os.path.join(imagesPath, imgPath)
		path = row['path']
		oldLabel = int(row['symbol_id'])
		letter = row['latex']
		newLabel = oldLabel - 21
		print(f"OLD: {oldLabel}, NEW: {newLabel}")
		
		data.append([path, oldLabel, letter, 0, newLabel])

		cnt += 1
		print(f"Record added! {cnt}/{tot} : {path}")

	data = pd.DataFrame(data, columns=['path', 'symbol_id', 'latex', 'user_id', 'map-MNIST-label'])
	data = data.drop(['user_id'], axis=1)
	print(data)
	data.to_csv(savePath, index=True)

except FileNotFoundError:
	print('Provided image path is not found')