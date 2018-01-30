// Set class implemented as B-tree.  Written by Cate Sheller using algorithms
// described in Main & Savitch, "Data Structures and Other Objects Using C++"
// Modified/debugged/improved by Chad Kunde, April 2004

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

ofstream out("out.txt");

template <class item>
class Set
{
	public:
		Set( );
 //		Set(const Set& source);
 //		~Set( );
 //		void operator = (const Set& source);
 //		void clear( );
		bool insert (item entry);
		void remove (item target);
		int contains (item target) const;
		int is_empty ( ) const {return count == 0;}
		void print(int indent)const;
      private:
	// constants needed for B-tree implementation
		enum {MINIMUM = 1};
		enum {MAXIMUM = 2};

   // all member variables describe root node
		int count;					// # of data items stored
		int data[MAXIMUM+1];	// stores rootâ€™s data entries
		int children;				// # of children root has
		Set* subset[MAXIMUM+2];
		// array of pointers to rootâ€™s children
		// each subset is itself a Set object;
		// each one is the root node of a smaller Set

   // private section continued -- helper functions

		int is_leaf( ) const {return children == 0;}
		int loose_insert (item entry);
		// adds entry to set; may result in one
		// extra entry in root node of the subset
		void loose_remove (item target);
		// removes entry from set; may result in
		// subsetâ€™s root node being short one data entry
		void remove_largest(item& removed);
		void remove_smallest(item& removed);
		void fix_excess (int x);  // restores B-tree after loose_insert
		void fix_shortage (int x); // restores B-tree after loose_remove

};

template <class item>
Set<item>::Set()
//Set::Set()
{
	count = 0;
	children = 0;
	for (int x=0; x<MAXIMUM+2; x++)
		subset[x]=NULL;
}

template <class item>
int Set<item>::contains (item target) const
//int Set::contains (const int& target) const
{
	int t;
	for (t=0; (t<count) && (data[t]<target); t++);
	if ((t < count) && data[t] == target)
		return true;
	if (is_leaf())
		return false;
	return subset[t]->contains(target);
}

template <class item>
void Set<item>::print (int indent) const
//void Set::print (int indent) const
{	    
    if(is_leaf())
    {
        cout<<setw(3*indent)<<"";
        for(int i=0;i<count;i++)
            cout<<data[i]<<" ";
    }
    else
    {
        for(int i=0;i<children;i++)
        {
            subset[i]->print(indent+1);
            cout<<setw(3*indent)<<"";
            if(i!=children-1)
                cout<<data[i]<<endl;
        }
    }
    cout<<endl;
}

template <class item>
void Set<item>::fix_excess (int x)
//void Set::fix_excess (int x)
{
	int ct;
	//copy middle entry of child to root:
	for (ct=count; ct>x; ct--)
		data[ct]=data[ct-1];

	data[x]=subset[x]->data[MINIMUM];
	count++;
	//split node in 2:
	Set *left, *right; // will hold child's old entries
	left=new Set;
	right=new Set;
	left->count=MINIMUM;
	right->count=MINIMUM;

	for(ct=0; ct<MINIMUM; ct++) // copy data
	{
		left->data[ct]=subset[x]->data[ct];
		right->data[ct]=subset[x]->data[ct+MINIMUM+1];
	}
	if(!(subset[x]->is_leaf()))	// copy subsets if any exist
	{
		int chct=(subset[x]->children)/2;
		for(ct=0; ct<chct; ct++)
		{
			left->subset[ct]=subset[x]->subset[ct];
			right->subset[ct]=subset[x]->subset[ct+chct];
		}
		left->children=MINIMUM+1;
		right->children=MINIMUM+1;
	}

	subset[children]=new Set;
	for(ct=children; ct>x; ct--)
		subset[ct]=subset[ct-1];
	children++;

	subset[x]=left;
	subset[x+1]=right;
}


template <class item>
int Set<item>::loose_insert (item entry)
//int Set::loose_insert (const int& entry)
{
	int t;
	for (t=0; (t<count && data[t]<entry); t++);

	if (t < count && data[t]==entry)
	{
		cout << data[t] << " already in set" << endl;
		return false;	// entry already in set -- not inserted
	}
	if (is_leaf())
	{
		// add new entry at root -- shift data right to make room for new entry
		for(int x=count; x>t; x--)
			data[x] = data[x-1];
		count++;
		data[t] = entry;
	  return true;	// entry was inserted
	}
	else	// entry wasn't found and node has children
	{
		int added = subset[t]->loose_insert(entry);
		if (subset[t]->count > MAXIMUM)
			fix_excess(t);

		return added;
	}
}

