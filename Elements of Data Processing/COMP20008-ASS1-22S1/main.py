"""
COMP20008 Elements of Data Processing
2022 Semester 1
Assignment 1

Solution: main file

DO NOT CHANGE THIS FILE!
"""

import os
import sys


def verify_task1():
    try:
        from task1 import task1
    except ImportError:
        print("Task 1's function not found.")
        return

    print("=" * 80)
    print("Executing Task 1...\n")
    
    task1()

    print("Checking Task 1's output...\n")
    if os.path.isfile("task1.json"):
        print("\tTask 1's JSON output found.\n")
    else:
        print("\tTask 1's JSON output NOT found. Please check your code.\n")


    print("Finished Task 1.")
    print("=" * 80)


def verify_task2():

    try:
        from task2 import task2
    except ImportError:
        print("Task 2's function not found.")
        return

    print("=" * 80)
    print("Executing Task 2...\n")
    task2()

    print("Checking Task 2's output...\n")
    if os.path.isfile("task2.csv"):
        print("\tTask 2's CSV output found.\n")
    else:
        print("\tTask 2's CSV output NOT found. Please check your code.\n")

    print("Finished Task 2.")
    print("=" * 80)


def verify_task3():

    try:
        from task3 import task3
    except ImportError:
        print("Task 3's function not found.")
        return

    print("=" * 80)
    print("Executing Task 3...\n")
    task3()

    print("Checking Task 3's output...\n")

    if os.path.isfile("task3a.csv"):
        print("\tTask 3a's CSV output found.\n")
    else:
        print("\tTask 3a's CSV output NOT found. Please check your code.\n")

    if os.path.isfile("task3b.png"):
        print("\tTask 3b's PNG output found.\n")
    else:
        print("\tTask 3b's PNG output NOT found. Please check your code.\n")

    print("Finished executing Task 3.")
    print("=" * 80)


def verify_task4():

    try:
        from task4 import task4
    except ImportError:
        print("Task 4's function not found.")
        return 

    print("=" * 80)
    print("Executing Task 4...\n")
    task4()

    print("Checking Task 4's output...\n")
    
    if os.path.isfile("task4a.csv"):
        print("\tTask 4a's CSV output found.\n")
    else:
        print("\tTask 4a's CSV output NOT found. Please check your code.\n")
    
    if os.path.isfile("task4b.png"):
        print("\tTask 4b's PNG output found.\n")
    else:
        print("\tTask 4b's PNG output NOT found. Please check your code.\n")

    print("Finished executing Task 4.")
    print("=" * 80)


def verify_task5():

    try:
        from task5 import task5
    except ImportError:
        print("Task 5's function not found.")
        return

    print("=" * 80)
    print("Executing Task 5...\n")
    task5()

    print("Checking Task 5's output...\n")
    if os.path.isfile("task5.png"):
        print("\tTask 5's PNG output found.\n")
    else:
        print("\tTask 5's PNG output NOT found. Please check your code.\n")

    print("Finished executing Task 5.")
    print("=" * 80)


def verify_task6():

    try:
        from task6 import task6
    except ImportError:
        print("Task 6's function not found.")
        return

    print("=" * 80)
    print("Executing Task 6...\n")

    task6()

    print("Checking Task 6's output...\n")

    if os.path.isfile("task6.json"):
        print("\tTask 6's JSON output found.\n")
    else:
        print("\tTask 6's JSON output NOT found. Please check your code.\n")
    print("Finished executing Task 6.")
    print("=" * 80)


def verify_task7():

    try:
        from task7 import task7
    except ImportError:
        print("Task 7's function not found.")
        return

    print("=" * 80)
    print("Executing Task 7...\n")
    task7()

    print("Checking Task 7's output...\n")
    if os.path.isfile("task7a.csv"):
        print("\tTask 7a's CSV output found.\n")
    else:
        print("\tTask 7a's CSV output NOT found. Please check your code.\n")

    if os.path.isfile("task7b.png"):
        print("\tTask 7b's PNG output found.\n")
    else:
        print("\tTask 7b's PNG output NOT found. Please check your code.\n")
    
    if os.path.isfile("task7c.png"):
        print("\tTask 7c's PNG output found.\n")
    else:
        print("\tTask 7c's PNG output NOT found. Please check your code.\n")

    print("Finished executing Task 7.")
    print("=" * 80)

def verify_task8():

    print("Checking if task8.pdf exists...\n")
    
    if os.path.isfile("task8.pdf"):
        print("\tReport task8.pdf found.\n")
    else:
        print("\tReport task8.pdf NOT found. Please check the file name or upload the file.\n")

    print("Finished Task 8.")
    print("=" * 80)



def main():
    args = sys.argv
    assert len(args) >= 2, "Please provide a task."
    task = args[1]
    assert task in ["task" + str(i) for i in range(1, 9)] + \
        ["all"], "Invalid task."
    if task == "task1":
        verify_task1()
    elif task == "task2":
        verify_task2()
    elif task == "task3":
        verify_task3()
    elif task == "task4":
        verify_task4()
    elif task == "task5":
        verify_task5()
    elif task == "task6":
        verify_task6()
    elif task == "task7":
        verify_task7()
    elif task == "task8":
        verify_task8()
    elif task == "all":
        verify_task1()
        verify_task2()
        verify_task3()
        verify_task4()
        verify_task5()
        verify_task6()
        verify_task7()
        verify_task8()


if __name__ == "__main__":
    main()
