# Yukari Data Manager

The **Yukari Data Manager** is a spreadsheet created with Apple Numbers, designed to help organize Yukari Questionnaire Data, compile it for the Yukari Code team optimization program, and review the optimized team assignments.

1. **Compiling Data for the Optimization Program**  
   This tool helps organize and prepare the necessary data files to run optimization calculations.

2. **Reviewing Optimized Team Assignments**  
   After the optimization process, the spreadsheet allows you to review the results and make adjustments based on the optimized output.

## How to open the Yukari Data Manager

- **macOS**: Open the file directly in the Apple Numbers application.
- **Windows and macOS (via web)**: You can also access the file using Apple Numbers through iCloud at iCloud.com.

## Settings

1. Compile the Student List  
   The serial numbers start from 0 (not 1). For enhanced confidentiality, the serial numbers may be randomized.

2. Define Matching Matrices  
   Define matching as numbers 1–10 (larger is better).

Note: The following tables are used internally for calculations: **Compatibility**, **Preference Matching**, **Commitment Matching**, **Preferences**, and **Commitment**.

## When the Number of Students Exceeds the Table Limits

1. Expand the rows and columns of the tables (including the tables for internal calculations) to match the number of students.
2. Verify that the formulas are correctly applied to the newly added cells.

## Questionnaire Data

1. Retrieve the questionnaire data from Google Forms and export it as an Excel document.
2. Clean the data.
3. Copy the cleaned data and paste it into the **Questionnaire Data** tab of the spreadsheet.
4. Leave any missing data fields blank (do not use placeholders).

## Setting Restrictions

You can adjust values in the spreadsheet by adding negative or positive numbers (ranging from -10 to +10) in the relevant cells. Some samples are provided below.

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
2. Copy the Compatibility Code (excluding the header) from the spreadsheet and paste it into the file.
3. Use the `grep` function to replace all tab characters (`\t`) with newlines (`\n`).
4. Use the `grep` function again to replace any multiple newlines (`\n+`) with a single newline (`\n`).
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

1. Choose the best team assignment like below.
2. Copy the assignment and paste it into the blue box in the **Team Assignment** tab.

```
0,4,20,43g,105g,107,10 7 10 8 8 10 ,53.0,53,2,2,0,
1,4,10g,56,77g,112,10 6 6 8 8 7 ,41.0,45,2,2,0,
2,4,78,81,92,117H,6 7 10 10 9 10 ,50.0,52,0,4,1,
3,4,1g,44g,57,85,9 10 9 10 10 10 ,58.0,58,2,2,0,
4,4,30,47g,61,113gH,9 9 9 10 8 10 ,55.0,55,2,2,1,
5,4,14g,23,38,96g,8 9 9 9 8 9 ,52.0,52,2,2,0,
6,4,9g,26,32,80g,10 7 10 9 9 9 ,54.0,54,2,2,0,
7,4,67g,91,120gH,123H,7 10 9 7 8 7 ,48.0,48,2,2,2,
8,4,2,7g,21g,35,10 6 8 7 7 8 ,44.0,46,2,2,0,
9,4,5,27,69g,110g,10 9 8 9 9 7 ,52.0,52,2,2,0,
10,4,6g,29,60g,99,10 7 9 9 7 7 ,49.0,49,2,2,0,
11,4,12g,19,63g,127H,8 10 9 8 8 8 ,51.0,51,2,2,1,
12,4,18g,82g,104,116H,10 8 9 10 8 10 ,55.0,55,2,2,1,
13,4,37g,62,95g,98,9 7 8 10 10 7 ,51.0,51,2,2,0,
14,4,42,90,93,114H,6 7 6 10 7 9 ,41.0,45,0,4,1,
15,4,48,52g,86g,122H,8 10 7 9 8 10 ,52.0,52,2,2,1,
16,4,76,84,106g,125gH,9 9 8 9 8 9 ,52.0,52,2,2,1,
17,4,89,102g,111,119gH,9 8 10 7 10 10 ,54.0,54,2,2,1,
18,4,55g,64,71,87g,9 8 8 7 10 9 ,51.0,51,2,2,0,
19,4,36g,40,49,51g,8 8 10 9 6 8 ,47.0,49,2,2,0,
20,4,3g,54,101,118gH,10 10 10 10 8 9 ,57.0,57,2,2,1,
21,4,25,39,94g,103g,10 10 10 10 6 7 ,51.0,53,2,2,0,
22,4,41,66g,73,121gH,8 10 10 9 9 8 ,54.0,54,2,2,1,
23,4,65,74g,75,109g,9 7 10 10 10 8 ,54.0,54,2,2,0,
24,4,0,45g,53g,59,9 7 10 7 9 7 ,49.0,49,2,2,0,
25,4,24,83g,88g,97,9 6 10 9 10 10 ,52.0,54,2,2,0,
26,4,31g,34g,100,126H,10 8 10 8 7 8 ,51.0,51,2,2,1,
27,4,13,50,72g,124gH,10 10 8 7 10 8 ,53.0,53,2,2,1,
28,4,8,11g,28,68g,9 10 8 10 10 10 ,57.0,57,2,2,0,
29,4,16g,17g,33g,108g,10 10 9 10 9 9 ,57.0,57,4,0,0,
30,4,4,15g,70g,79,10 8 10 10 10 8 ,56.0,56,2,2,0,
31,4,22,46g,58,115gH,9 10 7 9 7 10 ,52.0,52,2,2,1,
```

---

## Note

The sample data in this file are either randomized or AI-generated and do not contain any individual's personal information.
