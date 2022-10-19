from collections import Counter


def symval(i):
    '''
    a supporting function for runnning_cards where 
    it converts each non-number card into its according 
    value to compare the value
    '''
    # i[0] being the first character of each card 
    # e.g : 2, 6, J, Q
    if i[0] == '0':
        return 10
    elif i[0] == 'J':
        return 11
    elif i[0] == 'Q':
        return 12
    elif i[0] == 'K':
        return 13
    elif i[0] == 'A':
        return 1
    else:
        return int(i[0])

def phazed_play(player_id, table, turn_history, phase_status, hand, discard):
    '''
    a function which is a bot to be played in a tournament
    and it will determine which play is the most optimal in a 
    given situation and return that play 
    '''
    # if there is no turn history the player must pick up the card
    if turn_history == []:
        return (1, None)
    # if there is turn history 
    elif turn_history != []:
        # check if there is play history of the player themself
        # if not, must pick up a card to start the turn
        if turn_history[-1][0] != player_id:
            return (1, None)
        else: 
            for i in turn_history:
                # find a list in turn history with the player's ID number
                if i[0] == player_id:
                    # grab the list of plays in the turn history by that player   
                    plays = [x[1] for x in turn_history if x[0] == player_id]
                    # extract and check if the card has been picked up from 
                    # either the discard pile or the deck and create 
                    # a temporary list
                    pick_up = [x for x in plays[0] if x[0] == 1 or x[0] == 2]
                    # if there is a sign of pick ups
                    if(len(pick_up) > 0):
                        # make a play according to one's phase status
                        if phase_status[player_id] == 0:
                            # output a list for phase 1 with 3 same value 
                            # cards in each list
                            new_list = [[k for i in range(v)][:3] for k,
                                        v in Counter(hand).items() if v >= 3]
                            # remove the used cards form the hand
                            for i in new_list:
                                for j in i:
                                    if j in hand:
                                        hand.remove(j)
                            # if there are both lists filled with 3 cards 
                            # each with same value            
                            if len(new_list) == 2:
                                # play the phase
                                return (3, (1, new_list))
                            else:
                                # if not proceed to discarding a highest 
                                # value card from the hand
                                return (5, max(hand, key=lambda x: symval(x)))        
                        else:
                            return (5, max(hand, key=lambda x: symval(x)))
                    else:
                        return (1, None)
                    
                    
if __name__ == '__main__':
    # Example call to the function.
    print(phazed_play(1, [(None, []), (5, [['2C', '3H', '4D', 'AD', '6S', '7C',
      '8S', '9H', '0S', 'JS']]), (None, []), (None, [])], [(0, [(2, 'JS'),
      (5, 'JS')]), (1, [(2, 'JS'), (3, (5, [['2C', '3H', '4D', 'AD', '6S',
      '7C', '8S', '9H']])), (4, ('0S', (1, 0, 8))), (4, ('JS',
      (1, 0, 9)))])], [0, 5, 0, 0], ['5D'], None))
