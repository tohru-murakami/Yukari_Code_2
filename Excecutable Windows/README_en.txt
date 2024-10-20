Group Optimization Program

** About this problem

The task is to create groups of m (=4) students from the class of n students.
The "compatibility" between students is given as a number from 1 to 10. 
A larger number indicates a "better relationship."

For example, the goal is to create groups that satisfy the following
conditions:
(1) Each group has m or m-1 students.
(2) Groups with only one girl or one boy are not allowed, except in groups of three where one can be alone.
(3) A "good group assignment" is defined as:
  (a) The group with the largest "minimum compatibility" within the group.
  (b) If the "minimum compatibility" is the same, the group with the largest "total compatibility" is preferred.


** Assumptions

(1) There are more boys than girls.
(2) If girls cannot be alone in a group, the number of girls is even. 
    (If the number of girls is odd, please add a dummy student.)

** Preparing Student Data

Prepare a file as follows:
Example:
--- Start ---
16
0 1 0
1 1 0
2 1 0
3 1 0
4 1 0
5 1 1
6 0 1
7 0 1
8 0 0
9 0 0
10 0 0
11 0 0
12 0 0
13 0 0
14 0 0
15 0 0
4 12 2
4 13 4
4 14 6
4 15 8
5 6 8
5 7 8
5 8 4
5 9 8
5 10 4
5 11 4
5 12 5
5 13 7
5 14 5
5 15 8
6 7 4
6 8 4
6 9 8
6 10 4
6 11 6
6 12 5
6 13 6
6 14 5
6 15 9
7 8 5
7 9 9
7 10 7
7 11 4
7 12 4
7 13 6
7 14 9
7 15 5
8 9 5
8 10 3
8 11 6
8 12 2
8 13 3
8 14 6
8 15 4
9 10 5
9 11 4
9 12 6
9 13 4
9 14 4
9 15 5
10 11 5
10 12 2
10 13 9
10 14 8
10 15 5
11 12 8
11 13 4
11 14 3
11 15 9
12 13 5
12 14 9
12 15 2
13 14 4
13 15 5
14 15 6
0 0 0
--- End ---

*** File Description

Line 1: Total number of students n

Next n lines:
Student ID, Gender, Transfer student status
Gender (0: Male, 1: Female)
Transfer student (0: Regular, 1: Transfer)

Subsequent lines:
Format: a b x where a and b are students, and x indicates their
relationship.
The last line ends with "0 0 0".

** Run the program

We explain how to run the program "grouping_ils.exe" in Windows.
We assume that the file containing the above student information is data16.txt.

1. You put the executable file "grouping_ils.exe" and the text file "data16.txt" in the same folder.
   In the following example, assume these files are installed in the folder "C:\Users\user\Desktop\Group".

2. Run the command prompt.

3. Change the current working directory to the installed folder.
   For example:
   C:\Users\user> cd Desktop\Group

4. Run the executable file "grouping_ils.exe" with the data file.

   C:\Users\user\Desktop\Group> grouping.exe data16.txt > result16.csv

   To specify the execution time, use -t time (seconds). If no time is
   specified, the execution time is 120 seconds.
   In the following example, the calculation stops after 10 seconds and
   outputs the result:
   Example: If the file name in the above example is `data16.txt`:
      % ./grouping_ils -t 10 data16.txt

5. After a few minutes, the result is written result64.csv.



Output Example:
=======
0,4,7H,10,13,14,7 6 9 9 8 4 ,41.0,43,40,4,1,
1,4,1g,4g,6H,9,6 7 9 9 10 8 ,49.0,49,62,2,1,
2,4,0g,5gH,8,15,6 5 6 4 8 4 ,29.0,33,42,2,1,
3,4,2g,3g,11,12,8 4 6 6 10 8 ,40.0,42,42,2,0,
Total Value = 159.0
Minimum Compatibility = 4
Total Compatibility = 167
=======
From left to right:
Group number
Number of members in the group (m)
Student numbers of the m members. g indicates a girl, H indicates a
transfer student.
List of compatibilities within the group
Group's evaluation value (reduced by the lowest compatibility)
Total compatibility within the group
Minimum compatibility within the group
Number of girls
Number of boys
Number of transfer students
