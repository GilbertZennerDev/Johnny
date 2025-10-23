'''
the idea is to have a User Experience like this:

Johnny - Nano Clone
Instructions: '_save' for saving, '_open' for opening, '_exit' for exit

line1content var x = 5
line2content var y = 2
_save
_exit
'''

import sys
import subprocess as sp

def save(content, filename):
	if content is None: print("Enter Content first"); return
	try:
		with open(filename, "w") as f:
			f.write("\n".join(content))
		print("File saved!")
	except Exception as e:
		print(e)
		return
    

def load(filename):
	try:
		with open(filename, "r") as f:
			content = [line for line in f.read().splitlines()]
		return content
	except Exception as e:
		print(e)

def printInstructions():
	print("Johnny - Nano Clone")
	print("Instructions: \n'_save' for saving\n'_load' for loading\n'_exit' for exit\n'_clear' to clear console")

content = []
printInstructions()
while 1:
	txt = input("")
	if txt == '_exit': exit()
	elif txt == '_save': save(content, input("Enter filename: "))
	elif txt == '_load':
		content = load(input("Enter filename: "))
		if content:
			for line in content: print(line)
	elif txt == '_clear':
		sp.run("clear"); printInstructions();
	else: content.append(txt)
