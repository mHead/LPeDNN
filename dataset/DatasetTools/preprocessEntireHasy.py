import os
import numpy as np
import pandas as pd
import shutil
import matplotlib.pyplot as plt
import math 



####
image_preprocessing_mode = False
if image_preprocessing_mode:
	import PIL
	from PIL import Image
	import PIL.ImageOps

def preprocess_single_img_hasy_to_mnist(save_desktop, save_desktop_separated, src_img_folder, src_filename, salt_1, salt_2):
	src_filename_tosave = salt_1+salt_2+"_"+src_filename
	save_1 = os.path.join(save_desktop, src_filename_tosave)
	save_2 = os.path.join(save_desktop_separated, src_filename_tosave)
	src = os.path.join(src_img_folder, src_filename)
	if os.path.isfile(src):
		if not src_filename.startswith('.'):
			print(f"\n ***Preprocessing FUNCTION internal print-{src}***\nfilename: {src_filename}\n")
			
			img = Image.open(src)
			resized = img.resize((28, 28))

			invertedImage = PIL.ImageOps.invert(resized)

			grayscaledImage = PIL.ImageOps.grayscale(invertedImage)

			print(f"Going to save:  {save_desktop}\n {save_desktop_separated}")
			grayscaledImage.save(save_1)
			grayscaledImage.save(save_2)


			print(f"DONE! {save_desktop}\n {save_desktop_separated}")
	else:
		print(f"File {src} does not exists")


dictionary = {
	'41' : 'A',
	'42' : 'B',
	'43' : 'C',
	'44' : 'D',
	'45' : 'E',
	'46' : 'F',
	'47' : 'G',
	'48' : 'H',
	'49' : 'I',
	'4a' : 'J',
	'4b' : 'K',
	'4c' : 'L',
	'4d' : 'M',
	'4e' : 'N',
	'4f' : 'O',
	'50' : 'P',
	'51' : 'Q',
	'52' : 'R',
	'53' : 'S',
	'54' : 'T',
	'55' : 'U',
	'56' : 'V',
	'57' : 'W',
	'58' : 'X',
	'59' : 'Y',
	'5a' : 'Z',

}

labels = {
	'A' : 10,
	'B' : 11, 
	'C' : 12, 
	'D' : 13, 
	'E' : 14, 
	'F' : 15, 
	'G' : 16, 
	'H' : 17, 
	'I' : 18, 
	'J' : 19, 
	'K' : 20,
	'L' : 21,
	'M' : 22,
	'N' : 23, 
	'O' : 24,
	'P' : 25, 
	'Q' : 26, 
	'R' : 27, 
	'S' : 28, 
	'T' : 29, 
	'U' : 30, 
	'V' : 31, 
	'W' : 32, 
	'X' : 33, 
	'Y' : 34, 
	'Z' : 35
}

root = r'/Users/head/Desktop/by_field'
save_root = r'/Users/head/Desktop/eMNIST'

alphabet = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
folders_names = ['41', '42','43','44', '45', '46', '47', '48', '49', '4a', '4b', '4c', '4d', '4e', '4f', '50', '51', '52', '53', '54', '55', '56', '57', '58', '59', '5a']


datasetSlicesDirs = 6
dataset_slices = ['0','1', '2', '3', '4', '6', '7']


save_imgs_Letter_path = ''
detailed_dataset_info_csv = os.path.join(save_root, 'entireHasy_detailed.csv')
general_dataset_info_csv = os.path.join(save_root, 'entireHasy_info-general.csv')
slice_cnt = 0
dir_cnt = 0


letter_distribution = np.zeros(26) #index has to be calculated as (label - 10) of offset

###offsets
s_offset = 21
l_offset = 10



path_to_filename = r'/Users/head/Dropbox\ \(Politecnico\ Di\ Torino\ Studenti\)/Apps/LPeDNN/entireHasy_src_img'
path_to_desktop = r'/Users/head/Desktop/entireHasy_src_img'
relativeHasyPath = r'/entireHasy_src_img'

##general info.csv [index, symbol_id, latex, map-MNIST-label, globalTotal]
general_data = pd.DataFrame(np.inf, index=['index'], columns=['symbol_id', 'latex', 'map-MNIST-label', 'globalTotal']) #one line per letter
detailed_data = pd.DataFrame(np.inf, index=['index'], columns=['path-to-filename','symbol_id', 'latex', 'map-MNIST-label', 'slice']) #one line per jpg

