**Quesition:**
That Breath of the Wild Windmill Puzzle

One of the puzzles in the video game “Legend of Zelda: Breath of the Wild” places you near a rectangular grid of blocks. Some of the blocks have windmills mounted on them, which spin when air is
blown through them. The remaining blocks have fans, which blow wind in a single direction (up, down, left, or right). A fan will blow wind in a straight line, spinning each windmill in that line, no matter how far away, and no matter what other objects are in between. A windmill will spin if one or more fans are
pointed at it.

The goal of the puzzle is to make all of the windmills spin simultaneously by turning the fans. We’d like
to do it in the least amount of moves possible. A “move” turns a block’s fan ninety degrees in either direction.

Input:
Each input case will begin with two integers r and c (<10), the number of rows and columns of the grid. A value of r=c=0 denotes end of input. The next line will contain an integer n (1 <= n < 10), the number of fans. On the next n lines, there will be three integers ri ci di. ri and ci are integers denoting the row and column of the fan on the grid (positions start from 0). di will be one of the 4 characters {U,D,L,R}, signifying whether the fan is initially blowing air Up, Down, Left, or Right.

Output:
For each input case I, output:
Case i: k
..where k is the minimum number of turns of fans needed to make wind blow on all windmills.
If it is not possible to make the wind blow on all windmills, output:
Case i: Impossible
Sample Input:
4 4
5
0 3 U
1 2 U
2 2 R
3 0 L
3 3 U
4 4
4
0 3 U
1 2 U
2 2 R
3 0 L
0 0
Sample Output:
Case 1: 6
Case 2: Impossible
