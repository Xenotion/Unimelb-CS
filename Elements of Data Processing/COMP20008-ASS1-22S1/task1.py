import os
import json

def task1():

    # get the total number of files in the health story folder
    json_article_count = len(os.listdir('/course/data/a1/content/HealthStory'))

    # open the healthstory.json file 
    with open('/course/data/a1/reviews/HealthStory.json') as review_json_file:
        review_json = json.load(review_json_file)

    # count the number of reviews in the file
    json_review_count = len(review_json)
    
    # open tweet.json file
    with open('/course/data/a1/engagements/HealthStory.json') as tweet_json_file:
        tweet_json = json.load(tweet_json_file)
    
    # loop through the dictionary and add all the twitter ids to a temp list
    temp_list = []
    for key, val in tweet_json.items():
        for key2, val2 in val.items():
            for tweets in val2:
                temp_list.append(tweets)
    
    # remove all the redundancy get count the total number of tweet ids in the list
    json_tweet_count = len(set(temp_list))

    # create a dictionary for the output file
    num_count = {
        "Total number of articles": json_article_count,
        "Total number of reviews": json_review_count,
        "Total number of tweets": json_tweet_count
    }

    json_count = json.dumps(num_count, indent = 4)
    
    with open("task1.json", "w") as outfile:
        outfile.write(json_count)      

    return 
