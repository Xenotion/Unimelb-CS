def phazed_score(hand):
    '''
    this function find the total score of the
    remaining cards in hand
    '''

    # initialise the starting hand score
    hand_score = 0
    # iterate through the hand and add up values 
    # according to their card 
    for i in hand:
        if i[0] == '0':
            hand_score += 10
        elif i[0] == 'A':
            hand_score += 25
        elif i[0] == 'J':
            hand_score += 11
        elif i[0] == 'Q':
            hand_score += 12
        elif i[0] == 'K':
            hand_score += 13
        else:
            hand_score += int(i[0])
    return hand_score

  
if __name__ == '__main__':
    # Example calls to the function.
    print(phazed_score(['9D', '9S', '9D', '0D', '0S', '0D']))
    print(phazed_score(['2D', '9S', 'AD', '0D']))
    print(phazed_score([]))
