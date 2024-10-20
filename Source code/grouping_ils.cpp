#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <vector>
#include <algorithm>
#include <tuple>
#include <ctime>
#include "grouping_ils.hpp"
#include <unistd.h>
using namespace std;

// If this is set to true, various output will be generated.
//bool DEBUG = true;
bool DEBUG = false;

/*****************************************************
 *
 *    Configurable parameters
 *
 *****************************************************/

// (1) Maximum value of peer compatibility
const int MAX_COMPATIBILITY = 10;

// (2) Number of people in one group (dissection team)
// If the class is not divisible by the number, groups of 1 less people is allowed.
const int STUDENTS_IN_GROUP = 4;

// (3) True when groups with single girl are allowed.
// One girl in a group of 3 or less is allowed.
const bool PermitGirlAlone = false;

// (4) True when groups with single boy are allowed.
// One boy in a group of 3 or less is allowed.
const bool PermitBoyAlone = false;

// (5) True if groups of all girls are allowed.
const bool PermitAllGirl = true;

// (6) True if groups of all boys are allowed.
const bool PermitAllBoy = true;

// (7) True if more than one transfer student is allowed in a group.
//const bool PermitTwoHennyu = false;

// (7) default value of maximum processing time in seconds.
double LIMIT_TIME = 300;

/*** End: Configurable parameters *********************/

// Penalty value of peer compatibility
double factor = 2.0;

// Number of repeats for 3rd depth neighbor search
// If this is set to 0, no 3rd depth neighbors will be searched.
int try3swap = 1;

// If true, the first found 3rd depth better neighbor will be selected.
// When false, the best neighbor will be selected.
bool first_find_in_3swap = true;

/*************************************************/
// Global variable (no configuration needed)

// the maximum number of students 
const int MAX_STUDENTS = 150;
// the maximum number of groups
const int MAX_NGROUP = 35;
// the maximum number of persons of groups
const int MAX_SIZE = 6;

const int DUMMY  = 10000;


// Array to store peer compatibility
int COMPATIBILITY[MAX_STUDENTS][MAX_STUDENTS];

// Array to store group assignment
int GROUPS[MAX_NGROUP][MAX_SIZE];

// Number of groups
int numGroups = 0;

// Number of students
int numStudents = 0;

// The minimum value of peer compatibilities in a group
int minimumCompatibility;

// Number of peers with the minimum compatibility value
int numMinCompatibility;

// Depth to the optimum solution
int inline default_distance() { return numGroups; }

// Number of feasible solutions
int NUMFEASIBLESOLUTION = 0;

/*************************************************/

Student STUDENTS[MAX_STUDENTS];

/*************************************************/

// Manage group information
GI groupInfo[MAX_NGROUP];

int best_grouping[MAX_NGROUP][MAX_SIZE];
int best_size[MAX_NGROUP];

// Set to true when any feasible solution is found．
bool FoundFeasibleSolution = false;

// seed of random number
unsigned int Seed;
/*************************************************/

typedef struct edge
{
  int group;
  int x;
  int y;
} Edge;

typedef struct gs
{
  int group;
  int id;
} GS;


/**  Auxiliary functions  *******************************************************/

// Generate random swaps within {0,...,n-1} and return as a vector.
vector<int> random_permutation(int n, CRand& mt)
{
  vector<int> rv;
  for (int i = 0; i < n; i++)
  {
    rv.push_back(i);
  }
  for (int i = 0; i < n-1; i++)
  {
    //auto num = mt.get();
    int num = mt.get();
    int j = (num % n-i) + i;
    int tmp = rv[i];
    rv[i] = rv[j];
    rv[j] = tmp;
  }
  return rv;
}

/**  end: Auxiliary functions  **************************************************/

/*** Read data from a file ***/
int read_file(const string &filename, Student *STUDENTS, int COMPATIBILITY[MAX_STUDENTS][MAX_STUDENTS])
{
  ifstream ifs(filename.c_str());
  int count_friendship[MAX_COMPATIBILITY + 1];

  if (ifs.fail())
  {
    cerr << "File does not exist.\n";
    exit(1);
  }

  ifs >> numStudents;           // Total number of students

  for (int i = 0; i < numStudents; i++)
  {
    string sn;  // student number
    int gn, hn; // gender, transfer
    ifs >> sn >> gn >> hn;
    Student st;
    st.id = i;
    st.studentNumber = sn;
    st.gender = gn;
    st.hennyu = hn;
    STUDENTS[i] = st;
  }

  // store the friendship level
  int p1, p2, v;
  for (int i = 0; i < numStudents; i++) COMPATIBILITY[i][i] = 0;
  while (ifs >> p1 >> p2 >> v)
  {
    if ((p1==0) && (p2==0) && (v==0)) return 0;
    if ((v <= 0) || (v > MAX_COMPATIBILITY))
    {
      cerr << "Irregal value of friendship" << endl;
      exit(1);
    }
    COMPATIBILITY[p1][p2] = COMPATIBILITY[p2][p1] = v;
    count_friendship[v]++;
  }
  return 1;
}
/*** End: read_file Read data from a file ***/

