#!/usr/bin/env python
import sys
import python_header
str2=""
evaluater = python_header.string_match_score() #object of class match_score
try:
  fo = open(sys.argv[2], "r") #reading the 3rd command line argument 
  str2 = fo.readline()
  str2=str2[0:len(str2)-1] 
except IOError:
  print "The file does not exist, exiting" #if the file does not exist (exception handling)
try:
  fo = open(sys.argv[2], "r")
  highest_ms=0
  ms_list=[] #list of match_scores 
  for str1 in open(sys.argv[1],'r').readlines():
    str1=str1[0:len(str1)-1]
    evaluater.input_from_file(str1,str2)
    evaluater.evaluate_match_score()
    ms=evaluater.match_score
    ms_list.append(ms)
    if evaluater.match_score >= highest_ms:
      highest_ms=evaluater.match_score
  for elem in ms_list:
    if elem==highest_ms:  
      print  1+ms_list.index(elem)
except IOError:
  print "The file does not exist, exiting"



    
    
  
  

