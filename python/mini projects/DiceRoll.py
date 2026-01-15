# roll the dice
# asks for the number of dice to roll and gives the result

import random

x = input('Roll the dice? (y/n): ').lower()

while True:

    if x == 'y':
        num = input('Enter number of dice: ')
        if num.isdigit():
            number = int(num)
            if number <= 0:
                print("Please enter a positive number.")
                continue

            results = [random.randint(1, 6) for _ in range(number)]

            print(f"You rolled: {results}")
            
        else:
            print("Please enter a valid number.")
            continue

        x = input('Would you like to roll the dice again? (y/n): ').lower()

    elif x == 'n':
        print('Thanks for playing!')
        break

    else:
        print('Invalid choice.')