/*** Add student i to group k ***/
int joinStudent(int GROUPS[][MAX_SIZE], int k, int i)
{
  int j = 0;
  while (GROUPS[k][j] < numStudents)
  {
    j++;
  }
  GROUPS[k][j] = i;
  groupInfo[k].size++;

  return k;
}

/*** remove student i from group k
     return 1 when the student exists, else 0
 ***/
int removeStudent(int k, int i)
{
  int j;
  bool found = false;

  if (groupInfo[k].size == 0) return 0;

  for (j = 0; j < groupInfo[k].size; j++)
  {
    if (i == GROUPS[k][j])
    {
      found = true;
      break;
    }
  }

  if (found)
  {
    GROUPS[k][j] = DUMMY;
    groupInfo[k].size--;
    sort(GROUPS[k], GROUPS[k] + MAX_SIZE);
    return 1;
  }
  else
    return 0;
}





/*** swap student s1 in group k1 with s2 in k2 ***/
/*** return 1 when successful, else 0 ***/
int swap_students(int k1, int s1, int k2, int s2)
{
  if (k1 == k2) return 0;

  int s1_sucess = removeStudent(k1, s1);
  int s2_sucess = removeStudent(k2, s2);

  if (!s1_sucess && !s2_sucess) return 0;
  else if (!s1_sucess && s2_sucess)
  {
    joinStudent(GROUPS, k2, s2);
    return 0;
  }
  else if (s1_sucess && !s2_sucess)
  {
    joinStudent(GROUPS, k1, s1);
    return 0;
  }
  else
  {
    joinStudent(GROUPS, k1, s2);
    joinStudent(GROUPS, k2, s1);
    return 1;
  }
}

/*** move student s1 in group k1 to group k2 ***/
/*** return 1 when successful, else 0 ***/
int move_student(int k1, int s1, int k2)
{
  if (k1 == k2) return 0;

  int s1_sucess = removeStudent(k1, s1);

  if (!s1_sucess) return 0;
  else
  {
    joinStudent(GROUPS, k2, s1);
    return 1;
  }
}

/*** make_initial_group : generate groups by random assortment ***/
void make_initial_group(CRand &mt)
{
  // number of groups
  numGroups = numStudents / STUDENTS_IN_GROUP;
  if (numStudents % STUDENTS_IN_GROUP > 0) numGroups++;

  // initialize
  for (int k=0; k<numGroups; k++)
  {
    for (int i=0; i<MAX_SIZE; i++)
    {
      GROUPS[k][i] = DUMMY;
    }
  }

  // calculate number of students per group
  for (int k=0; k<numGroups; k++)
  {
    groupInfo[k].size = 0;
  }

  vector<int> rv = random_permutation(numStudents, mt);
  int s = 0;
  int k = 0;
  for (s=0; s < numStudents; s++)
  {
    joinStudent(GROUPS, k, rv[s]);
    if (k == numGroups - 1) k = 0;
    else k++;
  }
}  // End: make_initial_group


/*** Display list of group k ***/
void printGroupCsv(int k)
{
  int* vs = GROUPS[k];
  sort(vs, vs + groupInfo[k].size);
  // Group number and size
  printf("%d,%d,", k, groupInfo[k].size);
  // Member list
  for (int i = 0; i < groupInfo[k].size; i++)
  {
    int st = vs[i];
    printf("%d", st);
    if (STUDENTS[st].gender && STUDENTS[st].hennyu) printf("gH,");
    else if (STUDENTS[st].gender && !STUDENTS[st].hennyu) printf("g,");
    else if (!STUDENTS[st].gender && STUDENTS[st].hennyu) printf("H,");
    else printf(",");
  }
  // Insert a blank space for groups with one less member
  if (groupInfo[k].size < STUDENTS_IN_GROUP)
  {
    printf(" ,");
  }
  // Compatibility list within the group
  vector<int> edges;
  for (int i = 0; i < groupInfo[k].size; i++)
  {
    for (int j = i + 1; j < groupInfo[k].size; j++)
    {
      int s1 = GROUPS[k][i];
      int s2 = GROUPS[k][j];
      int r = COMPATIBILITY[s1][s2];
      edges.push_back(r);
    }
  }
  for (int i=0; i < (int)edges.size(); i++)
  {
    printf("%d ", edges[i]);
  }
  printf(",");

  printf("%.1f,%d,", groupInfo[k].evaluation, groupInfo[k].totalCompatibility);
  printf("%d,%d,%d,", groupInfo[k].numGirls, groupInfo[k].numBoys, groupInfo[k].numH);

  // Display NG for groups that violate the rules
  if (!groupInfo[k].feasible) printf("NG\n");
  else printf("\n");
}
/*** End : PrintGroupCsv ***/


