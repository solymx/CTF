#!/usr/bin/env python
# -*- coding: utf-8 -*-
import random
import user_functions

user = raw_input("Enter your name: ")

if not user_functions.exists(user):
  # generate a code

  count_ = user_functions.generateID(user)%1000	#User ID/ UID in the table is always positive

  generator = "xorshift"
  random.seed(generator)
  count = 0;

  for ch in user:
    ra = random.randint(1, ord(ch))
    rb = (ord(ch) * random.randint(1, len(user))) ^ random.randint(1, ord(ch))

    count += (ra + rb)/2

  
  code = 1

  for i in range(1,count+count_):
    code = (code + random.randint(1, i) ) % 1000000

  final = random.randint(1,9) * 1000000 + code

  #store it in the database
  user_functions.store(user, final)

else:
  #if user already exists, fetch access code
  final = user_functions.get_code(user)

code = raw_input("Enter your access code: ").strip()


while True:
  
  if code.isdigit():
    if (int(code) == final):
      print "The flag is " + user_functions.get_flag(user)
      exit()
    else:
      print "Incorrect access code"
  else:
    print "The code must be an integer"

  code = (raw_input("\nPlease enter the code: "))

  print "\n###############################################"