#!/usr/bin/env python
import sys

'''
 shows first class nature of functions:
 1> can be assigned to variables
 1.1> functions can be returned
 2> higher-order functions: can be passed as arguments to other functions
 3> closures, call nested function even without outer function is done
'''

def function(test):
 ''' hi there.'''
 print "this is function", test

def anotherfunc(argfunc):
    print "This is another func", argfunc
    argfunc(10)

def outer(a):
   def inner(a):
     return a
   return inner

def outer_c(a):
   def inner_c(b):
     return a+b
   return inner_c

# 1> can be assigned to variables
variable=function
variable(3)
function.__doc__

#1.1> functions can be returned
f=outer(10)
print f
print f(11)

#2> can be passed as arguments to other functions
anotherfunc(variable)

#3> closures, call nested function even without outer function is done
print "Closure"
f=outer_c(12)
print f(11)

