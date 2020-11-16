import sys
from cs50 import get_string


def main():

    # Ensure proper usage
    if len(sys.argv) != 2 or not sys.argv[1].isdigit():
        exit("Usage: python slanted.py depth")
    depth = int(sys.argv[1])

    # Encrypt message
    message = get_string("Message: ")
    if len(message) >= depth:
        print("Slanted:", slant(message, depth))


def slant(message, depth):

    # Each line in the slant treated as a string
    depthLines = [[] for i in range(depth)]
    span = range(depth)
    limit = len(message)
    
    # Iteration based on slant
    for step in span:
        n = range(step, limit, depth)
        for index in n:
            # Create nested list for each chars found in line
            depthLines[step].append(message[index])
    
    # Combine nested list, join into one long entry, and return singular string entry
    return [''.join(j for k in depthLines for j in k)][0]
        

if __name__ == "__main__":
    main()
