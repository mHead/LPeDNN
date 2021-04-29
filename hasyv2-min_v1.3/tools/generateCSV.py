import pandas as pd
import os

try: 
	imagesPath = '/Users/head/Desktop/eMNIST/Z/'
	originalCSV = '/Users/head/Documents/GitHub/LPeDNN/hasy-data-labels-capital-letters.csv'
	#csvPath = '/Users/head/Documents/GitHub/LPeDNN/hasyv2-min_v1.1/hasy-data-labels-capital-letterss.csv'
	savePath = '/Users/head/Documents/GitHub/LPeDNN/hasyv2-min_v1.1/hasy-data-labels-capital-letters.csv'
	
	cnt = 0
	tot = len(os.listdir(imagesPath))
	data = []
	df = pd.read_csv(originalCSV)

	pathString = 'hasy-capital-letters-imgs/'

	for imgPath in os.listdir(imagesPath):
		#inputPath = os.path.join(imagesPath, imgPath)

		save_path = os.path.join(pathString, imgPath)
		
		data.append([save_path, 56, 'Z', 0])

		cnt += 1
		print("Record added! {}/{} : {}".format(cnt, tot, save_path))

	data = pd.DataFrame(data, columns=['path', 'symbol_id', 'latex', 'user_id'])
	df = df.append(data, ignore_index=True)
	print(df)
	df.to_csv(savePath, index=True)

except FileNotFoundError:
	print('Provided image path is not found')