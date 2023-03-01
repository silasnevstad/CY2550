#!/usr/bin/env python
import argparse
import random

# load words from a file into a list
def load_words(filename):
    valid_words = []
    
    with open(filename) as word_file:
        # remove words more than 8 characters long
        valid_words = [word.strip() for word in word_file.readlines() if len(word.strip()) <= 8]

    return valid_words

# generate a password using the XKCD method
def generate_password(word_list, num_words, num_caps, num_numbers, num_symbols):
    words = [random.choice(word_list) for _ in range(num_words)] # select random words from the word list
    password = ' '.join(words) # join the words together with spaces

    if num_caps > 0: # if we want to capitalize some of the words
        cap_indices = random.sample(range(num_words), num_caps)
        words = [words[i].capitalize() if i in cap_indices else words[i] for i in range(num_words)]
        password = ' '.join(words)

    if num_numbers > 0: # if we want to insert some numbers into the password
        insert_positions = [random.choice(range(0, num_words + 1)) for _ in range(num_numbers)] # select random positions to insert numbers (start, end, and between words)
        insert_positions.sort()
        for i, pos in enumerate(insert_positions):
            insert_pos = len(' '.join(words[:pos])) + i # calculate the position to insert the number
            password = password[:insert_pos] + str(random.randint(0, 9)) + password[insert_pos:] # insert a random number

    if num_symbols > 0: # if we want to insert some symbols into the password
        insert_positions = [random.choice(range(0, num_words + 1)) for _ in range(num_symbols)] # select random positions to insert symbols (start, end, and between words)
        insert_positions.sort()
        words = password.split() # split the password into words again (in case we inserted numbers)
        for i, pos in enumerate(insert_positions):
            insert_pos = len(' '.join(words[:pos])) + i # calculate the position to insert the symbol
            password = password[:insert_pos] + random.choice('~!@#$%^&*.:;') + password[insert_pos:] # insert a random symbol

    return password.replace(' ', '') # remove the spaces from the password

def main():
    parser = argparse.ArgumentParser(description='Generate a secure, memorable password using the XKCD method') # create a command line argument parser
    parser.add_argument('-w', '--words', type=int, default=4, help='include WORDS words in the password (default=4)') # add command line arguments
    parser.add_argument('-c', '--caps', type=int, default=0, help='capitalize the first letter of CAPS random words (default=0)') # add command line arguments
    parser.add_argument('-n', '--numbers', type=int, default=0, help='insert NUMBERS random numbers in the password (default=0)') # add command line arguments
    parser.add_argument('-s', '--symbols', type=int, default=0, help='insert SYMBOLS random symbols in the password (default=0)') # add command line arguments

    args = parser.parse_args() # parse the command line arguments
    
    word_list = load_words('words.txt') # load the word list
    
    if (args.caps > args.words): # if we want to capitalize more words than the number of words in the password
        print('Error: Cannot capitalize more words than the number of words in the password')
        exit(1)

    password = generate_password(word_list, args.words, args.caps, args.numbers, args.symbols) # generate the password
    print(password)

if __name__ == '__main__':
    main()