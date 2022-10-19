import json
import math
import pandas as pd
import time
import matplotlib.pyplot as plt

# function to count total number of articles in review file
def total_number_of_articles():
    with open('/course/data/a1/reviews/HealthStory.json') as review_json_file:
        review_json = json.load(review_json_file)
    
    articles = []

    # loop through the review file and add all the news id to an empty list
    for i in review_json:
        articles.append(i['news_id'])
    
    # return the length of the list with all the news ids
    return len(articles)

def task7():

    # create an empty list to add all the necessary data
    df_rows = []
    total = total_number_of_articles()

    with open('/course/data/a1/reviews/HealthStory.json') as review_json_file:
        review_json = json.load(review_json_file)
        
        num_fake_news = 0
        num_real_news = 0

        # loop through the review file to count the number fake/real articles depending on the rating
        for category in review_json:
            if category['rating'] >= 3:
                num_real_news += 1
            else:
                num_fake_news += 1
    
    # use the task6.json file for the function below
    with open('/home/task6.json') as json_file:

        json_file = json.load(json_file)

        # loop through task6 json file
        for words, articles in json_file.items():

            num_real_articles_with_w = 0
            num_fake_articles_with_w = 0

            # only deal with words that appear in 10 or more articles or that does not appear in every single article
            if len(articles) >= 10 or not total:

                # loop through each article in the articles list per word
                for article in articles:
                    
                    # for each news id in the list per word, loop through the review file and if the news id match and 
                    # rating is 3 or above increase number of real articles 
                    for category in review_json:
                        if article == category['news_id'] and category['rating'] >= 3:
                            num_real_articles_with_w += 1
                        elif article == category['news_id'] and category['rating'] < 3:
                            num_fake_articles_with_w += 1
                
                # calculate probability of a word appearing in a real news
                prob_w_in_real = num_real_articles_with_w / num_real_news  

                # if the probability isnt 1 or 0, calculate the odds 
                if prob_w_in_real != 0.0 and 1.0:
                    odds_real = prob_w_in_real / (1 - prob_w_in_real)
                else:
                    continue
                
                # same as above but for fake articles
                prob_w_in_fake = num_fake_articles_with_w / num_fake_news   

                # calculate odds for fake articles
                if prob_w_in_fake != 0.0 and 1.0:
                    odds_fake = prob_w_in_fake / (1 - prob_w_in_fake)
                else:
                    continue
                
                # calculate odds ratio of fake to re
                odds_ratio = odds_fake / odds_real
                
                # log the odds ratio and round the value to 5dp
                log_odds_ratio = math.log(odds_ratio, 10)
                log_odds_ratio = round(log_odds_ratio, 5)

                df_rows.append({
                        'word' :  words,
                        'log_odds_ratio' : log_odds_ratio
                })
    
    df = pd.DataFrame(df_rows)
    df = df.sort_values(by=['word'], ascending=True)
    df.to_csv('task7a.csv', index=False)
    
    # create a histogram for frequency of each odds rat
    plt.hist(df['log_odds_ratio'])
    plt.xlabel('Log Odds Ratio')
    plt.ylabel('Frequency')
    plt.title('Log Odds Ratio Distribution')
    plt.savefig('task7b.png', bbox_inches="tight")
    plt.close()
    
    # sort the dataframe by odds ratio value
    df = df.sort_values(by=['log_odds_ratio'], ascending=True)

    word_list = []
    log_odds_ratio_list = []
    
    # loop theough the data frame to gather top and bottom 15 data set
    for i in df['word'].head(15):
        word_list.append(i)
    
    for i in df['word'].tail(15):
        word_list.append(i)

    for i in df['log_odds_ratio'].head(15):
        log_odds_ratio_list.append(i)
    
    for i in df['log_odds_ratio'].tail(15):
        log_odds_ratio_list.append(i)

    # create a bar graph to compare odds ratio of the top\bottom 15 words in the data frame
    plt.bar(word_list, log_odds_ratio_list)
    plt.xticks(range(len(word_list)), word_list, rotation='vertical')
    plt.xlabel('Words')
    plt.ylabel('Odds Ratio')
    plt.title('Top/Bottom 15 Odds Ratio')
    plt.savefig('task7c.png', bbox_inches="tight")
    
    # run time program
    start_time = time.time()

    print("--- %s seconds ---" % (time.time() - start_time))

    return
