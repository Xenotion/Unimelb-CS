import json
import pandas as pd
from collections import Counter
import matplotlib.pyplot as plt

def task4():

    # create an empty list to contain all the necessary data
    df_rows = []

    # open the review file
    with open('/course/data/a1/reviews/HealthStory.json') as review_json_file:
        review_json = json.load(review_json_file)

    # create a temporary list and add all the news source for each review
    temp_list = []
    for items in review_json:
        if(items['news_source'] == ''):
            continue
        else:
            temp_list.append(items['news_source'])
    
    # create a counter dictionary and sort it
    c = Counter(temp_list)
    sorted_dict = sorted(c.items())
    

    articles_list = []
    num_articles_list = []

    # loop through the dictoinary to separate the articles and their count
    for key, val in dict(sorted_dict).items():
        articles_list.append(key)
        num_articles_list.append(val)

    total_rating_list = []

    # loop through the original review file to gather rating of each news source
    for key in articles_list:
        total_rating = 0
        for items in review_json:
            if key == items['news_source']:
                total_rating += items['rating']
            else:
                continue

        total_rating_list.append(total_rating)

    # find average rating for each news sources
    avg_rating = [i / j for i, j in zip(total_rating_list, num_articles_list)]    
    
    # append all the necessary data
    for i, j, k in zip(articles_list, num_articles_list, avg_rating):
        df_rows.append({
                    'news_source' : i,
                    'num_articles' : j,
                    'avg_rating' : k
        })

    df = pd.DataFrame(df_rows)
    
    df.to_csv('task4a.csv', index=False)

    temp_dict = {}

    # only add articles with 5 or more articles to new temporary dictionary 
    for i, j, k in zip(articles_list, num_articles_list, avg_rating):
        if j >= 5:
            temp_dict[i] = k

    # sort the dictionary
    temp_dict =  dict(sorted(temp_dict.items(), key=lambda x: x[1], reverse=True))

    # separate the key and value from dictionary
    label = list(temp_dict.keys())
    value = list(temp_dict.values())
    
    # create a bar graph to show average rating for each news agency with more than 5 articles
    plt.figure(figsize=(18, 8))
    plt.bar((range(len(temp_dict))), value, tick_label = label, align='center', width=0.5)
    plt.xticks(range(len(temp_dict)), temp_dict, rotation='vertical')
    plt.xlabel('News Angency')
    plt.ylabel('Average Rating')
    plt.title('Average ratings of all news sources, that have at least 5 articles')
    plt.savefig('task4b.png', bbox_inches="tight")

    return
