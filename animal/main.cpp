// FILE: animal.cxx
// An animal-guessing program to illustrate the use of the binary tree toolkit.
// From chapter 10 of Main/Savitch, Data Structures and Algorithms in C++
// Revised/compressed by Cate Sheller, March 2002

#include <stdlib.h>     // Provides EXIT_SUCCESS
#include <iostream>    // Provides cout
#include <iomanip>    // Provides std::setw
#include <cstdlib>   // Provides NULL, std::size_t
#include <string>      // Provides string class

bool inquire(const char query[ ]);

void eat_line( );

template <class Item>
    class binary_tree_node
    {
    public:
	// TYPEDEF
	typedef Item value_type;
	// CONSTRUCTOR
	binary_tree_node(
	    const Item& init_data = Item( ),
	    binary_tree_node* init_left = NULL,
	    binary_tree_node* init_right = NULL
	)
	{
      	    data_field = init_data;
    	    left_field = init_left;
    	    right_field = init_right;
   	}
   	// MODIFICATION MEMBER FUNCTIONS
   	Item& data( ) { return data_field; }
   	binary_tree_node*& left( ) { return left_field; }
   	binary_tree_node*& right( ) { return right_field; }
   	void set_data(const Item& new_data) { data_field = new_data; }
   	void set_left(binary_tree_node* new_left) { left_field = new_left; }
   	void set_right(binary_tree_node* new_right) { right_field = new_right; }
   	// CONST MEMBER FUNCTIONS
   	const Item& data( ) const { return data_field; }
   	const binary_tree_node* left( ) const { return left_field; }
   	const binary_tree_node* right( ) const { return right_field; }
   	bool is_leaf( ) const
   	    { return (left_field == NULL) && (right_field == NULL); }
    private:
    	Item data_field;
    	binary_tree_node *left_field;
    	binary_tree_node *right_field;
    };
    // NON-MEMBER FUNCTIONS for the binary_tree_node<Item>:
    template <class Process, class BTNode>
    void inorder(Process f, BTNode* node_ptr);

    template <class Process, class BTNode>
    void preorder(Process f, BTNode* node_ptr);

    template <class Process, class BTNode>
    void postorder(Process f, BTNode* node_ptr);

    template <class Item, class SizeType>
    void print(const binary_tree_node<Item>* node_ptr, SizeType depth);

    template <class Item>
    void tree_clear(binary_tree_node<Item>*& root_ptr);

    template <class Item>
    binary_tree_node<Item>* tree_copy(const binary_tree_node<Item>* root_ptr);

    template <class Item>
    std::size_t tree_size(const binary_tree_node<Item>* node_ptr);

    template <class Process, class BTNode>
    void inorder(Process f, BTNode* node_ptr)
    {
        if (node_ptr != NULL)
        {
            inorder(f, node_ptr->left( ));
            f( node_ptr->data( ) );
            inorder(f, node_ptr->right( ));
        }
    }

    template <class Process, class BTNode>
    void postorder(Process f, BTNode* node_ptr)
    {
        if (node_ptr != NULL)
        {
            postorder(f, node_ptr->left( ));
            postorder(f, node_ptr->right( ));
            f(node_ptr->data( ));
        }
    }

    template <class Process, class BTNode>
    void preorder(Process f, BTNode* node_ptr)
    {
        if (node_ptr != NULL)
        {
            f( node_ptr->data( ) );
            preorder(f, node_ptr->left( ));
            preorder(f, node_ptr->right( ));
        }
    }

    template <class Item, class SizeType>
    void print(const binary_tree_node<Item>* node_ptr, SizeType depth)
    {
        if (node_ptr != NULL)
        {
            print(node_ptr->right( ), depth+1);
            std::cout << std::setw(4*depth) << ""; // Indent 4*depth spaces.
            std::cout << node_ptr->data( ) << std::endl;
            print(node_ptr->left( ),  depth+1);
        }
    }

    template <class Item>
    void tree_clear(binary_tree_node<Item>*& root_ptr)
    {
        if (root_ptr != NULL)
        {
            tree_clear( root_ptr->left( ) );
            tree_clear( root_ptr->right( ) );
            delete root_ptr;
            root_ptr = NULL;
        }
    }

    template <class Item>
    binary_tree_node<Item>* tree_copy(const binary_tree_node<Item>* root_ptr)
    {
    	binary_tree_node<Item> *l_ptr;
    	binary_tree_node<Item> *r_ptr;
        if (root_ptr == NULL)
            return NULL;
        else
        {
            l_ptr = tree_copy( root_ptr->left( ) );
            r_ptr = tree_copy( root_ptr->right( ) );
            return new binary_tree_node<Item>(root_ptr->data(), l_ptr, r_ptr);
        }
    }

    template <class Item>
    size_t tree_size(const binary_tree_node<Item>* node_ptr)
    {
        if (node_ptr == NULL)
            return 0;
        else
            return 1+tree_size(node_ptr->left())+tree_size(node_ptr->right());
    }

