----------------------------------------
B. Darren Olson
CNS 3060
Project-6 Threads
----------------------------------------
Thoughts
----------------------------------------
part a-
This part executes immediately and finishes with count at 0. No notice able time elapsed from start to finish.
part b- 
This part takes a few seconds for it to come out with the end count which was 10 in the case.
part c- 
This part also like a executes very quickly and the count ends at 40.
part d- 
This one took >10s to complete, not sure why the mutex lock and unlock would cause this since in partc we didnt have the mutex we only used the sleep call and it got the correct count as well. Very intersting. 