/*** Print list of groups ***/
void printAllGroup()
{
  double tv = 0.0;
  int tc = 0;
  for (int k = 0; k < numGroups; k++)
  {
    //printGroup(k);
    printGroupCsv(k);
    tv += groupInfo[k].evaluation;
    tc += groupInfo[k].totalCompatibility;
  }

  printf("Total Value = %3.1f\n", tv);
  printf("Minimum Compatibility = %d\n", minimumCompatibility);
  //printf("Num of Minimum Compatibility = %d\n", numMinCompatibility);
  printf("Total Compatibility = %d\n", tc);
}
/*** End : PrintAllgroup ***/



/***
 * gr[]: Array of students, gsize: Number of elements in the array
 * Returns the evaluation value of the group
***/
double calc_group_evaluation(int *gr, int gsize)
{
  double val = 0.0;             // Evaluation value of the group

  for (int i = 0; i < gsize; i++)
  {
    for (int j = i + 1; j < gsize; j++)
    {
      int s1 = gr[i];
      int s2 = gr[j];
      val += calc_evaluation(s1, s2);
    }
  }

  // Lower the evaluation value of the group as a penalty if it violates constraints
  int ng = 0;
  int nb = 0;
  int nh = 0;
  for (int i = 0; i < gsize; i++)
  {
    Student s = STUDENTS[gr[i]];
    if (s.gender) ng++; else nb++;
    if (s.hennyu) nh++;
  }
  // Increase the penalty for violations of the constraints
  int penalty = 0;
  if (!PermitGirlAlone && (ng == 1) && (gsize >=4)) penalty++;
  if (!PermitBoyAlone && (nb == 1) && (gsize >=4)) penalty++;
  if (!PermitAllGirl && (nb == 0)) penalty++;
  if (!PermitAllBoy && (ng == 0)) penalty++;
  //if (!PermitTwoHennyu && (nh > 1)) penalty++;

  // Decrease the evaluation value by the penalty
  double eval;
  if (val >= 0) eval = val / (1 + penalty);  // <-- Reduction of evaluation
  else eval = val * (1 + penalty);           // <-- Reduction of evaluation
  return eval;
}
/*********************************************************************/

// Update group information in groupInfo[MAX_NGROUP]
void update_groupInfo(int k)
{
  double val = 0.0;             // Evaluation value of the group
  int mc = MAX_COMPATIBILITY;   // Minimum compatibility
  int num_mc = 0;               // Number of pairs with minimum compatibility
  int tc = 0;                   // Total compatibility
  int sz = 0;                   // Number of people

  for (int i = 0; i < MAX_SIZE; i++)
    if (GROUPS[k][i] < MAX_STUDENTS) sz++;

  groupInfo[k].size = sz;

  for (int i = 0; i < sz; i++)
  {
    for (int j = i + 1; j < sz; j++)
    {
      int s1 = GROUPS[k][i];
      int s2 = GROUPS[k][j];
      int f = COMPATIBILITY[s1][s2];
      if (f < mc)
      {
        mc = f;
      }
      tc += f;

      val += calc_evaluation(s1, s2);
    }
  }

  for (int i = 0; i < sz; i++)
    for (int j = i + 1; j < sz; j++)
    {
      int s1 = GROUPS[k][i];
      int s2 = GROUPS[k][j];
      int f = COMPATIBILITY[s1][s2];

      if (f == mc) num_mc++;
    }

  groupInfo[k].minCompatibility = mc;
  groupInfo[k].numMinCompatibility = num_mc;

  for (int i = 0; i < sz; i++)
    for (int j = i + 1; j < sz; j++)
    {
      int s1 = GROUPS[k][i];
      int s2 = GROUPS[k][j];

      if (s1 == s2)
      {
        printf("Student %d is doubled in Group %d\n", s1, k);
        printf("Seed = %u\n", Seed);
        exit(1);
      }
    }

  // Validate students
  int g = 0, b = 0, h = 0;
  for (int i = 0; i < sz; i++)
  {
    int s = GROUPS[k][i];
    Student st = STUDENTS[s];

    if (st.gender) g++;  else b++;
    if (st.hennyu) h++;
  }
  groupInfo[k].numGirls = g;
  groupInfo[k].numBoys = b;
  groupInfo[k].numH = h;

  // Lower the evaluation value of the group as a penalty if it violates constraints
  // Increase the penalty for violations of the constraints
  int penalty = 0;
  bool feasible = true;
  if (!PermitGirlAlone && (groupInfo[k].numGirls == 1) && (groupInfo[k].size >= 4))
  {
    penalty++;
    feasible = false;
  }
  if (!PermitBoyAlone && (groupInfo[k].numBoys == 1) && (groupInfo[k].size >= 4))
  {
    penalty++;
    feasible = false;
  }
  if (!PermitAllGirl && (groupInfo[k].numBoys == 0)) { penalty++; feasible = false; }
  if (!PermitAllBoy && (groupInfo[k].numGirls == 0)) { penalty++; feasible = false; }
  //if (!PermitTwoHennyu && (groupInfo[k].numH > 1)) { penalty++; feasible = false; }

  // Decrease the evaluation value by the penalty
  if (val >= 0) groupInfo[k].evaluation = val / (1 + penalty);  // <-- Reduction of evaluation
  else groupInfo[k].evaluation = val * (1 + penalty);

  groupInfo[k].totalCompatibility = tc;
  groupInfo[k].numGirls = g;
  groupInfo[k].numBoys = b;
  groupInfo[k].numH = h;
  groupInfo[k].feasible = feasible;
}
// End: update_groupInfo


