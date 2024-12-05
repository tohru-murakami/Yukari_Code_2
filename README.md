![Banner](https://github.com/tohru-murakami/Yukari_Code_2/blob/main/Images/DALL·E%202024-10-25%2010.54.30%20-%20A%20bright,%20cheerful%20manga-style%20banner%20image%20representing%20team%20optimization%20through%20the%20concept%20of%20'red%20threads%20of%20fate,'%20featuring%20four%20main%20character.jpeg?raw=true)

# Yukari Code 2

Yukari Code is a team assignment program that utilizes a heuristic local search combinatorial optimization algorithm based on peer-to-peer compatibility.

You can jump-start your team assignment process using executable files (available for macOS and Windows), sample data, a sample questionnaire, and a data management tool (Yukari Data Manager, formatted as an Apple Numbers spreadsheet).

For Linux, you can compile an executable from the source code.

## Changes from Yukari Code 1

The Yukari Code 1 was a private version intended for internal review. In Yukari Code 2, the calculation has been modified to complete within the specified time. The criteria for a good group division have been changed. The number of transfer students in a group is no longer considered.

## The problem this program solves

The task is to create groups of m students from the class of n students. The "compatibility" between students is given as a number from 1 to `MAX_COMPATIBILITY`. A larger number indicates a "better relationship."

For example, the goal is to create groups that satisfy the following conditions:

1. Each group has `m` or `m-1` members.
2. Groups with only one girl or one boy are not allowed, except in groups of three where one can be alone.
3. A "good group assignment" is defined as:
   - The group with the largest "minimum compatibility" within the group.
   - If the "minimum compatibility" is the same, the group with the largest "total compatibility" is preferred.

## Assumptions

1. There are more boys than girls.
2. If girls cannot be alone in a group, the number of girls is even. (If the number of girls is odd, please add a dummy student.)

## Preparing Student Data

Prepare a file as follows:

Example:

--- Start ---
```
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
0 1 4
0 2 3
0 3 9
0 4 3
0 5 6
0 6 2
0 7 2
0 8 5
0 9 7
0 10 6
0 11 1
0 12 3
0 13 7
0 14 7
0 15 6
1 2 4
1 3 6
1 4 6
1 5 4
1 6 7
1 7 6
1 8 5
1 9 9
1 10 7
1 11 3
1 12 5
1 13 4
1 14 5
1 15 5
2 3 8
2 4 6
2 5 5
2 6 3
2 7 8
2 8 3
2 9 5
2 10 5
2 11 4
2 12 6
2 13 3
2 14 5
2 15 7
3 4 9
3 5 9
3 6 6
3 7 6
3 8 4
3 9 4
3 10 7
3 11 6
3 12 10
3 13 4
3 14 6
3 15 5
4 5 1
4 6 9
4 7 5
4 8 7
4 9 10
4 10 7
4 11 7
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
```
--- End ---

## File Description

- Line 1: 
  - Total number of students `n`
- Next n lines:
  - Student ID, Gender, Transfer student status
    - Gender (`0`: Male, `1`: Female)
    - Transfer student (`0`: Regular, `1`: Transfer)
- Subsequent lines:
  - Format: `a b x` 
  - where `a` and `b` are students, and `x` indicates their relationship.
- The last line ends with "`0 0 0`".

## Pre-configuration of the program

In the file grouping_ils.cpp, there is a section titled "`Configurable Parameters`." Adjust the following variables according to your objectives:

(1) `MAX_COMPATIBILITY`: The maximum value for compatibility. In the following example, it is 10:

```
const int MAX_COMPATIBILITYFRIENDSHIP = 10;
```

(2) `STUDENT_IN_GROUP`: The number of students per group. If the total number is not divisible, groups with one less member are created. In this example, groups of 4 or 3 members are created:

```
const int STUDENT_IN_GROUP = 4;
```

(3) `PermitGirlAlone`: Set to true if you allow groups with only one girl, false otherwise. In the following example, groups with only one girl are not allowed:

```
const bool PermitGirlAlone = false;
```

(4) `PermitBoyAlone`: Set to true if you allow groups with only one boy, false otherwise. In the following example, groups with only one boy are not allowed:

```
const bool PermitBoyAlone = false;
```

(5) `PermitAllGirl`: Set to true to allow all-girl groups:

```
const bool PermitAllGirl = false;
```

(6) `PermitAllBoy`: Set to true to allow all-boy groups:

```
const bool PermitAllBoy = true;
```

(Note) Variables set with true or false might not function correctly as they have not been thoroughly tested. Please contact us if you notice any issues.

(7) `LIMIT_TIME`: The time (in seconds) allowed for searching for a solution. The loop terminates if the time exceeds this value. In the following example, it stops after 120 seconds:

```
double LIMIT_TIME = 120;
```

## Compilation

Use the make command.

Example:

```
% make
```

This generates the executable file `grouping_ils`. 

Run it as follows:

```
% ./grouping_ils filename
```

To specify the execution time, use `-t` time (seconds). If no time is specified, the `LIMIT_TIME` defined in the source file is used.

In the following example, the calculation stops after `10` seconds and outputs the result:

Example: If the file name in the above example is `data16.txt`:

```
% ./grouping_ils -t 10 data16.txt
```


Output Example:

```
0,4,7H,10,13,14,7 6 9 9 8 4 ,41.0,43,40,4,1,
1,4,1g,4g,6H,9,6 7 9 9 10 8 ,49.0,49,62,2,1,
2,4,0g,5gH,8,15,6 5 6 4 8 4 ,29.0,33,42,2,1,
3,4,2g,3g,11,12,8 4 6 6 10 8 ,40.0,42,42,2,0,
Total Value = 159.0
Minimum Compatibility = 4
Total Compatibility = 167
```

From left to right:


- Group number
- Number of members in the group (`m`)
- Student numbers of the m members. `g` indicates a girl, - `H` indicates a transfer student.
- List of compatibilities within the group
- Group's evaluation value (reduced by the lowest compatibility)
- Total compatibility within the group
- Minimum compatibility within the group
- Number of girls
- Number of boys
- Number of transfer students


## Contributions

The source codes, sample data, and this README (Time-stamp: <2018-05-22 16:00:18 arakit>) were written by [Toru Araki](https://github.com/arakit0328) (arakit) . Japanese in the codes and README were translated to English by [Tohru Murakami](https://github.com/tohru-murakami). The repository at GitHub including these files and other supplimentary files were compiled by Tohru Murakami.
