
#include <map>
#include <cctype>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

struct Node
{
	char first[10];
	char second[10];
};

int main()
{
	int t, n, len1, len2;
	bool poss;
	bool decision, right;
	string A, B;
	string check1, check2;
	char F, S;

	bool hashVariable[26];
	bool hashTerminal[26];
	
	// Reset HashStates
	for(int i = 0; i < 26; i++) {
		hashVariable[i] = false;
		hashTerminal[i] = false;
	}
	
	printf("Number of Variables : ");
	cin >> n;
	
	for(int i = 0; i < n; i++) {
		printf("Variable %d : ", i+1);
		cin >> F;
		
		hashVariable[F-'A'] = true;
	}
	
	printf("Number of Terminal : ");
	cin >> n;
	
	for(int i = 0; i < n; i++) {
		printf("Terminal %d : ", i+1);
		cin >> F;
		
		hashTerminal[F-'a'] = true;
	}
	
	vector < pair <string, string > > V;
	printf("\n\n>> Use $ for Eplison\n\n");
	printf("How many productions are there : ");
	cin >> t;
	
	for(int i = 0; i < t; i++) {
		cin >> A >> B;
		
		// insert all the production LHS and RHS to array
		V.push_back(make_pair(A, B));
	}
	
	// Assume grammar be valid
	poss = true;
	decision = false;
	
	// Traverse all the productions
	for(int i = 0; i < t; i++) {
		
		check1 = V.at(i).first;		// LHS string
		check2 = V.at(i).second;	// RHS string
		
		len1 = check1.length();		// len of LHS Variable
		len2 = check2.length();		// len of RHS result
		
		// len of Variable is more than 1
		// len of result is more than 2
		// Varible is not upperCase
		if(len1 > 1 || len2 > 2) {
			poss = false;
			break;
		}// end if
		
		// Handle LHS
		if (check1[0] >= 'A' && check1[0] <= 'Z') {	// Valid Variable
			if(!hashVariable[check1[0] - 'A']) {	// but not in hashVariable set
				poss = false;
				break;
			}// end if
		}
		else {	// Not a Valid variable
			poss = false;
			break;
		}// end if
		
		// Handle RHS
		
		if(len2 == 2) {
			F = check2[0];	// first state
			S = check2[1];	// second state
			
			// Left Regular Grammar
			if(F >= 'a' && F <= 'z' && S >= 'A' && S <= 'Z') {		// Pattern possible
				if(!hashTerminal[F-'a'] || !hashVariable[S-'A']) {	// not valid
					poss = false;
					break;
				}
				else {
					if(decision) {			// decision already taken
						if(right) {			// and type is right, but left given
							poss = false;	// break;
							break;
						}// end if
					}
					else {					// decision not taken
						decision = true;	// TYPE DECIDED
						right = false;		// LEFT REGULAR
					}// end if
				}// end if
			}
			
			// Right Regular Grammar
			else if(F >= 'A' && F <= 'Z' && S >= 'a' && S <= 'z') {	// Pattern possible
				if(!hashVariable[F-'A'] || !hashTerminal[S-'a']) {	// not valid
					poss = false;
					break;
				}
				else {
					if(decision) {			// decision already taken
						if(!right) {		// and type is left, but right given
							poss = false;	// break;
							break;
						}// end if
					}
					else {					// decision not taken
						decision = true;	// TYPE DECIDED
						right = true;		// RIGHT REGULAR
					}// end if
				}// end if
			}
			
			// Both are terminals or variables
			else {
				poss = false;
				break;
			}// end if
		}
		
		// if len of result is 1
		else {
			F = check2[0];	// first state
			
			// if state is possible terminal
			if(((F >= 'a' && F <= 'z'))) {
				if(!hashTerminal[F-'a']) {	// But is not valid
					poss = false;
					break;
				}// end if
			}
			else if(F != '$') {	// not a terminal, neither an epsilon state
				poss = false;
				break;
			}// end if
		}// end if
		
	}// end for
	
	printf("\nResult : Given Grammar");
	if(poss) {
		printf(" a ");
	}
	else {
		printf(" not a ");
	}
	printf("Regular Grammar\n");
	
	return 0;
}