// Return the difference in evaluation values after swapping student s1 from group k1 with student s2 from group k2
// Positive return value indicates an increase in evaluation value after the swap
double delta_by_swap(int k1, int s1, int k2, int s2)
{
  // Evaluation value of the groups before the swap
  double before = groupInfo[k1].evaluation + groupInfo[k2].evaluation;

  // Generate groups after the swap
  int group_k1[MAX_SIZE];
  int group_k2[MAX_SIZE];

  int j = 0;
  for (int i=0; i < groupInfo[k1].size; i++)
  {
    int s = GROUPS[k1][i];
    if (s != s1)
    {
      group_k1[j] = s;
      j++;
    }
  }
  group_k1[groupInfo[k1].size - 1] = s2;

  j = 0;
  for (int i=0; i < groupInfo[k2].size; i++)
  {
    int s = GROUPS[k2][i];
    if (s != s2)
    {
      group_k2[j] = s;
      j++;
    }
  }
  group_k2[groupInfo[k2].size - 1] = s1;

  // Evaluation value after the swap
  double after = calc_group_evaluation(group_k1, groupInfo[k1].size) +
    calc_group_evaluation(group_k2, groupInfo[k2].size);
  // Return the difference in evaluation values
  return after - before;
} // end delta_by_swap

// Return the difference in evaluation values after moving student s1 from group k1 to group k2
// Positive return value indicates an increase in evaluation value after the move
double delta_by_move(int k1, int s1, int k2)
{
  // Evaluation value of the groups before the move
  double before = groupInfo[k1].evaluation + groupInfo[k2].evaluation;

  // Generate groups after the move
  int group_k1[MAX_SIZE];
  int group_k2[MAX_SIZE];

  int j = 0;
  for (int i=0; i < groupInfo[k1].size; i++)
  {
    int s = GROUPS[k1][i];
    if (s != s1)
    {
      group_k1[j] = s;
      j++;
    }
  }

  for (int i=0; i < groupInfo[k2].size; i++)
  {
    int s = GROUPS[k2][i];
    group_k2[i] = s;
  }
  group_k2[groupInfo[k2].size] = s1;

  // Evaluation value after the move
  double after = calc_group_evaluation(group_k1, groupInfo[k1].size - 1) +
    calc_group_evaluation(group_k2, groupInfo[k2].size + 1);
  // Return the difference in evaluation values
  return after - before;
} // end delta_by_move


