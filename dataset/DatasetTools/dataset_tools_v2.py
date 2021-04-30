import pandas as pd
import numpy as np
from PIL import Image
from numpy import asarray
import os
import matplotlib.pyplot as plt
import math

###0. array[36] map(contains the mapping of labels: indexes are true labels, content is oldValue)
  ##	array[36] histogram(contains the distribution of labels, thus gives an idea about what letters i'm working on)
###1. fun make_hasy_dataset(dataset_path, csv_dataframe)
###2. fun toArray(src_dataset, labels_dataset)
###3. fun shuffle_in_unison_scary(a, b)
###4. fun set_split_percentage()
###5. fun def make_x_y_split(source_img_dataset_array, train_perc, test_perc)
###6. fun print_extractOf_dataset(imgs_array, labels_array, numberOfImages)
###7. fun standardize_labels_forMNIST_inglobation(labels_array, oldLowerBound, offset)



#0. map and histogram arrays
map_array = np.zeros(36)
histogram_array = np.zeros(36)
OFFSET = 0




#1.This function reads the files in the folder and make two lists
#one for the img sources
#one for the labels

##vectors have to be kept parallel, to have the mapping src[i] <-> label[i]
#csv_dataframe has to be entireHasy_detailed.csv
def make_hasy_dataset(dataset_path, csv_dataframe):
	images_hasy = []
	labels_hasy = []
	#print(f"This is the dataset path: {dataset_path}")
	for index, row in csv_dataframe.iterrows():
		path = row['path-to-filename']
		label = row['map-MNIST-label']
		#print(f"Joining {dataset_path} with {path}")
		fullPath = os.path.join(dataset_path, path)
		try:
			img = Image.open(fullPath)
			numpydata = asarray(img)
			images_hasy.append(numpydata)
			labels_hasy.append(label)
		except FileNotFoundError:
			print(f"File not found: {fullPath}")


	print(f"DONE! loaded {len(images_hasy)} images in a numpyarray and {len(labels_hasy)} labels")
	print(f"IMAGES: {type(images_hasy)} {len(images_hasy)} \nLABELS: {type(labels_hasy)} {len(labels_hasy)}")
	return images_hasy, labels_hasy


#will return np.array both of imgs and labels
def toArray(src_dataset, labels_dataset):
	print("np.asarray() ...")
	hasy_imgs_array = np.asarray(src_dataset)

	print("np.asarray() ..")
	hasy_labels_array = np.asarray(labels_dataset)

	print("np.asarray() .")
	print("DONE! here is the report:\nIMAGES:", type(hasy_imgs_array), len(hasy_imgs_array), "\nLABELS: ", type(hasy_labels_array), len(hasy_labels_array))

	return hasy_imgs_array, hasy_labels_array

#performs a parallel shuffle of np.arrays, works inplace
def shuffle_in_unison_scary(a, b):
	print("shuffle_in_unison_scary()...")
	rng_state = np.random.get_state()

	print("shuffle_in_unison_scary() ..")
	np.random.shuffle(a)
	np.random.set_state(rng_state)

	print("shuffle_in_unison_scary().")
	np.random.shuffle(b)
	print("\n\n\n")

#ask the user for input, an integer number between 50 and 100
def get_split_percentage():
	print("Now it's time to split, how do you want to split?")
	train_perc_input = input("Enter the percentage [0-100] of the training\n")
	train_perc_input = int(train_perc_input, base=10)

	assert(train_perc_input >= 50 and train_perc_input <= 100)
	test_perc_input = 100 - train_perc_input
	assert(test_perc_input >= 0 and test_perc_input <= 50)

	print(f'Your splits will be {train_perc_input}-{test_perc_input}\nCall make_x_y_split(...) to create them, passing the return values of this function')
	print("\n\n\n")
	return train_perc_input, test_perc_input

