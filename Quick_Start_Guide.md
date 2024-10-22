# Quick Start Guide
This is a quick guide to help you install and use Yukari Code 2.

## Set the Working Directory

Create a directory (folder) at any location for team optimization. In this guide, we'll assume you create a working directory named "Yukari" on the Desktop.

The path to the Yukari directory will be as follows:

- macOS: `/Users/(username)/Desktop/Yukari`
- Windows: `C:/Users/(username)/Desktop/Yukari`

## Download Codes, Examples, and Documents

Download and unzip all the files from the repository.

## Put executable code

Copy the executable file `grouping_ils` (for macOS) or `grouping_ils.exe` (for Windows) to the top level of the Yukari directory.

Also, copy the sample data file `data16.txt` to the Yukari directory.

## Run a Test

Open a terminal application:

- macOS: Terminal.app
- Windows: Command Prompt

Navigate to the Yukari directory:

```
% cd (path to Yukari directory)
```

Execute Yukari Code.

On macOS:

```
% grouping_ils data16.txt
```

On Windows:

```
> grouping_ils.exe data16.txt
```

After about 5 minutes, you will get a result similar to this:

```
% ./grouping_ils data16.txt 
data16.txt
0,4,0g,5gH,10,13,6 6 7 4 7 9 ,37.0,39,2,2,1,
1,4,6H,8,11,15,4 6 9 6 4 9 ,34.0,38,0,4,1,
2,4,1g,4g,7H,9,6 6 9 5 10 9 ,45.0,45,2,2,1,
3,4,2g,3g,12,14,8 6 5 10 6 9 ,44.0,44,2,2,0,
Total Value = 160.0
Minimum Compatibility = 4
Total Compatibility = 166
```

## Compile the Source Code (macOS & Linux Users)

For macOS and Linux users, you can compile the source code using `make`. Follow these steps:

### 1. Install the Build Tools

Before proceeding, make sure you have the necessary build tools installed. On most systems, this will include a C or C++ compiler (such as `gcc` or `clang`) and `make`.

#### macOS

  Install the Xcode command-line tools by running the following command in Terminal:

  ```
  % xcode-select --install
  ```

#### Linux

Ensure that `gcc` and `make` are installed. You can do this with the following commands:

  ```
  % sudo apt update
  % sudo apt install build-essential
  ```

### 2. Navigate to the Source Code Directory

Go to the directory where the source code files are located. For example, if the source code is in the `Yukari` directory, run:

```
% cd (path to Yukari directory)/Source\ code
```

### 3. Run the `make` Command

In the terminal, run the `make` command to compile the source code. The `Makefile` in the directory should automate the compilation process:

```
% make
```

If everything is set up correctly, this will generate an executable file called `grouping_ils` in the same directory.

### 4. Confirm the Compilation

After the `make` process finishes, you can check that the executable was created by listing the contents of the directory:

```
% ls
```

You should see the `grouping_ils` executable file.

### 5. Run the Program

You can now run the compiled executable as described in the test flight section:

```
% ./grouping_ils data16.txt
```
