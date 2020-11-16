# Like Magic

## Questions

4.1. 0x42 is (16x4) + (2x1)= 66 which is B. 0x4d is (16x4) + (13x1) = 77, or M,
    forming "BM" string.

4.2. Similarly, first four hexadecimals in PDF form "%PDF" string.

4.3. Magic numbers in front of a file could easily be picked up by a byte editor
    which would then modify every relevant byte in the file. Sometimes, though, they
    may indicate the file devloper's initials or even birthday.

4.4. The fourth byte (buffer[3]) is compared against 11110000 (0xf0), yielding
    the results of the bitwise gate doing logical AND operation. If a byte has 
    the 1110xxxx format (where x is 0 or 1) then this will evaluate to 11100000, 
    or 0xe0. Compared for equality against 0ex0 guarantees that the fourth byte
    of a jpeg was converted to 0xe0 after the AND operation, a valid jpeg byte.
    
4.5. Zamylas code will have to run many less case comparison computations
    that can be otherwise simplified into one line of code (calcualtion); less 
    memory is used leading to more graceful code.

4.6. See `magic.c`.

## Debrief

a. http://www.linfo.org/magic_number.html and Wikipedia; recover.c and shorts

b. 60 minutes
