#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

//debug function - not necessary
template <typename K, typename V>
ostream& operator<<(ostream& out, const map<K, V> &m) {
    out << "[ ";
    for (auto it = m.begin(); it != m.end(); it++) {
        out << "[" << it->first << "," << it->second << "] ";
    }
    out << "]";
    return out;
}

/* Map to be used for memoization

Each map in memo has another map attached. The first map we'll call data.
Data represents a set of numbers where the mapped value is the quantity of the key value present in the set. (same as elsewhere in this program).
    For example, memo[3, 1, 0] is a set with three 1's and one 2.
The second map we will call summap.
Summap is a map that tracks how many different subsets add to a sum. The sum is the key and the mapped value is the number of subsets.
    Continuing the example, memo[3, 1, 0][3] would be 2. Since there are two subsets of [3, 1, 0] that add up to 3. [1, 1, 1] and [1, 2, 0].
*/
map<map<int, int>, map<int, int>> memo;

/*hasLookup function
Checks if the map Data is in our memoization map already.
The default value is 0, so we can't use brackets. Since this is also the "fail" condition for when a subset can't sum to t.
So, .find is used since that won't pick up false positives.
*/
bool hasLookup(map<int, int> &data, int t) {
    //Returns true if: data is in memo && sum t is in the summap of Data.
    return memo.find(data) != memo.end() && memo[data].find(t) != memo[data].end();
}

/* countSubsets recursive function
Checks if this has already been calculated.
Then checks if the target is 0, meaning the sum has been reached, < 0, which means the target won't be reached.
Then it will do two things
    *Make a new dataset, d, which is missing the smallest number present.
    *Recurse on d with each possible quantity of smallest numbers > 1. Subtracting the values from t.
    
    For example, if the smallest value is 1, and we have 5 1s, we would recurse on d 5 times. 
    In the first, t would be the same. This represents having zero 1's in our subset. 
    In the second, t would be t - 1. Which represents having one 1 in our subset.
    In the third, t would be t - 2. Which represents having two 1's in our subset.
    And so on until we get to t - 5, which represents having all five 1's in our subset.

    It returns the recursions, which will be how many subsets reach the required sum.
*/
int countSubsets(int target, map<int, int> data) {
    //Checks if data and target have values calculated.
    if (hasLookup(data, target)) {
        return memo[data][target];  //return previously calculated value.
    }
    /*  If the target is 0, this subset's sum == t
        Store 1 then return 1. */
    if (target == 0) {
        memo[data][target] = 1;
        return 1;
    }
    /*  if the target < 0, this subset's sum > t.
        So there is no point in adding more numbers to this subset.
        It is impossible to add to t from this point.
        So, store 0, then return 0.  */
    if (target < 0 || data.size() == 0) {
        memo[data][target] = 0;
        return 0;
    }

    auto leftMost = data.begin();
    int key = leftMost->first;      //stores the value of the smallest value in the map.
    int value = leftMost->second;   //stores how many of those ^^ values are in the map

    map<int, int> d = data; 
    d.erase(key);   //makes a new temp map, which will not have that smallest value.

    //The number of subsets in this Data that add up to sum must include subsets without the current value.
    memo[data][target] += countSubsets(target, d);
    
    int sum = 0;
    /*  For each iteration (will run once per removed value)
            Add the removed value to sum and insert it into the subset.
            Then Recurse
                The new target is oldTarget - sum.
                The new d is Data with that smallest value removed.
                Subset will change each iteration to have an increasing quantity of the removed value.
            it will store the number of subsets that add to the sum it finds after recursing.
    For example, if 1 was the value removed and there were 2 1's:
        The first recursion's target would be 6. The subset would contain a single 1.
        The second recursion's target would be 5. The subset would contain two 1's.
    */
    for (int i = 1; i <= value; i++) {
        sum += key;
        memo[data][target] += countSubsets(target - sum, d);
    }
    return memo[data][target]; //returns the calculated value.
}

/* read_input function
Reads the input file. 
Initializes the values needed on each line of input and calls the recursive function. 
Then prints the output file.
*/
void read_input(string filename)
{
    ifstream input(filename);
    ofstream output;
    output.open("output.txt");

    //Shouldn't be needed
    if(!input.is_open()) 
        cout << "No file found!" << endl << endl;

    int variable = 0;
    string temp = "";

    //First line dictating number of inputs isn't necessary.
    //Will run for each line of inputs
    while (getline(input, temp)) {
        vector<int> vec;
        istringstream line(temp);

        //Adds every number to the vector.
        while(line >> variable)
            vec.push_back(variable);

        //Ensures we don't do anything for the first line. (Which would only have one value)
        if(vec.size() > 1) {
            map<int, int> data; //stores the actual values.
            int t = vec[0]; //target
            //largest number, this actually isn't even used.
            //int n = vec[1];

            //Goes through the vector, skipping t and what should be n. Adds the values to data.
            //We actually don't need
            for(int i = 2; i < vec.size(); i++)
                data[i - 1] = vec[i];

            //prints to output file
            output << countSubsets(t, data);
            output << endl;
        }
    }
    //Close files, finished.
    input.close();
    output.close();
}

int main() {
    read_input("input.txt");
    return 0;
}