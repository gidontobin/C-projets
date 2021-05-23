/***************
 * Gidon Tobin
 * 320518020
 * 01
 * ex6
 ***************/

#ifndef _EX6_H_
#define _EX6_H_

struct Trin_Ari {
	int id;
	char* name;
    struct Trin_Ari *father;
	struct Trin_Ari *left;
	struct Trin_Ari *middle;
	struct Trin_Ari *right;
};
typedef struct Trin_Ari Trin_Ari;

void trinAriFamilyTree(Trin_Ari* root);

#endif