template <class item>
bool Set<item>::insert (item entry)
//int Set::insert (const int& entry)
{
	if(loose_insert(entry))  // do loose_insert; if entry added, check for excess
	{
		if (count > MAXIMUM)
		{
			Set *child = new Set;
			for(int x=0; x<count; x++)
				child->data[x]=data[x];
			for(int y=0; y<children; y++)
				child->subset[y]=subset[y];
			child->children=children;
			child->count=count;
			count=0;
			children=1;
			subset[0]=child;
			fix_excess(0);
		} // ends inner if
	return true;
	} // ends outer if
	return false; // if loose_insert failed, so did insert
}

template <class item>
void Set<item>::remove (item target)
{	if(this == NULL)
		return;
	loose_remove(target);
	if (count==0 && children==1) // root has 0 entries -- must be fixed
	{
		int x;
		Set* root=subset[0];
		for(x=0; x<root->count; x++)
			data[x]=root->data[x];
		children=root->children;
		count=root->count;
		for(x=0; x<children; x++)
			subset[x]=root->subset[x];
		delete root;
		root = NULL;
   }
}

template <class item>
void Set<item>::loose_remove(item target)
{	
    if(this == NULL)
		return;

	int r;
	for(r = 0; r < count && data[r] < target; r++);
	// find first entry >= target; if not found, r==count

	if(r == count && is_leaf())
		return;	// target wasn't found & no subtrees to search
	if(r < count && data[r] == target && is_leaf()) // target found, node has no subtrees
	{	count--;
		for(int c = r; c<count; c++)
			data[c]=data[c + 1];	//reduce count & copy over target value
		return;
	}
	if(r == count || (r < count && data[r] != target))
	{	if(is_leaf())
			return;
		// this node doesn't have target -- search subtrees
		subset[r]->loose_remove(target);
		if(subset[r] != NULL && subset[r]->count < MINIMUM)
			fix_shortage(r);
		return;
	}
   // last possibility -- root has value, but also subtrees -- must maintain
   // shape of B-tree
   // cout << "option 4" << endl;
	if(subset[r + 1]->count > MINIMUM && is_leaf())
	{	subset[r + 1]->remove_smallest(data[r]);	}
	else
	{	subset[r]->remove_largest(data[r]);
		if(subset[r]->count < MINIMUM)
			fix_shortage(r);
	}
	return;
}

template <class item>
void Set<item>::remove_largest(item& removed)
{
	if (is_leaf())
	{
		count--;
		removed = data[count];
	}
	else
	{
		subset[children - 1]->remove_largest(removed);
		if(subset[children - 1]->count < MINIMUM)
			fix_shortage(children - 1);
	}
}

template <class item>
void Set<item>::remove_smallest(item& removed)
{	removed = data[0];

		for(int i = 0; i < count; ++i)
			data[i] = data[i + 1];
      --count;
}

