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
    else:
        return int(i[0])

def revsymval(val):
    '''
    reverting the value of the face cards that has been 
    converted in the previous function so the card remains 
    with its original value
    '''
    if val == 13:
        return 'K'
    elif val == 11:
        return 'J'
    elif val == 12:
        return 'Q'
    elif val == 10:
        return '0'
    else:
        return str(val)

def running_cards(play):
    '''
    function used to find out whether the sets of card is running
    this is for play-style 3
    '''
    normcard = []
    aces = []

    # separating the value cards from ace cards
    for card in play[1][1]:
        if card[0] == 'A':
            aces.append(card)
        else:
            normcard.append(card)

    # sort the value cards in an order of its values
    normcard.sort(key=lambda x: symval(x))

    # if there are no normal cards return nothing
    if len(normcard) == 0:
        return []
    else:
        # while iterating through the value cards
        # append an ace card everytime the two adjacent 
        # cards do not subtract to 1. 
        potseq = [normcard.pop(0)]

        while(len(normcard) > 0):
            if(symval(potseq[-1]) == 13):
                break
            elif(symval(normcard[0]) - symval(potseq[-1]) == 1):
                potseq.append(normcard.pop(0))
            elif(len(aces) > 0):
                potseq.append(revsymval(symval(potseq[-1]) + 1))
                aces.pop()
            else:
                break
        
        # after all the adding if there still are aces left over
        # append all of them to one end of the list
        if len(aces) != 0:
            for i in aces:
                potseq.insert(0, i)

    return potseq

def running_cards2(play):
    '''
    function used to find out whether the sets of card is running
    this is for play-style 4
    '''
    normcard = []
    aces = []

    # separating the value cards from ace cards
    for card in play:
        if card[0] == 'A':
            aces.append(card)
        else:
            normcard.append(card)

    # sort the value cards in an order of its values
    normcard.sort(key=lambda x: symval(x))

    # if there are no normal cards return nothing
    if len(normcard) == 0:
        return []
    else:
        # while iterating through the value cards
        # append an ace card everytime the two adjacent 
        # cards do not subtract to 1. 
        potseq = [normcard.pop(0)]

        while(len(normcard) > 0):
            if(symval(potseq[-1]) == 13):
                break
            elif(symval(normcard[0]) - symval(potseq[-1]) == 1):
                potseq.append(normcard.pop(0))
            elif(len(aces) > 0):
                potseq.append(revsymval(symval(potseq[-1]) + 1))
                aces.pop()
            else:
                break
        
        # after all the adding if there still are aces left over
        # append all of them to one end of the list
        if len(aces) != 0:
            for i in aces:
                potseq.insert(0, i)

    return potseq

def accumulation_list_1(play):
    '''finding accumulation of the first list in play-style 3'''
    accumulation_1 = 0
    for i in play[1][1][0]:
        if i[0] == '0':
            accumulation_1 += 10
        elif i[0] == 'A':
            accumulation_1 += 1
        elif i[0] == 'J':
            accumulation_1 += 11
        elif i[0] == 'Q':
            accumulation_1 += 12
        elif i[0] == 'K':
            accumulation_1 += 13
        else:
            accumulation_1 += int(i[0])
        
    return accumulation_1

def accumulation_list_2(play):
    '''finding accumulation of the second list in play-style 3'''
    accumulation_2 = 0
    # only if the input list has two lists
    if len(play[1][1]) == 2:
        for i in play[1][1][1]:
            if i[0] == '0':
                accumulation_2 += 10
            elif i[0] == 'A':
                accumulation_2 += 1
            elif i[0] == 'J':
                accumulation_2 += 11
            elif i[0] == 'Q':
                accumulation_2 += 12
            elif i[0] == 'K':
                accumulation_2 += 13
            else:
                accumulation_2 += int(i[0])
    else:
        None 

    return accumulation_2

def accumulation_list_3(table):
    '''finding accumulation of the first list in play-style 4'''
    accum_3 = 0
    for i in table:
        if i[0] == 3:
            for j in i[1][0]:
                if j[0] == '0':
                    accum_3 += 10
                elif j[0] == 'A':
                    accum_3 += 1
                elif j[0] == 'J':
                    accum_3 += 11
                elif j[0] == 'Q':
                    accum_3 += 12
                elif j[0] == 'K':
                    accum_3 += 13
                else:
                    accum_3 += int(j[0])
        
    return accum_3

def accumulation_list_4(table):
    '''finding accumulation of the second list in play-style 4'''
    accum_4 = 0
    for i in table:
        if i[0] == 3:
            # only if the input list has two lists
            if len(i[1]) == 2:
                for j in i[1][1]:
                    if j[0] == '0':
                        accum_4 += 10
                    elif j[0] == 'A':
                        accum_4 += 1
                    elif j[0] == 'J':
                        accum_4 += 11
                    elif j[0] == 'Q':
                        accum_4 += 12
                    elif j[0] == 'K':
                        accum_4 += 13
                    else:
                        accum_4 += int(j[0])
    else:
        None 

    return accum_4

