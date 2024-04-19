/* main.cpp
 * date: April 19th, 2024
 * Author: Alex Dai, Aarush Ganji
 * utlns: zdai03, aganji01
 * Project 4 - Gerp
 *
 * description: Driver code for gerp. 
 */

#include "gerp.h"

using namespace std;

void abort(string error_message);

/* main
 * purpose: initialize gerp object, receive and check input directory & output
 *          file from the user.
 * arguments: argc: number of command-line arguments
 *            argv: array of pointers to C-style strings representing the
 *            command-line arguments
 * returns: return 0 upon successful execution
 * effects: none
 */
int main(int argc, char *argv[])
{
    // terminate program if not enough arguments specified.
    if (not (argc == 3))
    {
        abort("Usage: ./gerp inputDirectory outputFile");
    }

    //initialize and call gerp
    Gerp gerp;
    
    gerp.run(argv[1], argv[2]);

    return 0;
}

/* abort
 * purpose: output error message and terminate program
 * arguments: error message
 * returns: none
 * effects: terminates program with EXIT_FAILURE
 */
void abort(string error_message)
{
    // display error message
    cerr << error_message << endl;

    exit(EXIT_FAILURE);
}