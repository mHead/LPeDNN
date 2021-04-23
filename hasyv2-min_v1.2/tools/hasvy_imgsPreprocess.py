from PIL import Image
import PIL.ImageOps
import os

try: 
	imgDirPath = '/Users/head/Desktop/by_field/hsf_0/upper/5a'
	outPath = '/Users/head/Desktop/eMNIST/Z/'
	cnt = 0
	tot = len(os.listdir(imgDirPath))

	for imgPath in os.listdir(imgDirPath):
		inputPath = os.path.join(imgDirPath, imgPath)
		img = Image.open(inputPath)
		resized = img.resize((28, 28))
		invertedImage = PIL.ImageOps.invert(resized)
		fullOutPath = os.path.join(outPath, imgPath)
		grayscaledImage = PIL.ImageOps.grayscale(invertedImage)
		grayscaledImage.save(fullOutPath)
		cnt += 1
		print("DONE! {}/{}".format(cnt, tot))

except FileNotFoundError:
	print('Provided image path is not found')