// Return the difference in evaluation values after swapping (k1, s1) -> (k2, s2) -> (k3, s3)
// Positive return value indicates an increase in evaluation value after the swap
double delta_by_3swap(int k1, int s1, int k2, int s2, int k3, int s3)
{
  // Evaluation value of the groups before the swap
  double before = groupInfo[k1].evaluation + groupInfo[k2].evaluation + groupInfo[k3].evaluation;
  // Generate groups after the swap
  int group_k1[STUDENTS_IN_GROUP];
  int group_k2[STUDENTS_IN_GROUP];
  int group_k3[STUDENTS_IN_GROUP];

  // s3 -> k1
  int j = 0;
  for (int i=0; i < groupInfo[k1].size; i++)
  {
    int s = GROUPS[k1][i];
    if (s != s1)
    {
      group_k1[j] = s;
      j++;
    }
  }
  group_k1[groupInfo[k1].size - 1] = s3;

  // s1 -> k2
  j = 0;
  for (int i=0; i < groupInfo[k2].size; i++)
  {
    int s = GROUPS[k2][i];
    if (s != s2)
    {
      group_k2[j] = s;
      j++;
    }
  }
  group_k2[groupInfo[k2].size - 1] = s1;

  // s2 -> k3
  j = 0;
  for (int i=0; i < groupInfo[k3].size; i++)
  {
    int s = GROUPS[k3][i];
    if (s != s3)
    {
      group_k3[j] = s;
      j++;
    }
  }
  group_k3[groupInfo[k3].size - 1] = s2;

  // Evaluation value after the swap
  double after = calc_group_evaluation(group_k1, groupInfo[k1].size)
    + calc_group_evaluation(group_k2, groupInfo[k2].size)
    + calc_group_evaluation(group_k3, groupInfo[k3].size);

  // Return the difference in evaluation values
  return after - before;
} // end calc_eval_by_3swap


/*** Simple local search ***/
int local_search_swap(CRand &mt)
{
  // Return true if a local optimum solution is found
  bool found_local_opt = false;
  do
  {
    // Evaluate all neighboring swaps
    vector<pair<GS,GS> > exchange_pair;
    double max_difference = 0.0;
    int k1, k2;
    int p1, p2;

    for (k1 = 0; k1 < numGroups; k1++)
    {
      for (k2 = k1+1; k2 < numGroups; k2++)
      {
        if (groupInfo[k1].size == groupInfo[k2].size)
        {
          // Check 2-swap neighbors as the group sizes are the same
          for (p1 = 0; p1 < groupInfo[k1].size; p1++)
          {
            for (p2 = 0; p2 < groupInfo[k2].size; p2++)
            {
              int s1 = GROUPS[k1][p1];
              int s2 = GROUPS[k2][p2];

              // Difference in evaluation value after the swap
              double delta = delta_by_swap(k1, s1, k2, s2);
              GS gs1, gs2;
              if (delta >= max_difference && delta > 0)
              {
                if (delta > max_difference)
                {
                  max_difference = delta;
                  exchange_pair.clear();
                }
                gs1.group = k1;
                gs1.id = s1;
                gs2.group = k2;
                gs2.id = s2;
                exchange_pair.push_back(make_pair(gs1, gs2));
              }
            }
          }
        } // end 2-swap neighbors (groups k1 and k2 have the same size)
        else
        {
          // Check 1-move neighbors
          if (groupInfo[k1].size - groupInfo[k2].size == 1)
          {
            // Move a student from k1 to k2
            for (int p = 0; p < groupInfo[k1].size; p++)
            {
              int s1 = GROUPS[k1][p];

              // Difference in evaluation value after the move
              double delta = delta_by_move(k1, s1, k2);
              GS gs1, gs2;
              if (delta >= max_difference && delta > 0)
              {
                if (delta > max_difference)
                {
                  max_difference = delta;
                  exchange_pair.clear();
                }
                gs1.group = k1;
                gs1.id = s1;
                gs2.group = k2;
                gs2.id = -1;
                exchange_pair.push_back(make_pair(gs1, gs2));
              }
            }
          }
          else
          {
            // Move a student from k2 to k1
            for (int p = 0; p < groupInfo[k2].size; p++)
            {
              int s2 = GROUPS[k2][p];
              // Difference in evaluation value after the move
              double delta = delta_by_move(k2, s2, k1);
              GS gs1, gs2;
              if (delta >= max_difference && delta > 0)
              {
                if (delta > max_difference)
                {
                  max_difference = delta;
                  exchange_pair.clear();
                }
                gs1.group = k2;
                gs1.id = s2;
                gs2.group = k1;
                gs2.id = -1;
                exchange_pair.push_back(make_pair(gs1, gs2));
              }
            } // for p
          } // end else
        } // end 1-move neighbors check
      } // end for k2
    } // Check all neighbors

    // exchange_pair contains the pair of neighbors with the highest evaluation
    // If the second element is -1, it means moving a student
    if (exchange_pair.empty())
    {
      found_local_opt = true;
      if (DEBUG)
      {
        printf("------------\n");
        printf("       Found Local Optima by 2-swap.\n");
      }
    }
    else
    {
      int p = mt.get() % exchange_pair.size();
      GS gs1 = exchange_pair[p].first;
      GS gs2 = exchange_pair[p].second;
      k1 = gs1.group;
      k2 = gs2.group;
      int s1 = gs1.id, s2 = gs2.id;

      if (DEBUG)
      {
        if (s2 == -1)
          printf("       Move (%d,%d)  --> %d; %.1f\n", k1, s1, k2, max_difference);
        else
          printf("       Swap (%d,%d) <--> (%d,%d); %.1f\n", k1, s1, k2, s2, max_difference);
      }

      if (s2 == -1)
      {
        // Move student
        if (DEBUG)
        {
          // Check if s1 is already in group k2
          for (int j=0; j<groupInfo[k2].size; j++)
          {
            if (s1 == GROUPS[k2][j])
            {
              printf("Student %d is already in Group %d\n", s1, k2);
              exit(1);
            }
          }
        }
        move_student(k1, s1, k2);
      }
      else
      {
        // Swap students (k1,s1) <==> (k2,s2)
        if (DEBUG)
        {
          // Check if s1 is already in group k2
          for (int j=0; j<groupInfo[k2].size; j++)
          {
            if (s1 == GROUPS[k2][j])
            {
              printf("Student %d is already in Group %d\n", s1, k2);
              exit(1);
            }
          }
          // Check if s2 is already in group k1
          for (int j=0; j<groupInfo[k1].size; j++)
          {
            if (s2 == GROUPS[k1][j])
            {
              printf("Student %d is already in Group %d\n", s2, k1);
              exit(1);
            }
          }
        }
        // Swap s1 and s2
        swap_students(k1, s1, k2, s2);
      } // End of student exchange

      update_groupInfo(k1);
      update_groupInfo(k2);

      //if (DEBUG) printAllGroup();
    }
  } while (!found_local_opt);
  return 1;
} /* End: local_search */


