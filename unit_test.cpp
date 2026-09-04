////////////////////////////////////////////////////////
// ECE 3574 Exercise: CMake using Catch - starter code
//
#define CATCH_CONFIG_MAIN  // This line tells Catch to provide a main() function
                           // - do this in one cpp file only
#include "catch.hpp"       // This line provides access to all Catch macros
                           // - do not modify catch.hpp
#include "treap.h"
#include <cassert>    
#include <cstdlib>

TEST_CASE("treap unit test1", "[treap]") {

	struct TreapNode *root = NULL; 
	root = insert(root, 50);
	
	TreapNode *res = search(root, 50);
	REQUIRE(res->key == 50);

}

// Utility functions first

// newNode
TEST_CASE("treap newnode test", "[treap]"){
	struct TreapNode *root = newNode(10); 

	REQUIRE(root->key == 10);
	REQUIRE(root->left == root->right);
	REQUIRE(root->left == NULL);
}

// rightRotate and leftRotate
TEST_CASE("treap right rotate", "[treap]"){
	// Set up tree 
	//     x
	//  y / \ a
	//z/ \ b
	struct TreapNode *x = newNode(10);
	struct TreapNode *y = newNode(20);
	struct TreapNode *z = newNode(30);
	struct TreapNode *a = newNode(40);
	struct TreapNode *b = newNode(50);

	x->left = y;
	x->right = a;
	y->left = z;
	y->right = b;

	struct TreapNode *newRoot = rightRotate(x);

	// Rotated tree:
	//     y
	//   z/ \x
	//     b/ \a

	REQUIRE(newRoot->key == 20); // y is new root
	REQUIRE(newRoot->left->key == 30); // z is left
	REQUIRE(newRoot->right->key == 10); // x is right
	REQUIRE(z->left == NULL); // z has no children
	REQUIRE(z->right == NULL);
	REQUIRE(x->left->key == 50);
	REQUIRE(x->right->key == 40); // x has b and a as children

}

// Left rotate
TEST_CASE("treap left rotate", "[treap]"){
	// Set up tree 
	//     x
	//  z / \ y
	//      a/ \b
	struct TreapNode *x = newNode(10);
	struct TreapNode *y = newNode(20);
	struct TreapNode *z = newNode(30);
	struct TreapNode *a = newNode(40);
	struct TreapNode *b = newNode(50);

	x->left = z;
	x->right = y;
	y->left = a;
	y->right = b;

	struct TreapNode *newRoot = leftRotate(x);

	// Rotated tree:
	//     y
	//   x/ \b
	//  z/ \a   

	REQUIRE(newRoot->key == 20); // y is new root
	REQUIRE(newRoot->left->key == 10); // x is left
	REQUIRE(newRoot->right->key == 50); // b is right
	REQUIRE(z->left == NULL); // z has no children
	REQUIRE(z->right == NULL);
	REQUIRE(x->left->key == 30);
	REQUIRE(x->right->key == 40); // x has z and a as children

}

// Insert
TEST_CASE("treap insert test", "[treap]"){

	srand(0); // For consistency

	struct TreapNode *root = NULL;

	// Base case
	root = insert(root, 10);
	REQUIRE(root->key == 10);

	// Add smaller node
	// Causes rotation
	root = insert(root, 5);
	REQUIRE(root->key == 5);
	REQUIRE(root->left == NULL);
	REQUIRE(root->right->key == 10);

	// Add larger node
	root = insert(root, 15);
	REQUIRE(root->key == 5);
	REQUIRE(root->right->key == 10);
	REQUIRE(root->right->right->key == 15);
}

// Search
TEST_CASE("treap search test", "[treap]"){
	// Base cases
	srand(0); // For consistency

	struct TreapNode *root = NULL;
	REQUIRE(search(root, 10) == root);

	root = insert(root, 50);
	REQUIRE(search(root, 50) == root);
	
	// Simple tree
	insert(root, 60);
	insert(root, 40);

	REQUIRE(search(root, 60) == root->right);
	REQUIRE(search(root, 40) == root->left);

	// More complicated tree
	insert(root, 30);
	insert(root, 20);
	insert(root, 50);
	insert(root, 80);
	REQUIRE(search(root, 50)->key == 50);
}

// Delete
TEST_CASE("treap basic delete test", "[treap]"){
	struct TreapNode *root = NULL;
	REQUIRE(deleteNode(root, 10) == NULL);

	// Simple tree
	//    10
	//  5/   \15
	//   \7 17/
	root = insert(root, 10);
	
	root->left = newNode(5);
	root->right = newNode(15);
	root->left->right = newNode(7);
	root->right->left = newNode(17);
	

	// Delete left node
	deleteNode(root, 5);
	REQUIRE(root->left->key == 7);
	REQUIRE(root->right->key == 15);

	// Delete right node
	deleteNode(root, 15);
	REQUIRE(root->left->key == 7);
	REQUIRE(root->right->key == 17);

	// Delete left again
	deleteNode(root, 7);
	REQUIRE(root->left == NULL);
	REQUIRE(root->right->key == 17);

}

// Delete with a more complicated tree
TEST_CASE("treap complicated delete test", "[treap]"){
	// Set up tree 
	//     x
	//  y / \ a
	//z/ \ b
	srand(0); // For consistency
	struct TreapNode *x = newNode(50);
	struct TreapNode *y = newNode(30);
	struct TreapNode *z = newNode(20);
	struct TreapNode *a = newNode(60);
	struct TreapNode *b = newNode(40);

	x->left = y;
	x->right = a;
	y->left = z;
	y->right = b;

	// Delete y
	auto deletedNode = deleteNode(x, 30);

	REQUIRE(x->right->key == 60); // right is still a
	REQUIRE(x->left->key == 40); // left is now b
	REQUIRE(x->left->left->key == 20); // child of b is now z
}