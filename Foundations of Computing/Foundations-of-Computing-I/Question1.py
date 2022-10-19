def normal_cards(group):
    '''counts how many non-ace cards are in the group''' 
    normal_cards = 0
    # loop through the group and count every card that 
    # doesn't start with an A
    for i in group:
        if i[0] != 'A':
            normal_cards += 1
        else:
            None
    
    return normal_cards

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

def running_cards(group):
    '''
    function used to find out whether the sets of card is running
    '''
    normcard = []
    aces = []

    # separating the value cards from ace cards
    for card in group:
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

def phazed_group_type(group):
    ''' 
    main function that will check what phase has been played
    '''
    phase_list = []
    normal_card = normal_cards(group)
    run_card = running_cards(group)
    black = ['C', 'S']
    red = ['H', 'D']
    
    # checking accumulation count
    accumulation = 0
    if len(group) > 0:
        
        # iterate through each card in the list and add up their values
        for i in group:
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

        # checking for phase 1 with 3 items in a list 
        if len(group) == 3:
            # checking if there are more than 2 value cards in a list
            if normal_card >= 2:
                # checking if all the card in a list has a same value
                if len(set([x[0] for x in group if x[0] != 'A'])) == 1: 
                    # if yes it's phase 1
                    phase_list.append(1)
                else:  
                    None
        
        # checking for phase 2 with 7 items in a list
        elif len(group) == 7:
            if normal_card >= 2:
                # checking if all the suits of the cards are the same
                if len(set([x[1] for x in group if x[0] != 'A'])) == 1: 
                    # if yes it's phase 2
                    phase_list.append(2)
                else:  
                    None

        # check if there are 4 cards in the lsit
        elif len(group) == 4:
            if normal_card >= 2:
                # check if all the values are the same
                if len(set([x[0] for x in group if x[0] != 'A'])) == 1: 
                    # if yes it's phase 3
                    phase_list.append(3)
                
                # check if all the cards are black
                elif not i.startswith('A') and i[1] in black:
                    # check if the list is a run by comparing the
                    # length of the modified list from running_cards
                    # and the original list
                    if len(group) == len(run_card):
                        # if yes it's phase 5
                        phase_list.append(5)
                # check if all the cards are red
                elif not i.startswith('A') and i[1] in red:
                    # check if the list is a run by comparing the
                    # length of the modified list from running_cards
                    # and the original list
                    if len(group) == len(run_card):
                        # if yes it's phase 5
                        phase_list.append(5)

                else:
                    None

        # check if there are 8 cards in the list 
        elif len(group) == 8:
            if normal_card >= 2:
                # check if the list is a run by comparing the
                # length of the modified list from running_cards
                # and the original list
                if len(group) == len(run_card):
                    # if yes it's phse 4
                    phase_list.append(4)

        # if the all the values add up to 34 in a list
        if accumulation == 34:
            # if all the cards are black
            if not i.startswith('A') and all(x[1] in black for x in group):
                # it's phase 6 and 7
                phase_list.extend([6, 7])
            # if all the cards are red
            elif not i.startswith('A') and all(x[1] in red for x in group):
                # it's phase 6 and 7
                phase_list.extend([6, 7])
            else:
                # if colours don't match and just adds up to 34
                # it's phase 6 only
                phase_list.append(6)
        else:
            None  
    
    else:
        return []
    
    # return a sorted list with phases
    return sorted(phase_list)


if __name__ == '__main__':
    # Example calls to the function.
    print(phazed_group_type(['2C', '2S', '2H']))
    print(phazed_group_type(['2C', '2C', '4C', 'KC', '9C', 'AH', 'JC']))
    print(phazed_group_type(['4H', '4S', 'AC', '4C']))
    print(phazed_group_type(['4H', '5S', 'AC', '7C', '8H', 'AH', '0S', 'JC']))
    print(phazed_group_type(['4H', '5D', 'AC', '7H']))
    print(phazed_group_type(['KS', '0D', '8C', '3S']))
    print(phazed_group_type(['KS', '0C', '8C', '3S']))
    print(phazed_group_type(['2C', '2C', '4C', 'KC', '9C', 'AS', '3C']))
    print(phazed_group_type(['4H', '5D', '7C', 'AC']))
