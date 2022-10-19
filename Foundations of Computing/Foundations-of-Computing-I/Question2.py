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

def running_cards(phase):
    '''
    function used to find out whether the sets of card is running
    '''
    normcard = []
    aces = []

    # separating the value cards from ace cards
    for card in phase:
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

def number_cards_list_1(phase):
    '''counts how many value cards there are in the first list'''
    # loop through the group and count every card that 
    # doesn't start with an A
    count = 0
    for i in phase[0]:
        if i[0] != 'A':
            count += 1
    
    return count
        
def number_cards_list_2(phase):
    '''counts how many value cards there are in the second list'''
    # loop through the group and count every card that 
    # doesn't start with an A
    count = 0
    if len(phase) == 2:
        for i in phase[1]:
            if i[0] != 'A':
                count += 1
    
    return count

def accumulation_list_1(phase):
    '''calculate the accumulation of the first list'''
    accumulation_1 = 0
    for i in phase[0]:
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

def accumulation_list_2(phase):
    '''calculate the accumulation of the second list'''
    accumulation_2 = 0
    if len(phase) == 2:
        for i in phase[1]:
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

def phazed_phase_type(phase):
    '''function that identifies what phases the following inputs,
    which consists of one or two lists are'''
    phase_list = []

    black = ['C', 'S']
    red = ['H', 'D']
    
    list1_numcards = number_cards_list_1(phase)
    list2_numcards = number_cards_list_2(phase)
    accumulation_1 = accumulation_list_1(phase)
    accumulation_2 = accumulation_list_2(phase)

    # check if the input lits isn't empty
    if len(phase) > 0:
        # if there are two lists
        if len(phase) == 2:
            # initialise counters
            count_for_1 = 0
            count_for_4 = 0
            for i in phase:
                run_card = running_cards(i)

                # if a list has three cards in it
                if len(i) == 3:
                    # check if both lists have more than 2 value cards
                    if list1_numcards & list2_numcards >= 2:
                        # check if a list has cards with all the same numbers
                        if len(set([x[0] for x in i if x[0] != 'A'])) == 1:
                            # add one to the counter
                            count_for_1 += 1
                        else:
                            None
                
                # if both lists satisfy the requirement 
                if count_for_1 == 2:
                    # it's phase 1
                    phase_list.append(1)
                else:
                    None

                # if a list has four cards in it
                if len(i) == 4:
                    # check if both lists have more than 2 value cards
                    if list1_numcards & list2_numcards >= 2:
                        # check if a list has cards with all the same numbers
                        if len(set([x[0] for x in i if x[0] != 'A'])) == 1:
                            # add one to the counter
                            count_for_4 += 1
                        else:
                            None

                    # if both lists satisfy the requirement
                    if count_for_4 == 2:
                        # it's phase 4
                        phase_list.append(4)
                    # if not grab the one that doesn't satisfy the requirement
                    elif count_for_4 == 0: 
                        # check if the list is a run by comparing the
                        # length of the modified list from running_cards
                        # and the original list
                        if len(i) == len(run_card):
                            # create a temp list with no aces
                            list_no_ace = [x for x in i if x[0] != 'A']
                            # if all the cards are black
                            if all(x[1] in black for x in list_no_ace):
                                # then it's phase 7 overall
                                phase_list.append(7)
                            # if all the cards are red
                            elif all(x[1] in red for x in list_no_ace):
                                # then it's phase 7 overall too
                                phase_list.append(7)
                            else:
                                None

                # check if both lists have an accumulation of 34
                if accumulation_1 & accumulation_2 == 34:
                    # check if both lists have more than 2 number cards
                    if list1_numcards & list2_numcards >= 2:
                        # create a temp list with no aces
                        list_no_ace = [x for x in i if x[0] != 'A']
                        # if it adds up to 34 and all the cards are black    
                        if all(x[1] in black for x in list_no_ace):
                            # it's both phase 3 and 6
                            phase_list.extend([3, 6])
                        # if it adds up to 34 and all the cards are red 
                        elif all(x[1] in red for x in list_no_ace):
                            # it's both phase 3 and 6
                            phase_list.extend([3, 6])
                        else:
                            # if the colours don't match it's just phase 3
                            phase_list.append(3)

        # check if the lenght of the original input is 1
        if len(phase) == 1:
            for i in phase:
                run_card = running_cards(i)
                # check if the list has more than 2 value cards at least
                if list1_numcards >= 2:
                    # check if the list has 7 cards
                    if len(i) == 7:
                        # check if they all have the same suits
                        if len(set([x[1] for x in i if x[0] != 'A'])) == 1:
                            # if yes it's phase 2
                            phase_list.append(2)
                        else:
                            None    
                    
                    # check if the list has 8 cards
                    if len(i) == 8:        
                        # check if the card is running        
                        if len(i) == len(run_card):
                            # if it's run of 8 cards it's phase 5
                            phase_list.append(5)
                        else:
                            None
    else:
        return []

    # remove duplicates
    phase_list = dict.fromkeys(phase_list)
    # return a sorted list 
    return sorted(phase_list)


if __name__ == '__main__':
    # Example calls to the function.
    print(phazed_phase_type([['2C', '2S', '2H'], ['7H', '7C', 'AH']]))
    print(phazed_phase_type([['2C', '2C', '4C', 'KC', '9C', 'AH', 'JC']]))
    print(phazed_phase_type([['2C', 'KH', 'QS', '7H'],
                             ['3H', '7S', '0D', 'KD', 'AD']]))
    print(phazed_phase_type([['4H', '4S', 'AC', '4C'],
                             ['7H', '7C', 'AH', 'AC']]))
    print(phazed_phase_type([['4H', '5S', 'AC', '7C',
                              '8H', 'AH', '0S', 'JC']]))
    print(phazed_phase_type([['2C', 'KC', 'QS', '7C'],
                             ['3H', '7H', '0D', 'KD', 'AD']]))
    print(phazed_phase_type([['4H', '5D', 'AC', '7H'],
                             ['7H', '7C', 'AH', 'AS']]))
    print(phazed_phase_type([['4H', '5D', '7C', 'AC'], ['AC', 'AS', 'AS']]))