#returns indexes to read the entire_dataset(imgs + labels) as train and test splits
def make_x_y_split(source_img_dataset_array, train_perc):
	test_perc = 100 - train_perc
	entire_dataset_len = len(source_img_dataset_array)

	train_len = (entire_dataset_len * train_perc) / 100
	test_len = (entire_dataset_len * test_perc) / 100

	math.trunc(train_len)
	train_len += 1 #avoid to lose one sample after the division, the choose is to keep it in the training split

	math.trunc(test_len)

	print(f"The dataset len is: {entire_dataset_len}\n TRAIN SPLIT: {train_len} samples\nTEST SPLIT: {test_len}\n\n")

	print("Creating indexes...")

	#the logic is to create one array with len = entire_dataset_len containing:
		#1 if TRAIN sample
		#0 if TEST sample
		#possibility of extension with others number (ex 2 if validation.. but we have to calculate those indexes among training ones)

	#every test_index_ratio iterations, we keep an index for the test set
	test_index_ratio = int(round(entire_dataset_len/effective_test_len))
		
	train_test_indexes = np.zeros(entire_dataset_len)
	tot_train_indexes_no = 0
	tot_test_indexes_no = 0


	for i in range(0, entire_dataset_len):
		
		if i % test_index_ratio == 0:
			#pick for test
			tot_test_indexes_no = 0
			train_test_indexes[i] = 0
		else:
			#pick for train
			tot_train_indexes_no = 0
			train_test_indexes[i] = 1
	print(f"Indexes array created: {train_test_indexes} len: {len(train_test_indexes)}\n train_indexes: {tot_test_indexes_no}\n test indexes:{tot_test_indexes_no}\n\n")

	return train_test_indexes

#support function to visually print dataset 
def print_extractOf_dataset(imgs_array, labels_array, numberOfImages):
	plt.figure(figsize = (10, 10))
	for i in range(int(round(numberOfImages))):
		plt.subplot(m.sqrt(numberOfImages), m.sqrt(numberOfImages), i+1)
		plt.xticks([])
		plt.yticks([])
		plt.grid(False)
		plt.imshow(dataset_array[i], cmap=plt.cm.gray)
	plt.show()
	print(f"Labels Array: {labels_array}")

#takes labels array [31, 45, 53, 56...], oldLowerBound = 31 in our case, offset = 21 in our case
#labels are mapped from [31-56] to [10-36]
def standardize_labels_forMNIST_inglobation(labels_array, oldLowerBound, offset):
	startOld = 31
	endOld = 56
	OFFSET = offset
	for labelValue in labels_array:
			newLabelValue = labelValue - 21
			map_array[newLabelValue] = labelValue 	#save the map
			histogram[newLabelValue] += 1			#count occurrences and construct the histogram

	return map_array, histogram
#returns two arrays, train_labels_mapped and test_labels_mapped
def map_labels(map_array, train_labels_array, test_labels_array):
	train_labels_data = []
	test_labels_data = []
	
	for i in range(0, len(train_labels_array)):
		#index contains a vector of indices of map_array where the value is equal to the
		#actual value to map
		#example: index = 10 if train_labels_array[i] == 31
			#index could assume any of [10-35] 26values
		index = np.where(map_array == train_labels_array[i])
		#create the mapping
		train_labels_data.append(index[0][0])

	
	for i in range(0, len(test_labels_darray)):
		index = np.where(map_array == test_labels_array[i])
		test_labels_data.append(index[0][0])

	assert(max(train_labels_data) <= 36)
	print(max(train_labels_data))
	assert(max(test_labels_data) <= 36)
	print(max(test_labels_data)) 

	return train_labels_data, test_labels_data


def print_mapped_arrays(lowerBound, upperBound, train_array, test_array):
	for i in range(lowerBound, upperBound):
		print(f"TRAIN.  {hasy_train_labels_array_mapped[i]}\n") 
		print(f"TEST.  {hasy_train_labels_array_mapped[i]}\n\n\n")


def max(array_int):
  max = 0
  for e in array_int:
    if e > max:
      max = e
  return max

def plot_histograms(distribution_array):
	plt.hist(distribution_array)
	plt.show()



