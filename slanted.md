# Complementary Questions

## Questions

7.1.  A "cipher" would be secure when knowing everything about the system minus the key does not reveal how the encryption was carried out.

7.2. The Caesar cipher is not too secure as its shift can be relatively easy to figure out after a few attempts modifying a trial key (the shift is the key); the cipher
    is also uniformly (and predictably) carried out throughout the whole encryption. 

7.3. Aside from the latter half of response 2, the slanted cipher suffers from the fact that modern day systems can trial a few 
    depths (key) and work backwards to reverse engineer whether the plaintext and trial key yield the original ciphertext. 

7.4. Encryption converts plaintext into ciphertext by using a key; without the key it cannot be understood. If the key is found the ciphertext
    can be converted back to plaintext, a "two-way" street. Hashing, meanwhile, maps the plaintext data to a fixed length of code which is not
    easily reversed. This exhibits more of "one-way" street functionality. 

7.5. It would not be secure to sland message with n characters to a depth of n as the message can be easily read from top to bottom, sort
    of like a vertical entry in a crossword puzzle.

7.6. See `slanted.py`
## Debrief

a. https://simplicable.com/new/encryption-vs-hashing, caesar.c

b. 75 minutes
