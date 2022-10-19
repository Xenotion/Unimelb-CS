import json
from collections import Counter
import matplotlib.pyplot as plt

def task5():

    # open tweet file and review file
    with open('/course/data/a1/engagements/HealthStory.json') as tweet_json_file:
        tweet_json = json.load(tweet_json_file)

    with open('/course/data/a1/reviews/HealthStory.json') as review_json_file:
        review_json = json.load(review_json_file)
    
    # a list for tweet ids for each article per rating
    tweet_rating_0 = []
    tweet_rating_1 = []
    tweet_rating_2 = []
    tweet_rating_3 = []
    tweet_rating_4 = []
    tweet_rating_5 = []

    # loop through each of the tweet id for each article and append all the tweet id to the list with its corresponding rating
    for (key, val), i in zip(tweet_json.items(), review_json):
        for key2, val2 in val.items():
            for tweet in val2:
                if i['rating'] == 0:
                    tweet_rating_0.append(tweet)
                elif i['rating'] == 1:
                    tweet_rating_1.append(tweet)
                elif i['rating'] == 2:
                    tweet_rating_2.append(tweet)
                elif i['rating'] == 3:
                    tweet_rating_3.append(tweet)
                elif i['rating'] == 4:
                    tweet_rating_4.append(tweet)
                elif i['rating'] == 5:
                    tweet_rating_5.append(tweet)
                else:
                    continue

    # a list with total number of tweets in each rating                
    total_number_of_tweets_per_rating = [len(tweet_rating_0), len(tweet_rating_1),
    len(tweet_rating_2), len(tweet_rating_3), len(tweet_rating_4), len(tweet_rating_5)]

    rating_list = []

    # gain all the rating for each article 
    for i in review_json:
        rating_list.append(i['rating'])
    
    # create a counter dictionary and sort it
    c = Counter(rating_list)

    ordered_dict = dict(sorted(c.items()))

    
    number_of_rating_per_rating = []
    list_of_rating = []
     
    # loop through the dictionary with rating counter to separate and key and value
    for key, val in ordered_dict.items():
        number_of_rating_per_rating.append(val)
        list_of_rating.append(key)

    # gain average number of tweets per rating
    avg_num_tweets = [i / j for i, j in zip(total_number_of_tweets_per_rating, number_of_rating_per_rating)] 
    
    # create a bar graph to compare average number of tweet per rating
    plt.figure(figsize=(18, 8))
    plt.bar(list_of_rating, avg_num_tweets)
    plt.xlabel('Ratings')
    plt.ylabel('Average number of tweets')
    plt.title('Average number of tweets per rating')
    plt.savefig('task5.png', bbox_inches="tight")

    return
