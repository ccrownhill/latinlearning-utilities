#!/usr/bin/python3

'''
latinlearn.py -n num_vocs (default: 10) vocfilename

Ask random num_vocs latin words from vocfilename (a file with fields separated by tabs)
All words are in a queue data structure and wrongly answered ones go back to the beginning of the queue.
One line can have up to 255 characters.
A correct answer means that only one correct meaning must have been given.
'''

import argparse
from collections import deque 
from random import sample

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--numvoc', default=10, type=int, help='number of vocabularies to go throug')
    parser.add_argument('vocfilename', type=str, help='tab separated vocabulary file to load random words from')
    args = parser.parse_args()

    word_entry_dict_keys = ['word', 'extra', 'meaning']
    full_word_list = list()
    voc_queue = deque()

    with open(args.vocfilename, 'r') as file:
        for line in file:
            # replace all html elements correctly and split the line into the single parts
            # by splitting at tab characters because this program deals with tab separated values
            line = line.replace('<div>', ', ').replace('</div>', '')\
                    .replace('<br>', ', ')\
                    .replace('<i>', '').replace('</i>', '')\
                    .replace('<b>', '').replace('</b>', '')\
                    .strip().split('\t')
            full_word_list.append({key: value for key, value in zip(word_entry_dict_keys, line)})
    voc_queue.extend(sample(full_word_list, args.numvoc))

    # ask words until all words were answered correctly
    while voc_queue:
        word = voc_queue.popleft()
        answer = input("'%s'?: " % word['word'])
        if not is_word_correct(word['meaning'], answer):
            print('\033[1;31mWrong\033[0;0m') # print in red
            voc_queue.append(word)
        else:
            print('\033[1;32mCorrect\033[0;0m') # print in green
        print("%s\n%s\n" % (word['extra'], word['meaning']))


def is_word_correct(meaning, answer):
    '''
    Returns true if at least 1 meaning was correct
    '''
    meaning_set = set(meaning.split(', '))
    answer_set = set(answer.split(', '))
    return (meaning_set & answer_set)


if __name__ == '__main__':
    main()