def phazed_is_valid_play(play, player_id, table, turn_history, phase_status, 
                         hand, discard):
    '''
    a whole function which determines the validity 
    of the play according to a situation
    '''
     
    black = ['C', 'S']
    red = ['H', 'D']

    # section for play-style 3 which is actually playing the phase
    if play[0] == 3:
        accumulation_1 = accumulation_list_1(play)
        accumulation_2 = accumulation_list_2(play)
        # checking if the player playing has already picked up the card
        if player_id == turn_history[0] and turn_history[1][0] == 1 or 2:
            # checking if the phase that the player is trying to play 
            # is the phase they have to play from the phase status
            # phase 1
            if play[1][0] == 1 and int(phase_status[player_id]) + 1:
                # checking if the input is valid using counter
                count_for_1 = 0
                for i in play[1][1]:
                    if len(i) == 3:
                        if len(set([x[0] for x in i if x[0] != 'A'])) == 1:
                            count_for_1 += 1
                        # if the input is valid
                        if count_for_1 == 2:
                            # check if all the cards are in hand
                            set1 = set(play[1][1][0])
                            set2 = set(play[1][1][1])
                            set3 = set(hand)
                            if set1.issubset(set3) and set2.issubset(set3):
                                return True

            # checking for phase 2
            elif play[1][0] == 2 and int(phase_status[player_id]) + 1:
                for i in play[1]:
                    # check if all cards have the same suit
                    if len(set([x[1] for x in i if x[0] != 'A'])) == 1:
                        # check if all the cards are in hand
                        set1 = set(play[1][1])
                        set2 = set(hand)
                        if set1.issubset(set2):
                            return True

            # checking for phase 3
            elif play[1][0] == 3 and int(phase_status[player_id]) + 1:
                # check if both lists in input add up to 34
                if accumulation_1 & accumulation_2 == 34:
                    # if yes check if all the cards are in hand
                    set1 = set(play[1][1][0])
                    set2 = set(play[1][1][1])
                    set3 = set(hand)
                    if set1.issubset(set3) and set2.issubset(set3):
                        return True

            # checking for phase 4
            elif play[1][0] == 4 and int(phase_status[player_id]) + 1:
                # checking if the input is valid using counter
                count_for_4 = 0
                for i in play[1][1]:
                    if len(i) == 4:
                        if len(set([x[0] for x in i if x[0] != 'A'])) == 1:
                            count_for_4 += 1
                        # if both lists have 4 cards are have the same value
                        if count_for_4 == 2:
                            # check if all the cards are in hand
                            set1 = set(play[1][1][0])
                            set2 = set(play[1][1][1])
                            set3 = set(hand)
                            if set1.issubset(set3) and set2.issubset(set3):
                                return True
            
            # checking for phase 5
            elif play[1][0] == 5 and int(phase_status[player_id]) + 1:
                # checking if there are eight cards in the list
                if len(play[1][1]) == 8:
                    for i in play[1][1]:
                        # check if its a run
                        run_card = running_cards(i)
                        if len(i) == len(run_card):
                            # check if all the cards are in hand
                            set1 = set(play[1][1])
                            set2 = set(hand)
                            if set1.issubset(set2):
                                return True

            # checking for phase 6
            elif play[1][0] == 6 and int(phase_status[player_id]) + 1:
                # cehcking if both lists add up to 34
                if accumulation_1 & accumulation_2 == 34:
                    for i in play[1][1]:
                        # creating a temporary list without aces
                        list_no_ace = [x for x in i if x[0] != 'A']   
                        # check if they are all black  
                        if all(x[1] in black for x in list_no_ace):
                            # check if all cards are in hand 
                            set1 = set(play[1][1][0])
                            set2 = set(play[1][1][1])
                            set3 = set(hand)
                            if set1.issubset(set3) and set2.issubset(set3):
                                return True
                        # check if all card are red
                        elif all(x[1] in red for x in list_no_ace):
                            # chekc if all cards are in hand
                            set1 = set(play[1][1][0])
                            set2 = set(play[1][1][1])
                            set3 = set(hand)
                            if set1.issubset(set3) and set2.issubset(set3):
                                return True

            # check for phase 7
            elif play[1][0] == 7 and int(phase_status[player_id]) + 1:
                # set up a counter
                count_for_7 = 0
                for i in play[1][1]:
                    # check if each of them have 4 cards each 
                    if len(i) == 4:
                        run_card = running_cards(i)
                        # check if one of the list is a list 
                        # with 4 same value cards
                        if len(set([x[0] for x in i if x[0] != 'A'])) == 1:
                            # create temp list with no aces
                            list_no_ace = [x for x in i if x[0] != 'A']  
                            # if all the card are black  
                            if all(x[1] in black for x in list_no_ace):
                                set1 = set(play[1][1][0])
                                set2 = set(play[1][1][1])
                                set3 = set(hand)
                                # if all cards are in hand
                                if set1.issubset(set3) and set2.issubset(set3):
                                    # increase the count
                                    count_for_7 += 1
                            # if all the cards are red
                            elif all(x[1] in red for x in list_no_ace):
                                set1 = set(play[1][1][0])
                                set2 = set(play[1][1][1])
                                set3 = set(hand)
                                # if all the cards are in hand
                                if set1.issubset(set3) and set2.issubset(set3):
                                    # increase the count
                                    count_for_7 += 1
                            else:
                                None

                        # select the one that does not have 
                        # the same value and same colour
                        if count_for_7 == 0:
                            # check if the list is a run
                            if len(i) == len(run_card):
                                set1 = set(play[1][1][0])
                                set2 = set(play[1][1][1])
                                set3 = set(hand)
                                # check if they are in hand
                                if set1.issubset(set3) and set2.issubset(set3):
                                    return True

    # section for play-style 4 which is playing cards onto groups
    elif play[0] == 4:  
        # declare all the variables according to their indexes
        play_card = play[1][0]   
        play_table_no_index = play[1][1][0]
        group_to_be_played = play[1][1][1]
        index_to_be_played = play[1][1][2]
        player_no = table[play_table_no_index]
        phase_num_of_play = player_no[0]
        list_of_phase = table[play_table_no_index][1]
        first_element_of_the_group = list_of_phase[group_to_be_played][0]
        first_char_of_the_group= first_element_of_the_group[0]
        second_char_of_the_group = first_element_of_the_group[1]
        
        # check if the play card is valid
        if play_card in hand:
            # adding onto a phase 1
            if int(phase_num_of_play) == 1:
                # check if the number of the play card and 
                # the group card is the same
                if play_card[0] == first_char_of_the_group:
                    return True
                # if its ace automatically correct
                elif play_card[0] == 'A':
                    return True
                else:
                    return False

            # adding onto a phase 2
            elif int(phase_num_of_play) == 2:
                # check if the suit of the play card is the same as the group
                if play_card[1] == second_char_of_the_group:
                    return True
                # if its ace automatically correct
                elif play_card[0] == 'A':
                    return True
                else:
                    return False

            # adding onto a phase 3
            elif int(phase_num_of_play) == 3:
                
                # check the total value of the original list 
                accumulation = 0
                for i in list_of_phase[group_to_be_played]:
                    if i[0] == '0':
                        accumulation += 10
                    elif i[0] == 'A':
                        accumulation += 1
                    elif i[0] == 'J':
                        accumulation += 11
                    elif i[0] == 'Q':
                        accumulation += 12
                    elif i[0] == 'K':
                        accumulation += 13
                    else:
                        accumulation += int(i[0])

                # check the value of the play card
                value = 0
                if play_card[0] == '0':
                    value += 10
                elif play_card[0] == 'A':
                    value += 1
                elif play_card[0] == 'J':
                    value += 11
                elif play_card[0] == 'Q':
                    value += 12
                elif play_card[0] == 'K':
                    value += 13
                else:
                    value += int(play_card[0])

                # in a reverse fibonnacci scale
                # if the original list adds upto 34
                # make sure the play cards being add onto 
                # will create a total sum of equal or 
                # less than the next fibonnaci scale sum
                if accumulation <= 34:
                    if accumulation + value <= 55:
                        return True
                    else:
                        return False
                elif accumulation <= 55:
                    if accumulation + value <= 68:
                        return True
                    else:
                        return False
                elif accumulation <= 68:
                    if accumulation + value <= 76:
                        return True
                    else:
                        return False 
                elif accumulation <= 76:
                    if accumulation + value <= 81:
                        return True 
                    else:
                        return False
                elif accumulation <= 81:
                    if accumulation + value <= 84:
                        return True 
                    else:
                        return False
                elif accumulation <= 84:
                    if accumulation + value <= 86:
                        return True
                    else:
                        return False
                elif accumulation <= 86:
                    if accumulation + value <= 87:
                        return True 
                    else:
                        return False

            # adding onto a phase 4
            elif int(phase_num_of_play) == 4:
                # check if the number of the play card and 
                # the group card is the same
                if play_card[0] == first_char_of_the_group:
                    return True
                # if its ace automatically correct
                elif play_card[0] == 'A':
                    return True
                else:
                    return False
            
            # adding onto a phase 5
            elif int(phase_num_of_play) == 5:
                # grab the list which the play card is going to be added
                run = list_of_phase[group_to_be_played]
                # add the card onto the correct position
                run.insert(int(index_to_be_played), play_card)
                # check if the list is a run
                run_cards = running_cards2(run)
                # compare the length of the original and the modified list 
                if len(run) == len(run_cards):
                    return True
                else:
                    return False

            # adding onto a phase 6
            elif int(phase_num_of_play) == 6:
                # check if the play card matches the colour 
                # of the group to be added onto
                if play_card[1] and second_char_of_the_group in red or black:
                    # check the accumulation 
                    accumulation = 0
                    for i in list_of_phase[group_to_be_played]:
                        if i[0] == '0':
                            accumulation += 10
                        elif i[0] == 'A':
                            accumulation += 1
                        elif i[0] == 'J':
                            accumulation += 11
                        elif i[0] == 'Q':
                            accumulation += 12
                        elif i[0] == 'K':
                            accumulation += 13
                        else:
                            accumulation += int(i[0])

                    # check the numerical value of the play card 
                    value = 0
                    if play_card[0] == '0':
                        value += 10
                    elif play_card[0] == 'A':
                        value += 1
                    elif play_card[0] == 'J':
                        value += 11
                    elif play_card[0] == 'Q':
                        value += 12
                    elif play_card[0] == 'K':
                        value += 13
                    else:
                        value += int(play_card[0])

                    # in a reverse fibonnacci scale
                    # if the original list adds upto 34
                    # make sure the play cards being add onto 
                    # will create a total sum of equal or 
                    # less than the next fibonnaci scale sum
                    if accumulation <= 34:
                        if accumulation + value <= 55:
                            return True
                        else:
                            return False
                    elif accumulation <= 55:
                        if accumulation + value <= 68:
                            return True
                        else:
                            return False
                    elif accumulation <= 68:
                        if accumulation + value <= 76:
                            return True
                        else:
                            return False 
                    elif accumulation <= 76:
                        if accumulation + value <= 81:
                            return True 
                        else:
                            return False
                    elif accumulation <= 81:
                        if accumulation + value <= 84:
                            return True 
                        else:
                            return False
                    elif accumulation <= 84:
                        if accumulation + value <= 86:
                            return True
                        else:
                            return False
                    elif accumulation <= 86:
                        if accumulation + value <= 87:
                            return True 
                        else:
                            return False

    # play-style 5 which is discarding a card 
    elif play[0] == 5:
        accum_3 = accumulation_list_3(table)
        accum_4 = accumulation_list_4(table)
        # list of accumulations that must be met before discarding
        list_of_accum = [34, 55, 68, 76, 81, 84, 86, 87]
        play_card = play[1]
        # check if the play card is in the hand
        if play_card in hand:
            # iterate through the turn history
            for i in turn_history:
                # find the one that matches the player id
                if int(i[0]) == int(player_id):
                    for j in i[1]:
                        # check if the player has picked up the card
                        if j[0] == 1:
                            # check if the phase was accumulation
                            if table[player_id][0] == 3:
                                # check if accumulation adds up to 'complete'
                                if accum_3 & accum_4 in list_of_accum:
                                    return True
                                else:
                                    return False
                            else:
                                return True   
                        # check if they have already discarded the card 
                        elif j[0] == 5:
                            return False    
                        else:
                            return False        
                                        
        
