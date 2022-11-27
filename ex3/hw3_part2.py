

#a function that gets a string and returns dict. keys are lengths, and values are lists of all the palindromic substrings with same length
def get_palindrom_dict(s):
    dict={} #creates a dict to hold the result
    n = len(s)
    for k in range(1,n+1): #k goes from 1 to n
        for t in range(0,n-k+1):#t goes from 0 to n-k+1, used to intertate over substrings with length k
            tempStr = s[t:t+k]# substring with length k
            if(tempStr==tempStr[::-1]):#check if tempStr is palindom by reversing it and comparing to itself
                if(not(k in dict)): #creating a new list with the key 'k' if it does not exist
                    dict[k] = []
                dict[k].append(s[t:t+k])#inserts the substring
    return dict #returns the finished dictionary



def check_match(str):
    #if the str length is not even, the two strings are not the same lenght.
    if (len(str)%2!=0):
        return False
    
    charDict = {} #a ditctionary that will hold the letter mapping.
    #splits the string into pairs of letters. first letter from word1, second letter from word2 with the same index
    chunks = [str[i:i+2] for i in range(0, len(str), 2)]
    #iterating over all pairs of letters
    for entry in chunks:
        if entry[0] in charDict: #if the letter already has a mapped value check if its the same.
            if(charDict[entry[0]] != entry[1]):
                return False #return false if the mapped value is different.
        else:
            charDict[entry[0]] = entry[1] #the letter is not mapped yet, save the mapped value.
    #if we got here all of the letters can be mapped correctly.
    return True