for slice in dataset_slices: #ie for each slice inside /by_field/ -> construct hsf_1, hsf_2 ..
	#slice_cnt += 1
	#dir_cnt = 0
	#print(slice)
	hsf_i_folder = 'hsf_'+slice
	print(hsf_i_folder)

	hsf_i_root = os.path.join(root, hsf_i_folder)
	hsf_i_save_root = os.path.join(save_root, hsf_i_folder)

	upper_folder = os.path.join(hsf_i_root, 'upper')
	print(upper_folder)


	for dir in os.listdir(upper_folder): # 
		if not dir.startswith('.'):
			data = []
			file_cnt = 0
			#print(f"before assert ******* {dir}*******START\n")
			assert(dir in folders_names)
			#print(f"after assert ******* {dir}*******END\n")
			letter = dictionary.get(dir)
			save_imgs_Letter_path = os.path.join(hsf_i_save_root, letter)
			#print("\n\n\n\n\n\n")
			#print(f"I'm working for the folder of letter: {letter}\n")
			#print(f">>>OVERWRITE WARNING: I'm going to create the folder {save_imgs_Letter_path}")
			
			#if os.path.exists(save_imgs_Letter_path):
			#	shutil.rmtree(save_imgs_Letter_path)
			

			#os.mkdir(save_imgs_Letter_path)
			#print(f"---------{slice_cnt}**{upper_folder},{dir} ---- {dir_cnt}**{dir}")	
			dir_cnt += 1
			img_folder = os.path.join(upper_folder, dir)
			#print(f"IMAGE FOLDER IS: ---------->>>>> {img_folder}\n")


			for file in os.listdir(img_folder):				
				file_cnt += 1
				path_png_for_csv = os.path.join(path_to_filename, slice+letter+file)
				csv_path = os.path.join(relativeHasyPath, slice+letter+file)
				#print(f"{path_png} {labels.get(letter) + s_offset} {letter} {labels.get(letter)} {slice}")
				real_src_path = os.path.join(img_folder, file)
				if image_preprocessing_mode:
					##here begins the preprocessing, only to do one time
					#save_imgs_Letter_path = save_root/hsf_i_save_root/letter : /Users/head/Desktop/eMNIST  /  hsf_i  /  letter '
					#path_png:  /entireHasy_src_img/slice+letter+file.png
					#real_src_path: /Users/head/Desktop/by_field/hsf_i/upper/letter
					#path_png_for_csv: will be the name associated with the label, save in that path, to join: entireHasy_src_img/file
					save_path = os.path.join(save_imgs_Letter_path, path_png_for_csv)
					csv_path = os.path.join(relativeHasyPath, slice+letter+file)
					print(f" ***Preprocessing start before call\n***")
					print(f" ***save to: {path_to_desktop}\nsave to: {save_imgs_Letter_path}\ngiving as source: {img_folder}, {slice+letter+file}***")


					preprocess_single_img_hasy_to_mnist(path_to_desktop, save_imgs_Letter_path, img_folder, file, slice, letter)
					print(f" ***\nPreprocessing end after call***")


				data.append([csv_path, int(labels.get(letter)) + s_offset, letter, int(labels.get(letter)), slice])
				data = pd.DataFrame(data, columns=['path-to-filename', 'symbol_id', 'latex', 'map-MNIST-label', 'slice'])
				detailed_data = detailed_data.append(data, ignore_index=True)
				#detailed_data.head()
				#print(f"{img_folder}, {dir}, {file} {file_cnt}\n")

			letter_distribution[labels.get(letter) - l_offset] += file_cnt #update the distribution at folder rate
			#print(f"******There is an amount of {file_cnt}/{len(img_folder)} latex: {letter} with map-MNIST-label: {labels.get(letter)} in folder {upper_folder}\n\n")
			#localFolder_level_data = pd.DataFrame(localFile_level_data, columns=['slice_no', 'filename', 'symbol_id', 'latex', 'map-MNIST-label', 'cumulative_total'])

			#info_df = pd.DataFrame(data, columns=['slice_no', 'filename', 'symbol_id', 'latex', 'map-MNIST-label', 'cumulative_total'])
			#data.append(info_df)


print(f"**LETTER DISTRIBUTION: \n\n{letter_distribution}\n\n")
#detailed_data.head()
data = []
for i in range(0, len(letter_distribution)):
	
	symbol_id = labels.get(alphabet[i]) + s_offset
	latex = alphabet[i]
	mapLabel = int(symbol_id - s_offset)
	globalTotal = int(letter_distribution[i])
	data.append([symbol_id, latex, mapLabel, globalTotal])
	#print(f"{data}")

data = pd.DataFrame(data, columns=['symbol_id', 'latex', 'map-MNIST-label', 'globalTotal'])
general_data = general_data.append(data, ignore_index=True)

general_data.to_csv(general_dataset_info_csv)
detailed_data.to_csv(detailed_dataset_info_csv)

print(general_data.head()) ##tosave
print("\n\n")
print(detailed_data.head())

plt.bar(alphabet,letter_distribution,align='center')
plt.xlabel('Letters')
plt.ylabel('nLetters')
#for i in range(len(letter_distribution)):
 #   plt.hlines(letter_distribution[i], 0, alphabet[i]) # Here you are drawing the horizontal lines
plt.show()
#plt.hist(letter_distribution, bins=26)
#plt.show()
#plt.bars(letter_distribution)
print(f"{slice_cnt} ---- {dir_cnt}")
	#for letter in alphabet:
#		print(working for letter: {letter})
#		os.path.join()