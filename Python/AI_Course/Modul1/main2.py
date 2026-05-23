# import string

# def translate(text):
#     lower_map = {
#         'а': 'a', 'б': 'b', 'в': 'v', 'г': 'g', 'д': 'd',
#         'е': 'e', 'ё': 'e', 'ж': 'zh', 'з': 'z', 'и': 'i',
#         'й': 'i', 'к': 'k', 'л': 'l', 'м': 'm', 'н': 'n',
#         'о': 'o', 'п': 'p', 'р': 'r', 'с': 's', 'т': 't',
#         'у': 'u', 'ф': 'f', 'х': 'kh', 'ц': 'ts', 'ч': 'ch',
#         'ш': 'sh', 'щ': 'shch', 'ъ': 'ie', 'ы': 'y', 'ь': '',
#         'э': 'e', 'ю': 'iu', 'я': 'ia'
#     }

    
#     res = ""
#     for it in text:

#         if it == ' ':
#             res += ' '
#             continue

#         if it.isupper():
#             ch = lower_map[it.lower()]
#             res += ch.upper()
#         else:
#             res += lower_map[it]
#     return res

# text = input("Ведите Фамилия Имя Отчество: ")
# trans = translate(text)
# print(trans)

# ====================================================

def find_substring(text):

    max_count = 0
    count = 0
    subString = ""
    visit = []
    res = ""

    for it in text:
        if it in visit:
            if count > max_count:
                max_count = count
                res = subString
                            
            while it in visit:
                if count == 0:
                    break
                visit.pop(0)
                count -= 1
                subString = subString[1:]
                
            
        visit.append(it)
        count += 1
        subString += it
    
    if count > max_count:
                max_count = count
                res = subString

    return res

text = input()
subString = find_substring(text)
print(subString)