/*** Using 3-swap to find a better solution in the neighborhood
 *** Try 3-swap neighborhood for try3swap times
 *** Move to the first improvement found if first_find == true
 *** Move to the best improvement found if first_find == false
 *** Return 1 if a better neighborhood is found
 *** Return 0 otherwise ***/
int local_search_by_3swap(int try3swap, bool first_find, CRand &mt)
{
  if (try3swap == 0) return 0;
  if (DEBUG) printf("          Try 3-swap\n");
  double max_difference = 0.0;
  int k1, k2, k3;
  int p1, p2, p3;
  vector<tuple<GS, GS, GS> > exchange_triple;

  // Number of 3-Swap iterations
  int IterationTimeof3Swap = 0;

  while (IterationTimeof3Swap < try3swap)
  {
    IterationTimeof3Swap++;

  // Number of 3-Swap iterations
    k1 = mt.get() % numGroups;
    do {
      k2 = mt.get() % numGroups;
    } while (k1 == k2);
    do {
      k3 = mt.get() % numGroups;
    } while ((k3 == k1) || (k3 == k2));

    // Selected groups k1, k2, k3
    for (p1 = 0; p1 < groupInfo[k1].size; p1++)
    {
      for (p2 = 0; p2 < groupInfo[k2].size; p2++)
      {
        for (p3 = 0; p3 < groupInfo[k3].size; p3++)
        {
          int s1 = GROUPS[k1][p1];
          int s2 = GROUPS[k2][p2];
          int s3 = GROUPS[k3][p3];

          // Calculate the difference in evaluation value after the swap
          double delta1 = delta_by_3swap(k1, s1, k2, s2, k3, s3);
          double delta2 = delta_by_3swap(k3, s3, k2, s2, k1, s1);
          double delta = max(delta1, delta2);

          if (first_find)
          {
            // if first_find == true
            if (delta > 0)
            {
              if (delta1 > delta2)
              {
                // s1 -> s2 -> s3
                swap_students(k1, s1, k2, s2);
                swap_students(k2, s2, k3, s3);
              }
              else
              {
                // s1 -> s3 -> s2
                swap_students(k1, s1, k2, s2);
                swap_students(k1, s1, k3, s3);
              }
              // Found an improved solution, so end
              return 1;
            }
          }
          else
          {
            if (delta > 0)
            {
              if (delta >= max_difference)
              {
                if (delta > max_difference)
                {
                  max_difference = delta;
                  exchange_triple.empty();
                }
                GS gs1, gs2, gs3;
                gs1.group = k1;
                gs1.id = s1;
                gs2.group = k2;
                gs2.id = s2;
                gs3.group = k3;
                gs3.id = s3;

                if (delta1 > delta2)
                {
                  exchange_triple.push_back(make_tuple(gs1, gs2, gs3));
                }
                else
                {
                  exchange_triple.push_back(make_tuple(gs3, gs2, gs1));
                }
              }
            }
          }
        }
      }
    }
  } // End of search by 3-Swap

  // If first_find is 0, terminate here (no improvement found)
  if (first_find) return 0;

  // exchange_tuple contains the 3-tuple with the highest evaluation value
  if (!exchange_triple.empty())
  {
    // Randomly select one and swap
    int p = mt.get() % exchange_triple.size();
    GS gs1 = get<0>(exchange_triple[p]);
    GS gs2 = get<1>(exchange_triple[p]);
    GS gs3 = get<2>(exchange_triple[p]);
    int k1 = gs1.group, s1 = gs1.id;
    int k2 = gs2.group, s2 = gs2.id;
    int k3 = gs3.group, s3 = gs3.id;

    if (DEBUG)
    {
      printf("------------\n");
      printf("       3-Swap (%d,%d) -> (%d,%d) -> (%d,%d)\n", k1, s1, k2, s2, k3, s3);
    }

    swap_students(k1, s1, k2, s2);
    swap_students(k2, s2, k3, s3);

    return 1;
  }
  else
  {
    // No improvement found
    if (DEBUG)
    {
      printf("------------\n");
      printf("          Found Local Optima by 3-swap\n");
    }
    return 0;
  } // End of 3-Swap
} // End: local_search_by_3swap

