import sys
import pandas as pd
import numpy as np
from collections import defaultdict

DEFUALT_SEARCH_SIZE = 6
MIN_CONTAINED = 2
MAX_DEPTH = 5

def main():
    if len(sys.argv) != 6:
        print("Usage: (word list) (side1) (side2) (side3) (side4)")
    else:
        file_name = sys.argv[1]
        sides = sys.argv[2:]
        try_solving(file_name, sides)


def try_solving(file_name, sides):
    attempt = 1
    banned_words = set(getInvalidWordList())
    trying = True
    while trying:
        print("Solving Attempt {}".format(attempt))
        words = solver(file_name, sides, banned_words)
        for i, w in enumerate(words):
            print("{}) {}".format(i,w))
        print("{}) It worked".format(len(words)))
        inp = input("Please provide the disallowed words' numbers (no spaces): ")
        i_list = inp.split()
        if str(len(words)) in i_list:
            print('Thank you, saving new invalid words...')
            saveInvalidWordList(banned_words)
            return
        else:
            for i in i_list:
                if int(i) >= 0 and int(i) < len(words):
                    banned_words.add(words[int(i)])
        print("Banned words:")
        for w in banned_words:
            print(w)
        input("Press enter to continue\n")
        attempt += 1
        


def solver(file_name, sides, banned_words):
    valid = get_valid(file_name, sides, banned_words)
    df = pd.DataFrame(data=valid)
    filter_letters = df[df['contains'].str.len() > DEFUALT_SEARCH_SIZE]
    #Generate needed char set
    needed = set(''.join(sides))
    #For loop through first set
    res = search(filter_letters, needed)
    return(res)

def search(words_df, needed, previous_end = '.?', depth = 1):
    if len(needed) == 0:
        return [] #success
    elif depth > MAX_DEPTH:
        return None #failure
    #Filter out too few matches
    words_df_m = contains(words_df, needed, MIN_CONTAINED)
    #Filter out wrong first letter
    words_df_mf = words_df_m[words_df_m['first'].str.contains(previous_end,regex=True)]
    for row in words_df_mf.itertuples():
        new_needed = needed - set(row.contains)
        res = search(words_df_m, new_needed, row.last, depth+1)
        if res is not None:
            return [row.word] + res


def get_valid(file_name, sides, banned_words):
    d = {}
    for i,s in enumerate(sides):
        for c in s:
            d[c] = i
    word_list = getValidWordList()
    last = -1
    valid = {'word':[], 'first':[], 'last':[], 'contains':[]}
    print("DIRTY PRINT: {}".format(banned_words))
    for word in word_list:
        if word in banned_words:
            print(word)
            continue
        for c in word:
            if c in d and d[c] != last:
                last = d[c]
            else:
                last = -1
                break
        if last != -1:
            valid['word'].append(word)
            valid['first'].append(word[0])
            valid['last'].append(word[-1])
            contains = ''.join(sorted(set(word)))
            valid['contains'].append(contains)                
            last = -1
    return valid

def saveInvalidWordList(invalidWordList, filename = './InvalidWords.txt'):
    with open(filename, 'w') as f:
        for word in invalidWordList:
            f.write(word + '\n')
    return

def getInvalidWordList(filename = './InvalidWords.txt'):
    try:
        with open(filename, "r") as f:
            ret = f.read().splitlines()
        return ret
    except:
        return []

def getValidWordList(filename = './Words.txt'):
    with open(filename, "r") as f:
        ret = f.read().splitlines()
    return ret

def contains(df, chars, needs):
    ret = df[df['contains'].apply(lambda x: len(set(x).intersection(chars)) >= needs)]
    return ret

if __name__ == "__main__":
    main()