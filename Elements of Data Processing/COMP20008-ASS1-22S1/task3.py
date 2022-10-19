import json
import pandas as pd
import os
import glob
from datetime import datetime
from collections import Counter
import matplotlib.pyplot as plt
import numpy as np

def task3():
    
    # create an empty list to store all the necessary data
    df_rows = []

    path = '/course/data/a1/content/HealthStory'

    # loop to open each of the file in the folder
    for filename in glob.glob(os.path.join(path, '*.json')):

        with open(filename) as currentfile:
            current_file = json.load(currentfile)
        
        # obtain the time stamp value in each file, if empty skip
        if current_file['publish_date'] == None:
            continue
        else:
            timestamp = current_file['publish_date']

        # convert timestamp value to more readable format and divide them to year, month and day variable
        total_date = datetime.fromtimestamp(timestamp)
        year = total_date.year
        month = total_date.month
        day = total_date.day

        news_id = currentfile.name
        
        df_rows.append({
                    'news_id' : news_id[36:55],
                    'year' : year,
                    'month' : "{:02d}".format(month),
                    'day' : "{:02d}".format(day)
        })
    
    df = pd.DataFrame(df_rows)
    df = df.sort_values(by=['news_id'], ascending=True)
    
    df.to_csv('task3a.csv', index=False)

    # create a historgram graph with suitable data set
    plt.hist(df['year'])
    plt.xlabel('Year')
    plt.ylabel('Number of Articles')
    plt.title('Number of Articles published every year')
    plt.xticks(np.arange(min(df['year']), max(df['year']) + 1, 1.0))
    plt.savefig('task3b.png')
    
    return