if __name__ == '__main__':
    # Example calls to the function.
    print(phazed_is_valid_play((3, (1, [['2S', '2S', '2C'],
        ['AS', '5S', '5S']])), 0, [(None, []), (None, []),
        (None, []), (None, [])], [(0, [(2, 'JS')])],
        [0, 0, 0, 0], ['AS', '2S', '2S', '2C', '5S', '5S',
                       '7S', '8S', '9S', '0S', 'JS'], None))
    print(phazed_is_valid_play((4, ('KC', (1, 0, 0))),
        1, [(None, []), (2, [['2S', '2S', 'AS', '5S',
        '5S', '7S', 'JS']]), (None, []), (None, [])],
        [(0, [(2, 'JS'), (5, 'JS')]), (1, [(1, 'XX'),
        (3, (2, [['2S', '2S', 'AS', '5S', '5S', '7S', 'JS']]))])],
        [0, 2, 0, 0], ['5D', '0S', 'JS', 'KC'], 'JS'))
    print(phazed_is_valid_play((5, 'JS'), 1, [(None, []),
        (1, [['2S', '2S', '2C'], ['AS', '5S', '5S']]),
        (None, []), (None, [])], [(0, [(2, 'JS'),
        (5, 'JS')]), (1, [(1, 'XX'), (3, (1, [['2S', '2S',
        '2C'], ['AS', '5S', '5S']]))])], [0, 1, 0, 0],
        ['AD', '8S', '9S', '0S', 'JS'], 'JS'))
