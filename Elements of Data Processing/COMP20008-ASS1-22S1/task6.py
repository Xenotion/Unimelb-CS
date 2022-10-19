import json
import os
import re
import glob
from nltk.corpus import stopwords
from nltk.tokenize import sent_tokenize, word_tokenize
import time

# text processing function 
def text_processing(text):

    # convert all non-alphabetical characters to spacing characters
    new_string = re.sub(r'[^a-zA-Z\s]+', ' ', text)
    # convert all large spacing characters to single space character
    edited_string = re.sub(r'\s+', ' ', new_string)

    # create a set of english stop words
    stop_words = set(stopwords.words('english'))
    
    # convert the new string to lower case
    edited_string = edited_string.lower()

    # tokenize the new string
    word_tokens = word_tokenize(edited_string)

    new_filtered_sentence = []

    # loop through the tokens and only add the words that aren't stop words or a single character to the new list
    for w in word_tokens:
        if w not in stop_words and len(w) > 1:
            new_filtered_sentence.append(w)

    # return a list of text processed string 
    return list(set(new_filtered_sentence))


def task6():

    path = '/course/data/a1/content/HealthStory'

    dict_list = {}

    # loop through each file in the folder
    for filename in glob.glob(os.path.join(path, '*.json')):

        with open(filename) as currentfile:

            # extract the name of the currently accessed file and string slice
            news_id = currentfile.name[36:55]
            current_file = json.load(currentfile)

            # extract the text section from the file and text process
            text = current_file['text']
            text = text_processing(text)

            # loop through the text processed string and append the news id to the value list if the word
            # already exists if not add the word to the dictionary and add the news id to the value list
            for word in sorted(text):
                if word in dict_list:
                    dict_list[word].append(news_id)
                else:
                    dict_list[word] = []
                    dict_list[word].append(news_id)
    

    final_dict = dict()

    # loop through the dict_list to sort it and append to the new dictionary with sorted value list
    for key in sorted(dict_list):
        final_dict[key] = sorted(dict_list[key])

    with open('task6.json', 'w') as fp:
        json.dump(final_dict, fp)

    # check run time of the program
    start_time = time.time()

    print("--- %s seconds ---" % (time.time() - start_time))

    return
