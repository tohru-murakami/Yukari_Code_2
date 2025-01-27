# Yukari Data Manager

The **Yukari Data Manager** is a spreadsheet created with Apple Numbers, designed to help organize Yukari Preference Questionnaire Data, compile it for the Yukari Code team optimization program, and review the optimized team assignments.

1. **Compiling Data for the Optimization Program**  
   This tool helps organize and prepare the necessary data files to run optimization calculations.

2. **Reviewing Optimized Team Assignments**  
   After the optimization process, the spreadsheet allows you to review the results and make adjustments based on the optimized output.

## How to open the Yukari Data Manager

- **macOS**: Open the file directly in the Apple Numbers application.
- **Windows and macOS (via web)**: You can also access the file using Apple iCloud Numbers through at [iCloud.com](https://www.icloud.com).

## Settings

1. Compile the Student List  
   The serial numbers start from 0 (not 1). For enhanced confidentiality, the serial numbers may be randomized.

2. Define Matching Matrices  
   Define matching as numbers 1–10 (larger is better).

### Note ###
- For team assignments, you use the following tabels : **Student list**, **Matching Matrices**, **Questionnaire Data**, **Restrictions**, **Compatibility Code**, and **Team Assignment**. 

- Other tables are used internally for calculations: **Compatibility**, **Preference Matching**, **Commitment Matching**, **Preferences**, and **Commitment**.

## When the Number of Students Exceeds the Table Limits

The Yukari Data Manager is designed to accommodate class sizes of up to 160 students. If your class size exceeds this limit, you can adjust the spreadsheet as follows:

1. Expand the rows and columns of all tables (including those used for internal calculations) to match the increased number of students.

2. Ensure that all formulas are accurately extended to cover the newly added cells.

## Questionnaire Data

1. Retrieve the questionnaire data from Google Forms as an Excel document.
2. Clean the data.
3. Copy the cleaned data and paste it into the **Questionnaire Data** tab of the spreadsheet.
4. Leave any missing data fields blank (do not use placeholders).

## Setting Restrictions

You can adjust peer compatibility by adding negative or positive numbers (ranging from -10 to +10) in the relevant cells. Some samples are provided below.

### Suppressing Multiple Transfer Students on the Same Team

To ensure that multiple transfer students are not assigned to the same team:

- Input `-4` or lower in the cells corresponding to each transfer student.

### Distributing High-Achieving Students Across Teams

To evenly distribute high-achieving students across teams:

1. Define the number of teams (N).
2. Identify the top N students based on their performance.
3. Input `-4` or lower in the cells for every pair of these top students to prevent them from being assigned to the same team.

## Compiling Data for the Optimization Program

Use any text editor to compile data for the optimization program.

### Creating Header Data

1. Create a plain text file named **"header.txt"**.
2. On the first line, type the total number of students.
3. Copy the entire **Property Code** column (excluding the header) from the spreadsheet.
4. Paste it on the second line of the **header.txt** file.
5. Save the file.

### Creating Compatibility Data

1. Create a plain text file named **"compatibility.txt"**.
2. Copy the **Compatibility Code** (excluding the header) from the spreadsheet and paste it into the file.
3. Use the `grep` function to replace any multiple tab characters (`[\t\n]+`) with single newlines (`\n`).
4. Use the `grep` function again to replace any blank lines (`^\n`) with nothing.
5. Save the file.

### Compiling Data for the Optimization Program

1. Create a plain text file named **"data.txt"**.
2. Copy the contents of **header.txt** and paste them into **data.txt**.
3. Append the contents of **compatibility.txt** to the last line of **data.txt**.
4. On the final line of **data.txt**, type `0 0 0`.
5. Save the file.
6. Run the optimization program using **data.txt**.

```
% ./grouping_ils data.txt
```

## Reviewing Optimized Team Assignments

1. Choose the best team assignment from **result.txt** like below.
2. Copy the assignment and paste it into the blue box in the **Team Assignment** tab.

```
0,4,1,44g,57,85g,8 9 8 9 10 10 ,54.0,54,2,2,0,
1,4,3g,20g,101g,118gH,7 10 10 7 7 8 ,49.0,49,4,0,1,
2,4,5g,59,67g,76,10 9 10 9 6 10 ,52.0,54,2,2,0,
3,4,14,23g,38g,94,7 7 6 7 6 6 ,33.0,39,2,2,0,
4,4,35g,68g,78g,113gH,10 6 7 10 10 10 ,51.0,53,4,0,1,
5,4,0,4g,53g,119H,6 6 9 7 7 8 ,39.0,43,2,2,1,
6,4,10g,52,120H,123gH,9 10 8 7 8 6 ,46.0,48,2,2,2,
7,4,16g,17g,33,55,10 10 10 10 10 10 ,60.0,60,2,2,0,
8,4,9g,40,49,90g,9 10 9 9 7 9 ,53.0,53,2,2,0,
9,4,83,88,95,97,9 9 10 10 9 10 ,57.0,57,0,4,0,
10,4,12,63,69g,99g,9 10 6 10 10 10 ,53.0,55,2,2,0,
11,4,27g,50,60g,82,9 6 6 10 10 6 ,41.0,47,2,2,0,
12,4,22,39,58,124H,7 10 8 6 6 8 ,41.0,45,0,4,1,
13,4,43g,66g,105,107,6 7 6 7 10 8 ,40.0,44,2,2,0,
14,4,46,86,110,122H,9 10 9 10 10 9 ,57.0,57,0,4,1,
15,4,25g,98g,103,109,7 10 10 6 6 7 ,42.0,46,2,2,0,
16,4,6,29g,36,51g,10 6 6 8 6 10 ,40.0,46,2,2,0,
17,4,65,87g,91g,114H,10 7 9 9 8 10 ,53.0,53,2,2,1,
18,4,48,56,112,116H,8 6 7 8 6 8 ,39.0,43,0,4,1,
19,4,21,45,72g,77g,6 7 6 7 6 6 ,30.0,38,2,2,0,
20,4,11,47g,61g,108,9 7 7 9 6 10 ,46.0,48,2,2,0,
21,4,31g,34g,100,126H,8 6 10 6 7 8 ,41.0,45,2,2,1,
22,4,7g,54,89g,102,7 7 8 10 8 8 ,48.0,48,2,2,0,
23,4,2,93,111g,115gH,7 6 6 9 6 6 ,32.0,40,2,2,1,
24,4,19,41g,73,121gH,6 6 7 10 9 7 ,41.0,45,2,2,1,
25,4,15g,18,30g,79,9 7 10 7 10 8 ,51.0,51,2,2,0,
26,4,24g,64,71g,80,7 6 10 7 7 7 ,42.0,44,2,2,0,
27,4,42,74,75g,127gH,6 7 7 10 6 7 ,39.0,43,2,2,1,
28,4,8,13g,28,37g,10 10 10 10 10 10 ,60.0,60,2,2,0,
29,4,70,81g,92,117gH,9 10 10 10 9 10 ,58.0,58,2,2,1,
30,4,26g,32,62g,96,9 10 10 10 10 10 ,59.0,59,2,2,0,
31,4,84g,104g,106g,125gH,9 8 7 9 9 8 ,50.0,50,4,0,1,
```

---

## Note

The sample data in this file are either randomized or AI-generated and do not contain any individual's personal information.
