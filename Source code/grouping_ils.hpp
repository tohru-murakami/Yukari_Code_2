#ifndef GR_H
#define GR_H
#include <vector>
using namespace std;

class CRand {
public:
  // Constructor
  CRand(int seed = 1)
    : generator_(seed), distribution_(0, 65535) {}
  ~CRand(){}

  // Getter
  int get() { return distribution_(generator_); }
private:
  std::mt19937 generator_;
  std::uniform_int_distribution<> distribution_;
};

/*** Structure to handle group evaluation values, minimum compatibility, and total compatibility ***/
typedef struct gv
{
  double eval;
  int minCompatibility;
  int totalCompatibility;
} GroupValue;

typedef struct st
{
  int id;
  string studentNumber;
  int gender;
  int hennyu;
} Student;

// Group information
typedef struct gn
{
  int size;                     // Number of people in the group
  int totalCompatibility;       // Total compatibility
  int minCompatibility;         // Minimum compatibility
  int numMinCompatibility;      // Number of pairs with minimum compatibility
  double evaluation;            // Evaluation value
  int numGirls;                 // Number of girls
  int numBoys;                  // Number of boys
  int numH;                     // Number of transfer students
  bool feasible;                // True if constraints are met
} GI;



// // Return a vector containing a random permutation on {0,...,n-1}
// vector<int> random_permutation(int n);

// /*** Read data from file ***/
// int read_file(const string &filename);

// /******************************************************************/

// /*** Add student i to group k ***/
// int joinStudent(int k, int i);

// /*** Remove student i from group k
//      Returns 1 if the student exists, -1 if not ***/
// int removeStudent(int k, int i);

/*** Swap student s1 from group k1 with student s2 from group k2 ***/
/*** Returns 1 if the swap is successful, 0 if not ***/
int swap_students(int k1, int s1, int k2, int s2);

/*** Move student s1 from group k1 to group k2 ***/
/*** Returns 1 if successful, 0 if not ***/
int move_student(int k1, int s1, int k2);

/******************************************************************/



/*** make_initial_group: Create groups randomly ***/
void make_initial_group();

/*** Display list of information for group k ***/
void printGroup(int k);

/*** Print list of all groups ***/
void printAllGroup();



/*** Calculate evaluation value from compatibility ***/
double calc_evaluation(int s1, int s2);

/*** Evaluation value of group k ***/
//GroupValue evaluateGroup(int k);

/***
 * gr[]: Array of students, gsize: Number of elements in the array
 * Returns the evaluation value of the group
***/
double calc_group_evaluation(int *gr, int gsize);

// Update group information in groupInfo[MAX_NGROUP]
void update_groupInfo(int k);

/*********************************************************************/

// Return the difference in evaluation values after swapping student s1 from group k1 with student s2 from group k2
// Positive return value indicates an increase in evaluation value after the swap
double delta_by_swap(int k1, int s1, int k2, int s2);

// Return the difference in evaluation values after swapping (k1, s1) -> (k2, s2) -> (k3, s3)
// Positive return value indicates an increase in evaluation value after the swap
double delta_by_3swap(int k1, int s1, int k2, int s2, int k3, int s3);

/*** Simple local search ***/
int local_search_swap();

/*** Use 3swap to search for a better solution in the neighborhood
 *** Try try3swap 3-neighborhood solutions
 *** Move to the first found improved solution if first_find == true
 *** Move to the best improved solution if first_find == false
 *** Return 1 if there is such a neighborhood
 *** Return 0 if there is none ***/
int local_search_by_3swap(int try3swap, bool first_find);

/*** Iterated local search ***/
double iterated_local_search(int **best_grouping, int *best_size, CRand &mt, int default_distance, int try3swap, bool first_find);

// Perform random 2-swap times times
void random_swap(int times);

#endif
