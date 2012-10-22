#! /usr/bin/python

import math

def Print(array, counter):
  i = 0
  total = 0
  temp = 0
  print("Head Movement		Tracks Traversed")
  while(i < counter - 1):
    temp = int(math.fabs(array[i] - array[i+1]))
    print("Tracks " + str(array[i]) + "-" + str(array[i+1]) + "\t\t" +  str(temp))
    total = total + int(temp)
    i = i + 1
  print("Total Tracks Traversed:\t\t" + str(total))

def Sort(array, counter):
  print("Shortest Path:")
  sort_array = [-1] * 100
  count = counter
  first = array[0]
  sort_array[0] = first
  del array[0]
  i = 0
  while(count > 1):
    nearest_index = 0
    nearest_val = 10000000
    for j in xrange(0, count - 1): 
      diff = math.fabs(array[j] - sort_array[i])
      if(diff < nearest_val):
	nearest_index = j
	nearest_val = diff
    i = i + 1
    sort_array[i] = array[nearest_index]
    del array[nearest_index]
    count = count -1
  Print(sort_array, counter)

def Elevator(array, counter):
  print("Elevator: ")
  ele_array = [-1] * 100
  count = counter
  ele_array[0] = array[0]
  del array[0]
  i = 0
  curr_floor = ele_array[0]
  while(count > 1):
    nearest_index = 0
    nearest_val = 1000000
    for j in xrange(0, count -1):
      diff = math.fabs(array[j] - ele_array[i])
      if(diff < nearest_val and array[j] > curr_floor):
	nearest_index = j
	nearest_val = diff
    i = i + 1
    curr_floor = nearest_index
    ele_array[i] = array[nearest_index]
    del array[nearest_index]
    count = count - 1
  Print(ele_array, counter)

  
print("Enter a neg. value to exit: ")
input = 15
counter = 0
array = [-1] * 100
while(input >= 0):
  array[counter] = input
  counter = counter + 1;
  input = int(raw_input().rstrip('\n'))
print("First Come First Served")
temp = array[:]
Print(temp, counter)
temp = array[:]
Sort(temp, counter)
temp = array[:]
Elevator(temp, counter)
