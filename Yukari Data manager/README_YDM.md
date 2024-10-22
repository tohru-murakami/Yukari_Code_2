# Yukari Data Manager

The **Yukari Data Manager** is a spreadsheet created with Apple Numbers, designed to help organize **Yukari Questionnaire Data**, compile it for the Yukari Code team optimization program, and review the optimized team assignments.

## How to Use the Yukari Data Manager

- **macOS**: Open the file directly in the Apple Numbers application.
- **Windows and macOS (via web)**: You can also access the file using Apple Numbers through iCloud at iCloud.com.

---

## **How to Use This Spreadsheet**

The spreadsheet, titled **"Yukari Data Manager"**, is designed to support the following tasks:

1. **Compiling Data for the Optimization Program**  
   This tool helps organize and prepare the necessary data files to run optimization calculations.
   
2. **Reviewing Optimized Team Assignments**  
   After the optimization process, the spreadsheet allows you to review the results and make adjustments or selections based on the optimized output.

---

## **Settings**

1. **Compile the Student List**  
   The serial numbers start from 0 (not 1).  
   For enhanced confidentiality, the student list may be randomized.

2. **Define Matching Matrices**  
   The following tables are used internally for calculations: **Compatibility**, **Preference Matching**, **Commitment Matching**, **Preferences**, and **Commitment**.

---

## **When the Number of Students Exceeds the Table Limits**

1. Expand the rows and columns of the tables to match the number of students.
2. Verify that the formulas are correctly applied to the newly added cells.

---

## **Questionnaire Data**

1. Retrieve the questionnaire data from Google Forms and export it as an Excel document.
2. Clean the data.
3. Copy the cleaned data and paste it into the **Questionnaire Data** tab of the spreadsheet.
4. Leave any missing data fields blank (do not use placeholders).

---

## **Restrictions**

You can adjust values in the spreadsheet by adding negative or positive numbers (ranging from -10 to +10) in the relevant cells. Details are provided below.

---

## **Compiling Data for the Optimization Program**

Use any text editor to compile data for the optimization program.

---

### **Creating Header Data**

1. Create a plain text file named **"header.txt"**.
2. On the first line, type the total number of students.
3. Copy the entire **Property Code** column (excluding the header) from the spreadsheet.
4. Paste it on the second line of the **header.txt** file.
5. Save the file.

---

### **Creating Compatibility Data**

1. Create a plain text file named **"compatibility.txt"**.
2. Copy the Compatibility Code (excluding the header) from the spreadsheet and paste it into the file.
3. Use the `grep` function to replace all tab characters (`\t`) with newlines (`\n`).
4. Use the `grep` function again to replace any multiple newlines (`\n+`) with a single newline (`\n`).
5. Save the file.

---

### **Compiling Data for the Optimization Program**

1. Create a plain text file named **"data.txt"**.
2. Copy the contents of **header.txt** and paste them into **data.txt**.
3. Append the contents of **compatibility.txt** to the last line of **data.txt**.
4. On the final line of **data.txt**, type `0 0 0`.
5. Save the file.
6. Run the optimization program using **data.txt**.

---

## **Reviewing Optimized Team Assignments**

### **Team Assignment**

1. Choose the best team assignment.
2. Copy the assignment and paste it into the blue box in the **Team Assignment** tab.

---

## **Restriction Examples**

### **Suppressing Multiple Transfer Students on the Same Team**

To ensure that multiple transfer students are not assigned to the same team:

- Input `-4` or lower in the cells corresponding to each transfer student.

### **Distributing High-Achieving Students Across Teams**

To evenly distribute high-achieving students across teams:

1. Define the number of teams (N).
2. Identify the top N students based on their performance.
3. Input `-4` or lower in the cells for every pair of these top students to prevent them from being assigned to the same team.

---

## **Note**

The sample data in this file are either randomized or AI-generated and do not contain any individual's personal information.
