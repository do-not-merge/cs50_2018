import cs50 
from sys import argv
import string


def main():
    
    # Ensure proper usage
    if len(argv) != 2:
        print("Usage: python bleep.py dictionary")
        exit(1)
        
    # Read through bad words and add to set via a list comprehension
    badboitingz = set()
    file = open(argv[1], "r")
    badboitingz = [line.strip() for line in file]
    file.close()
    
    # Account for an all-caps case (dictionary of bad words assumed all lowercase)
    revertcase = False
    
    msg = cs50.get_string(print("What message would you like to censor?"))
   
    if msg.isupper():
        revertcase = True 
        msg = msg.lower()
    
    msg_token = msg.split()
    
    for badword in badboitingz:
        if badword in msg_token:
            censor = "*" * len(badword)
            msg = msg.replace(badword, censor) 
            
    if revertcase == True:
        msg = msg.upper()
        
    print(msg)
    exit(0)
    
    
if __name__ == "__main__":
    main()


# Future work: Mixed case. 'Well, DArn it' or 'well, DARN it' can also be censored to 'well, **** it'