// x: subset that is short
// Most of this code was written by Chad
template <class item>
void Set<item>::fix_shortage (int x)
{
     int i;
	//x isn't left child, and left sibling has a spare
	if(x && subset[x-1]->count > MINIMUM)
	{	cout<<"Borrow Left"<<endl;
		out<<"Borrow Left"<<endl;

		if(subset[x]->is_leaf())
		{	for(i = subset[x]->count; i > 0; --i)
			{	subset[x]->data[i] = subset[x]->data[i - 1];}
			subset[x]->data[0] = data[x - 1];
			subset[x]->count++;

			data[x - 1] = subset[x - 1]->data[subset[x - 1]->count - 1];
			subset[x - 1]->count--;
		}
		else
		{
            out << "else of borrow left" << endl;
            for(i = subset[x]->count; i > 0; --i)
			{	subset[x]->data[i] = subset[x]->data[i - 1];
				subset[x]->subset[i + 1] = subset[x]->subset[i];
			}
			subset[x]->subset[1] = subset[x]->subset[0];
			subset[x]->data[0] = data[x - 1];
			subset[x]->count++;

			subset[x]->subset[0]
				= subset[x - 1]->subset[subset[x - 1]->count];
			subset[x]->children++;
			subset[x - 1]->children--;

			data[x - 1] = subset[x - 1]->data[subset[x - 1]->count - 1];
			subset[x - 1]->count--;
		}
	}

	//x isn't right child, and right sibling has a spare
	else if(x < count && subset[x + 1]->count > MINIMUM)
	{	cout<<"Borrow Right"<<endl;
		if(subset[x]->is_leaf())
		{	subset[x]->data[subset[x]->count] = data[x];
			subset[x]->count++;
			data[x] = subset[x + 1]->data[0];
			subset[x + 1]->count--;
			for(i = 0; i < subset[x + 1]->count; ++i)
				subset[x + 1]->data[i] = subset[x + 1]->data[i + 1];
		}
		else
		{	out<<"Borrow Right"<<endl;
			subset[x]->data[subset[x]->count] = data[x];
			subset[x]->count++;
			subset[x]->subset[subset[x]->count] = subset[x + 1]->subset[0];
			data[x] = subset[x + 1]->data[0];
			subset[x + 1]->count--;
            for(i = 0; i < subset[x + 1]->count; ++i)
			{	subset[x + 1]->data[i] = subset[x + 1]->data[i + 1];
				subset[x + 1]->subset[i] = subset[x + 1]->subset[i + 1];
			}
			subset[x + 1]->subset[i] = subset[x + 1]->subset[i + 1];
 			subset[x + 1]->children--;
 			subset[x]->children++;
		}
	}

	//MUST COMBINE WITH A SIBLING

	//combine with left sibling
	else if(x > 0)
	{	cout<<"Combine Left"<<endl;
		out<<"Combine Left"<<endl;
		if(subset[x]->is_leaf())
		{	subset[x - 1]->data[subset[x - 1]->count] = data[x - 1];
			subset[x - 1]->count++;
			for(i = 0; i < subset[x]->count; ++i)
			{	subset[x - 1]->data[subset[x - 1]->count]
						= subset[x]->data[i];
				subset[x - 1]->count++;
			}
			delete subset[x];
			subset[x] = NULL;
			--children;

			for(i = x; i < count; ++i)
			{	data[i - 1] = data[i];
				subset[i] = subset[i + 1];
			}
			--count;
		}
		else
		{	subset[x - 1]->data[subset[x - 1]->count] = data[x - 1];
			subset[x - 1]->count++;
			for(i = 0; i < subset[x]->count; ++i)
			{	subset[x - 1]->data[subset[x - 1]->count]
					= subset[x]->data[i];
				subset[x - 1]->subset[subset[x - 1]->count]
					= subset[x]->subset[i];
				subset[x - 1]->count++;
				subset[x - 1]->children++;
			}
			subset[x - 1]->subset[subset[x - 1]->count]
				= subset[x]->subset[subset[x]->count];
			subset[x - 1]->children++;

			delete subset[x];
			subset[x] = NULL;
			--children;

			for(i = x; i < count; ++i)
			{	data[i - 1] = data[i];
				subset[i] = subset[i + 1];
			}
        			--count;
		}
	}

	//combine with right sibling(x is left child)
	else
	{	cout<<"Combine Right"<<endl;
		out<<"Combine Right"<<endl;
		if(subset[x]->is_leaf())
		{	
            subset[x]->data[subset[x]->count] = data[x];
			subset[x]->count++;
			for(i = 0; i < subset[x + 1]->count; ++i)
			{	subset[x]->data[subset[x]->count]
					= subset[x + 1]->data[i];
				subset[x]->count++;
			}
			delete subset[x + 1];
			subset[x + 1] = NULL;
			--children;
            
			for( i = x; i < count - 1; ++i)
			{	
                data[i] = data[i + 1];
				subset[i + 1] = subset[i + 2];
			}
			--count;
		}
		else
		{	subset[x]->data[subset[x]->count] = data[x];
			subset[x]->count++;
			for(i = 0; i < subset[x + 1]->count; ++i)
			{	subset[x]->data[subset[x]->count]
					= subset[x + 1]->data[i];
				subset[x]->subset[subset[x]->count]
					= subset[x + 1]->subset[i];
				subset[x]->count++;
				subset[x]->children++;
			}
			subset[x]->subset[subset[x]->count]
				= subset[x + 1]->subset[subset[x + 1]->count];
			subset[x]->children++;

			delete subset[x + 1];
			subset[x + 1] = NULL;
			--children;

			for(i = x; i < count; ++i)
			{	data[i] = data[i + 1];
				subset[i + 1] = subset[i + 2];
			}
			--count;
		}
	}
}

int main()
{
	Set<int> si;
    for(int i=5;i<12;i++)
    {
        si.insert(i);
    }
    si.remove(5);
	return 0;
}