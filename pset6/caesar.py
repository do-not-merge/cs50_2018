import cs50
from sys import argv

alphabet = 26


def main():
    
    # Ensure proper usage
    if len(argv) != 2:
        print(f"Usage: ./encrypt key")
        exit(1)
        
    # Validate key 
    key = argv[1]
    if not int(key.isdigit()):
        print(f"Usage: ./encrypt key")
        exit(1)

    plaintext = cs50.get_string(print("plaintext: ", end=""))
    ciphertext = []
    
    # Do some magic with lowercase and uppercase
    for char in plaintext:
        if char.isalpha():
            ciphertext.append(encrypt(int(key), char))
        else:
            ciphertext.append(char)
            
    # Construct the enryption            
    ciphertext = "".join(ciphertext)
    print(f"ciphertext: {ciphertext}")
    
    exit(0)


def encrypt(ikey, char):
    if char.islower():
        return chr(((ord(char) - 97 + ikey) % alphabet) + 97)
    else:
        return chr(((ord(char) - 65 + ikey) % alphabet) + 65)
            
    
if __name__ == "__main__":
    main()
