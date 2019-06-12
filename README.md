# Six Degrees of Kevin Bacon (C++)
 **Collaborators:** Winnie Jeng, Jack Zhao</br>
 **Date:** Jun 12, 2019</br>
 **Data Source:** [IMDb Datasets](https://datasets.imdbws.com)</br>
 
### What is this?
The Six degrees of separation is the idea that all people are six, or fewer, social connections away from each other. 
As a result, a chain of "a friend of a friend" statements can be made to connect any two people in a maximum of six steps.
### In this project...
Base on the concept of Six Degrees of seperation, the "Six Degrees of Kevin Bacon" implies the 
shortest path between an arbitrary actor and the prolific actor Kevin Bacon. 
### What's more?
Except for finding the "Bacon Number" only, this program allows users to find the shortest path between any two arbitrary actors or casts. 
With Breadth First Search Algorithm, the program will explore all the movies that the actor gets credited, 
then find all the actors related to these movies,..., finally, the target actor can be found.
### Insights
With 1105422 data sets, linked list or array based data structures takes O(n) times to treverse, hence, tree is implemented. 
Datas are collected and inserted into two seperate AVL Trees, 
the worst case scenario to loop up, insert and delete takes O(log(n)) times. However, rebalancing after each insertion wastes a lot of time.
</br>

### Preview
```C++

/**************************************************************************************

00%...10%...20%...30%...40%...50%...60%...70%...80%...90%...100%...Done!
Database loaded, elapsed time: 11s

Choose Mode:
 [a] Traditional [b] Freedom [x] Exit
:a
Traditional Mode --->
Enter two actor/cast names and find which person has the highest Bacon Number!
Actor 1 name  (or press Enter to exit): Jackie Chan
Actor 2 name:  (or press Enter to exit): Leonardo DiCaprio

	Initial Actor: Jackie Chan
	Target Actor: Kevin Bacon
	Path Length: 2

	Jackie Chan --> "The Protector" --> Danny Aiello.
	Danny Aiello --> "Dead Silence" --> Kevin Bacon.

	Time Elapsed: (43ms)


	Initial Actor: Leonardo DiCaprio
	Target Actor: Kevin Bacon
	Path Length: 2

	Leonardo DiCaprio --> "Parenthood" --> Dianne Wiest.
	Dianne Wiest --> "Footloose" --> Kevin Bacon.

	Time Elapsed: (18ms)

Actor 1 name  (or press Enter to exit): 
Choose Mode:
 [a] Traditional [b] Freedom [x] Exit
:b
Freedom Mode --->
Enter any two actor/cast names and find their connections!
Start with a Cast name  (or press Enter to exit): Matt Damon
Target Cast name:  (or press Enter to exit): David Tennant

	Initial Actor: Matt Damon
	Target Actor: David Tennant
	Path Length: 2

	Matt Damon --> "Saving Private Ryan" --> Mark Gordon.
	Mark Gordon --> "Casanova" --> David Tennant.

	Time Elapsed: (46ms)

Start with a Cast name  (or press Enter to exit): 
Choose Mode:
 [a] Traditional [b] Freedom [x] Exit
:x
Thanks for playing!
Program ended with exit code: 0

**************************************************************************************/
```
