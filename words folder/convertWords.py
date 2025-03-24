# convert_words.py
words = []
with open('words.txt', 'r') as file:
    for line in file:
        words.append(line.strip())

with open('words_array.cpp', 'w') as file:
    file.write('const char* wordsArray[] = {\n')
    for word in words:
        file.write(f'    "{word}",\n')
    file.write('};\n')
    file.write(f'const int wordsArraySize = {len(words)};\n')