/*********************************************************************/
/*********************************************************************/
/*********************************************************************/
/*********************************************************************/


/*** Calculate evaluation value from compatibility between s1 and s2 ***/
double calc_evaluation(int s1, int s2)
{
  if (s1 == s2) return 0;
  int f = COMPATIBILITY[s1][s2];
  int d = max(0, minimumCompatibility - f + 1);

  f = f - factor * d;

  return f;
}
/*********************************************************************/


// Perform random 2-swap times times
void random_swap(int times, CRand &mt)
{
  if (DEBUG) printf(" random_swap: %d\n", times);

  for (int p = 0; p < times; p++)
  {
    // Randomly select 2 groups
    int k1 = mt.get() % numGroups, k2;
    do {
      k2 = mt.get() % numGroups;
    } while (k1 == k2);

    int p1 = mt.get() % groupInfo[k1].size;
    int p2 = mt.get() % groupInfo[k2].size;
    int s1 = GROUPS[k1][p1];
    int s2 = GROUPS[k2][p2];

    int SWAP_SUCESS = swap_students(k1, s1, k2, s2);
    if (!SWAP_SUCESS)
    {
      printf("Error\n");
      exit(1);
    }
  }
}

/*** Iterated Local Search ***/
double iterated_local_search(int best_grouping[][MAX_SIZE], int best_size[], CRand &mt, int try3swap, bool first_find)
{
  int maximumTotalCompatibility = 0;
  double maximumTotalValue = 0.0;
  double previous_tc = -100.0;

  clock_t iteration_start = clock();       // Start time
  clock_t iteration_end = iteration_start; // End time

  bool initialize = true;

  /*** Termination condition ***/
  // Terminate if time exceeds LIMIT_TIME seconds
  while ((double)(iteration_end - iteration_start) / CLOCKS_PER_SEC < LIMIT_TIME)
  {
    if (initialize)
    {
      make_initial_group(mt);
      initialize = false;

      for (int k = 0; k < numGroups; k++) update_groupInfo(k);

      minimumCompatibility = MAX_COMPATIBILITY;
      numMinCompatibility = 0;

      for (int k = 0; k < numGroups; k++)
        if (groupInfo[k].minCompatibility < minimumCompatibility)
        {
          minimumCompatibility = groupInfo[k].minCompatibility;
        }
      for (int k = 0; k < numGroups; k++)
      {
        if (groupInfo[k].minCompatibility == minimumCompatibility)
        {
          numMinCompatibility += groupInfo[k].numMinCompatibility;
        }
      }

      if (DEBUG)
      {
        printf("Initial Grouping\n");
        for (int k = 0; k < numGroups; k++) update_groupInfo(k);
        printAllGroup();
      }
    }
    // Initialization of groups and calculation of minimumCompatibility and numMinCompatibility completed


    // Start of local search
    for (int k = 0; k < numGroups; k++) update_groupInfo(k);

    int not_local_opt = 1;
    do
    {
      // Move to local optimal solution
      local_search_swap(mt);
      // Try 3-swap
      not_local_opt = local_search_by_3swap(try3swap, first_find_in_3swap, mt);

      if (DEBUG)
      {
        if (not_local_opt) printf("Found better 3-neighbor\n");
        for (int k = 0; k < numGroups; k++) update_groupInfo(k);
        //printAllGroup();
      }
    } while (not_local_opt);

    // Check current solution
    int current_mc = MAX_COMPATIBILITY;
    int current_tc = 0;
    double current_tv = 0.0;

    // Check minimum compatibility and total compatibility of current grouping
    for (int k = 0; k < numGroups; k++)
    {
      update_groupInfo(k);

      current_mc = min(current_mc, groupInfo[k].minCompatibility);
      current_tc += groupInfo[k].totalCompatibility;
      current_tv += groupInfo[k].evaluation;
    }

    // Check if the solution is feasible
    bool feasible = true;
    for (int k = 0; k < numGroups; k++)
    {
      if (!groupInfo[k].feasible)
      {
        feasible = false;
        break;
      }
    }

    // Update new solution as the best solution if it is feasible or no feasible solution has been found yet,
    // and if it has a higher minimum compatibility or the same minimum compatibility but higher total compatibility
    if ((feasible || !FoundFeasibleSolution)
        &&
        ((minimumCompatibility < current_mc)
        ||
         ((minimumCompatibility == current_mc) && (maximumTotalCompatibility < current_tc)))
        )
    {
      if (DEBUG) printAllGroup();

      // Update as the best solution if it is feasible
      if (feasible)
      {
        // Found one feasible solution
        NUMFEASIBLESOLUTION++;
        FoundFeasibleSolution = true;
      } // if feasible

      minimumCompatibility = current_mc;
      maximumTotalCompatibility = current_tc;
      maximumTotalValue = current_tv;

      // Update best_grouping
      for (int k=0; k<MAX_NGROUP; k++)
        for (int i=0; i<MAX_SIZE; i++)
          best_grouping[k][i] = DUMMY;

      for (int k=0; k<numGroups; k++)
      {
        for (int i=0; i<groupInfo[k].size; i++)
        {
          best_grouping[k][i] = GROUPS[k][i];
        }
        best_size[k] = groupInfo[k].size;
      }
    } // // end if compatibility values are good
    else
    {
      if (DEBUG)
      {
        if (!feasible)
          printf("       Infeasible Solution\n");
        else
          printf("       Not Improved\n");
      }
    }

    // Move to a neighborhood with distance step from the current solution
    // If returning to the previous local solution, jump to a farther solution
    int distance = default_distance();
    if (current_tc == previous_tc)
    {
      distance += distance;
    }
    else
    {
      distance = default_distance();
      previous_tc = current_tc;
    }

    random_swap(distance, mt);

    // End time
    iteration_end = clock();
  }
  return maximumTotalValue;
}