// PROTOTYPES for functions used by this game program:

void ask_and_move(binary_tree_node<string>*& current_ptr);
// Precondition: current_ptr points to a non-leaf node in a binary taxonomy tree.
// Postcondition: The question at the current node has been asked. The current
// pointer has been shifted left (if the user answered yes) or right
// (for a no answer).

binary_tree_node<string>* beginning_tree( );
// Postcondition: The function has created a small taxonomy tree. The return
// value is the root pointer of the new tree.

void instruct( );
// Postcondition: Instructions for playing the game have been printed to the
// screen.

void learn(binary_tree_node<string>*& leaf_ptr);
// Precondition: leaf_ptr is a pointer to a leaf in a taxonomy tree. The leaf
// contains a wrong guess that was just made.
// Postcondition: Information has been elicited from the user, and the tree has
// been improved.

void play(binary_tree_node<string>* current_ptr);
// Precondition: current_ptr points to the root of a binary taxonomy tree with
// at least two leaves.
// Postcondition: One round of the animal game has been played, and maybe the
// tree has been improved.


int main( )
{
    binary_tree_node<string> *taxonomy_root_ptr;
    instruct( );
    taxonomy_root_ptr = beginning_tree( );
    do
        play(taxonomy_root_ptr);
    while (inquire("Shall we play again?"));

    cout << "Thank you for teaching me a thing or two." << endl;

    return EXIT_SUCCESS;
}

void ask_and_move(binary_tree_node<string>*& current_ptr)
{
    cout << current_ptr->data( );
    if (inquire(" Please answer:"))
        current_ptr = current_ptr->left( );
    else
        current_ptr = current_ptr->right( );
}

binary_tree_node<string>* beginning_tree( )
{
    binary_tree_node<string> *root_ptr;
    binary_tree_node<string> *child_ptr;
    const string root_question("Are you a mammal?");
    const string left_question("Are you bigger than a cat?");
    const string right_question("Do you live underwater?");
    const string animal1("Kangaroo");
    const string animal2("Mouse");
    const string animal3("Trout");
    const string animal4("Robin");

    // Create the root node with the question “Are you a mammal?”
    root_ptr = new binary_tree_node<string>(root_question);
    // Create and attach the left subtree.
    child_ptr = new binary_tree_node<string>(left_question);
    child_ptr->set_left( new binary_tree_node<string>(animal1) );
    child_ptr->set_right( new binary_tree_node<string>(animal2) );
    root_ptr->set_left(child_ptr);
    // Create and attach the right subtree.
    child_ptr = new binary_tree_node<string>(right_question);
    child_ptr->set_left( new binary_tree_node<string>(animal3) );
    child_ptr->set_right( new binary_tree_node<string>(animal4) );
    root_ptr->set_right(child_ptr);

    return root_ptr;
}

void instruct( )
{
    cout << "Let's play!" << endl;
    cout << "You pretend to be an animal, and I try to guess what you are.\n";
}

void learn(binary_tree_node<string>*& leaf_ptr)
{
    string guess_animal;    // The animal that was just guessed
    string correct_animal;  // The animal that the user was thinking of
    string new_question;    // A question to distinguish the two animals

    // Set strings for the guessed animal, correct animal and a new question.
    guess_animal = leaf_ptr->data( );
    cout << "I give up. What are you? " << endl;
    getline(cin, correct_animal);
    cout << "Please type a yes/no question that will distinguish a" << endl;
    cout << correct_animal << " from a " << guess_animal << "." << endl;
    cout << "Your question: " << endl;
    getline(cin, new_question);

    // Put the new question in the current node, and add two new children.
    leaf_ptr->set_data(new_question);
    cout << "As a " << correct_animal << ", " << new_question << endl;
    if (inquire("Please answer"))
    {
        leaf_ptr->set_left( new binary_tree_node<string> (correct_animal) );
        leaf_ptr->set_right( new binary_tree_node<string> (guess_animal) );
    }
    else
    {
        leaf_ptr->set_left( new binary_tree_node<string> (guess_animal) );
        leaf_ptr->set_right( new binary_tree_node<string> (correct_animal) );
    }
}

void play(binary_tree_node<string>* current_ptr)
{
    cout << "Think of an animal, then press the return key.";
    eat_line( );

    while (!current_ptr->is_leaf( ))
        ask_and_move(current_ptr);

    cout << ("My guess is " + current_ptr->data( ) + ". ");
    if (!inquire("Am I right?"))
        learn(current_ptr);
    else
        cout << "I knew it all along!" << endl;
}

bool inquire(const char query[ ])
{
    char answer;
    do
    {
        cout << query << " [Yes or No]" << endl;
        cin >> answer;
        answer = toupper(answer);
        eat_line( );
    }
    while ((answer != 'Y') && (answer != 'N'));
    return (answer == 'Y');
}

void eat_line( )
{
    char next;
    do
       cin.get(next);
    while (next != '\n');
}