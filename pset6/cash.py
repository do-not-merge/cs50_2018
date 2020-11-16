import cs50

# Prompt user for change owed

dollars = 0

while dollars <= 0:
    dollars = cs50.get_float("dollars = ")
    
# Convert dollars to cents to avoid floating-point imprecision
cents = int(round(dollars*100))

coins = 0

coins += cents // 25

# Amount of changed owed now equals remainder after dividing by 25
cents = cents % 25

# Repeat for dimes
coins += cents // 10
cents = cents % 10

# Repeat for nickels
coins += cents // 5

# Whatever is left must be pennies
coins += cents % 5

# Print counter
print("{}".format(coins))