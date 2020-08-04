
Lemin is an advanced algorithmic project at Codam dealing with graph theory and networks.

The objective of this project is to write an algorithm that is able to find the a combination of paths within a network, that would produce maximum network flow.

How can we get the most amount of ants through a maze with the least amount of moves?

An example of input for this program is as follows:

```
34                         the number of ants  (input quantity)         
##start                    a 'tag' indicating that the next line is the starting room 
1 23 3                                    
2 16 7                     a line detailing a room within the network (format: <name> <x_coordinate> <y_coordinate>
#comment                   a 'tag' used to write comments within the input file
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end                      a 'tag' indicating that the next line is the ending room
0 9 5
0-4
0-6                        a line indicated a connection between two rooms (format: <room_name>-<room_name>
1-3
4-3
5-2
3-5
#another comment
4-2
2-1
7-6
7-2
7-4
6-5
#another comment
```

from this input, the program generates a solution where the objective is to get all the ants from the start room to the end room with the least amount of moves possible.

constraints:

 -  each ant can only move once per turn.
 -  each room can only contain one ant, except the start and end room which can contain an infinite amount of ants.

solution for the input example above:

```
L1-3 L2-2                                     interpretation: Ant 1 moves to room 3, Ant 2 moves to room 2
L1-4 L3-3 L2-7 L4-2
L1-0 L3-4 L5-3 L2-6 L4-7 L6-2
L3-0 L5-4 L7-3 L2-0 L4-6 L6-7 L8-2
L5-0 L7-4 L9-3 L4-0 L6-6 L8-7 L10-2
L7-0 L9-4 L11-3 L6-0 L8-6 L10-7 L12-2
L9-0 L11-4 L13-3 L8-0 L10-6 L12-7 L14-2
L11-0 L13-4 L15-3 L10-0 L12-6 L14-7 L16-2
L13-0 L15-4 L17-3 L12-0 L14-6 L16-7 L18-2
L15-0 L17-4 L19-3 L14-0 L16-6 L18-7 L20-2
L17-0 L19-4 L21-3 L16-0 L18-6 L20-7 L22-2
L19-0 L21-4 L23-3 L18-0 L20-6 L22-7 L24-2
L21-0 L23-4 L25-3 L20-0 L22-6 L24-7 L26-2
L23-0 L25-4 L27-3 L22-0 L24-6 L26-7 L28-2
L25-0 L27-4 L29-3 L24-0 L26-6 L28-7 L30-2
L27-0 L29-4 L31-3 L26-0 L28-6 L30-7 L32-2
L29-0 L31-4 L33-3 L28-0 L30-6 L32-7
L31-0 L33-4 L34-3 L30-0 L32-6
L33-0 L34-4 L32-0                             Ant 33 moves to room 0, Ant 34 moves to room 4, Ant 32 moves to room 0
L34-0
```

Each 'turn' is represented with a line in the output. A move is indicated as 'L(ant_number)-(room_number)'.
For example, 'L23-3' means that ant 23 moves to room 3. The goal is to find a solution that used the least amount of turns.

To compile the lemin executable, run 'Make' in the root of the repository.



