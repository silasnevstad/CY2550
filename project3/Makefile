# Makefile for XKCD password generator

# Set the name of the Python script
SCRIPT = xkcdpwgen.py

# Set the name of the words file
WORDS_FILE = words.txt

# Set the default values for command line arguments
WORDS = 4
CAPS = 0
NUMBERS = 0
SYMBOLS = 0

default:
	./$(SCRIPT) -w $(WORDS) -c $(CAPS) -n $(NUMBERS) -s $(SYMBOLS)

w:
	./$(SCRIPT) -w $(WORDS)

c:
	./$(SCRIPT) -c $(WORDS)

n:
	./$(SCRIPT) -n $(WORDS)

password:
	./$(SCRIPT) -w $(WORDS) -c $(CAPS) -n $(NUMBERS) -s $(SYMBOLS)

clean:
	rm -f *.pyc

