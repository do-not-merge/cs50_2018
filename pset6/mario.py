import cs50

height = -1

while height <= 0 or height > 8:
    height = cs50.get_int(print("Height:", end=" "))

for i in range(1, height + 1):
    hash = i
    
    # Determine number of spaces to start
    spaces = height - hash
    
    # Format pyramid with proper spacing (left)
    print(" " * spaces, end="")
    print("#" * hash, end="")

    # Add 2 spaces between right and left sides
    print("  ", end="")

    # Format pyramid (right)
    print("#" * hash)