import pandas as pd
import json
import csv

def task2():

    # create an empty list to store all the output data 
    df_rows = []

    # open review file
    with open('/course/data/a1/reviews/HealthStory.json') as review_json_file:
        review_json = json.load(review_json_file)

    # extract all the wanted data from the file
    for review in review_json:
        news_id = review['news_id']
        news_title = review['title']
        review_title = review['original_title']
        rating = review['rating']
        
        num_satisfactory = 0

        # loop to count the total number of Satisfactory per review
        for sat in review['criteria']:
            if sat['answer'] == "Satisfactory":
                num_satisfactory += 1

        # append all the elements to the list
        df_rows.append({
                'news_id' : news_id,
                'news_title' : news_title,
                'review_title' : review_title,
                'rating' : rating,
                'num_satisfactory' : num_satisfactory
            })
    
    df = pd.DataFrame(df_rows)
    
    df.to_csv('task2.csv', index=False)

    
    return
