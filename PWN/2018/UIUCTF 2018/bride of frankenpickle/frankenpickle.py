#!/usr/bin/env python2.7
import os, sys, hashlib, pickle

class Recipe:
    def __init__(self, name):
        self.secret_ingredient = "flag{XXXXXXXXXXXXXXXX}"
        self.name = name
        self.prep_time = 0
        self.steps = []
        self.ingredients = []
    def set_prep_time(self, minutes):
        self.prep_time = minutes
    def add_ingredient(self, ingredient):
        self.ingredients.append(ingredient)
    def add_step(self, step):
        self.steps.append(step)
    def __str__(self):
        out = "\n"+(len(self.name)+4)*"-"+"\n"
        out += "| " + self.name + " |\n"
        out += (len(self.name)+4)*"-"+"\n"
        out += "Preparation time: " + str(self.prep_time) + " minutes\n"
        out += "Ingredients: "
        for i in self.ingredients:
            out += i + ", "
        out = out[:-2] + "\n"
        out += "Steps:\n"
        for i in range(len(self.steps)):
            out += str(i+1) + ". " + self.steps[i] + "\n"
        return out

print(sys.version)
username = raw_input('USERNAME> ')
userdir = hashlib.md5(username).hexdigest()
try: os.mkdir(userdir)
except: pass
os.chdir(userdir)
op = '0'
while op != '2':
    op = raw_input('\n[0] WRITE RECIPE\n[1] READ RECIPE\n[2] EXIT\n> ')
    filename = '/'
    while op in ('0', '1') and '/' in filename:
        filename = raw_input('NAME> ')
    if op == '0':
        recipe = Recipe(filename)
        recipe.set_prep_time(float(raw_input('PREP TIME> ')))
        print('INGREDIENTS:')
        ingredient = raw_input('> ')
        while ingredient:
            recipe.add_ingredient(ingredient)
            ingredient = raw_input('> ')
        print('STEPS:')
        step = raw_input('> ')
        while step:
            recipe.add_step(step)
            step = raw_input('> ')
        f = open(filename, 'wb')
        pickle.dump(recipe, f)
    elif op == '1':
        f = open(filename, 'rb')
        print(pickle.load(f))
