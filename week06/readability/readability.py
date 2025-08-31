text = input("Text: ")

def count_letters(text_letters):
    letters = sum(1 for char in text_letters if char.isalnum())
    return letters

def count_word(text_word):
    words = 0
    in_word = False
    for i in range(len(text_word)):
        if not text_word[i].isspace():
            if not in_word:
                words += 1
                in_word = True
        else:
            in_word = False
    return words

def count_sentences(text_sentence):
    sentences = 0
    in_sentence = False
    for i in range(len(text_sentence)):
        if text_sentence[i] in ['.', '!', '?']:
            if not in_sentence:
                sentences += 1
                in_sentence = True
        else:
            in_sentence = False  # 修正：遇到非结束符时重置状态
    return sentences

def count_index(index_letters, index_word, index_sentence):
    l = float(index_letters / index_word * 100)
    s = float(index_sentence / index_word * 100)
    index_value = round(0.0588 * l - 0.296 * s - 15.8)
    return index_value

def print_index(index_value):
    if index_value < 1:
        print("Before Grade 1")
    elif index_value >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index_value}")

letters1 = count_letters(text)
word1 = count_word(text)
sentences1 = count_sentences(text)
index = count_index(letters1, word1, sentences1)
print_index(index)
