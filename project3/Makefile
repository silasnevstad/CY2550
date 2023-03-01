# Makefile for XKCD password generator

# Set the name of the Python script
SCRIPT = xkcd_password.py

# Set the name of the words file
WORDS_FILE = words.txt

# Set the default values for command line arguments
WORDS = 4
CAPS = 0
NUMBERS = 0
SYMBOLS = 0

# Define the build rule for the script
$(SCRIPT): $(SCRIPT).py $(WORDS_FILE)
    chmod +x $(SCRIPT).py
    mv $(SCRIPT).py $(SCRIPT)

# Define a rule to generate a password
.PHONY: password
password:
    ./$(SCRIPT) -w $(WORDS) -c $(CAPS) -n $(NUMBERS) -s $(SYMBOLS)

# Define a rule to clean up generated files
.PHONY: clean
clean:
    rm -f $(SCRIPT)

# Define a rule to run tests (if any)
.PHONY: test
test:
    # Add test commands here, if any