int main(int argc, char** argv)
{
  string filename;
  // int best_grouping[MAX_NGROUP][MAX_SIZE];
  // int best_size[MAX_NGROUP];
  random_device rd;

  Seed = rd();
  //Seed = 1066235738; // For debugging
  CRand mt(Seed);

  if (DEBUG) printf("Seed = %u\n", Seed);

  int opt;
  opterr = 0;

  while ((opt = getopt(argc, argv, "t:")) != -1)
  {
    // Repeat until no more command line options
    switch (opt) {
    case 't':
      LIMIT_TIME = atof(optarg);
      break;

    default:
      // If unspecified option is passed
      printf("Usage: %s [-t time] filename\n", argv[0]);
      break;
    }
  }
  if (argc <= 1)
  {
    cerr << "Please give a problem filename." << endl;
    return 1;
  }
  else
  {
    filename = string(argv[optind]);
  }

  read_file(filename, STUDENTS, COMPATIBILITY);

  cout << filename << endl;

  // initialize
  for (int k=0; k<MAX_NGROUP; k++)
  {
    for (int i=0; i<MAX_SIZE; i++)
    {
      best_grouping[k][i] = DUMMY;
    }
  }

  // Iterated Local Search
  iterated_local_search(best_grouping, best_size, mt, try3swap, first_find_in_3swap);

  // Restore and display the optimal groups
  for (int k=0; k<MAX_NGROUP; k++)
  {
    for (int i=0; i<MAX_SIZE; i++)
    {
      GROUPS[k][i] = DUMMY;
    }
  }
  for (int k=0; k<numGroups; k++)
  {
    for (int i=0; i < best_size[k]; i++)
    {
      GROUPS[k][i] = best_grouping[k][i];
    }
    groupInfo[k].size = best_size[k];
  }
  for (int k=0; k<numGroups; k++) update_groupInfo(k);

  printAllGroup();
  //printf("%d feasible solutions are found.\n", NUMFEASIBLESOLUTION);

  return 0;
}
