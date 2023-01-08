import time

wordList = []

with open("words_alpha_len_4_greater.txt", encoding='utf-8') as f:
    wordList = f.read().split()

start = time.perf_counter()

allLetters = set('acdijlu')
wordList = filter(lambda s: 'a' in s, wordList)
wordList = filter(lambda s: set(s) <= allLetters, wordList)
final = list(wordList)

end = time.perf_counter()
print(f'{end-start} sec')

print(len(final))