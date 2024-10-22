# Quick Start Guide
Following is a quick guide to install and use Yukari Code 2.

## Set working directory

Let meke a directory (folder) at a any place for team optimization. Lets assume we have the working directory named "Yukari" at Desktop.

Path to Yukari directory will be following:

- macOS: /Users/username/Desktop/Yukari
- Windows: C:/Users/username/Desktop/Yukari
- Linux: /home/username/Desktop/Yukari

## Download codes, examples and ducuments

Download files from this repository to Yukari directory.

## Put executable code

Copy the executable code "grouping_ils" (macOS) or "grouping_ils.exe" (Windoes) to the top of Yukari directory.

Copy the sample data "data 16.txt" to Yukari directory.

## Do a test flight

Open terminal application.

- macOS: Terminal.app
- Windows: Command Prompt
- Linux: Terminal

Move to Yukari directory.

```
% cd (path to Yukari directory)
```

Execute Yukari Cole.

macOS and Linux:

```
(username@machinename) ~ % grouping_ils data16.txt
```

Windows:

```
C:\Users\(username)> grouping_ils.exe data16.txt
```

After 5 minute you will get a result like this:

```
% ./grouping_ils -t 10 data16.txt
data16.txt
0,4,2g,3g,12,14,8 6 5 10 6 9 ,44.0,44,2,2,0,
1,4,0g,5gH,10,13,6 6 7 4 7 9 ,37.0,39,2,2,1,
2,4,1g,4g,7H,9,6 6 9 5 10 9 ,45.0,45,2,2,1,
3,4,6H,8,11,15,4 6 9 6 4 9 ,34.0,38,0,4,1,
Total Value = 160.0
Minimum Compatibility = 4
Total Compatibility = 166
```

