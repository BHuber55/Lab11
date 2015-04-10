#include "BinarySearchTree.h"
#include "BinaryTreeIterator.h"
#include "ListArray.h"
using CSC2110::ListArray;
#include "ListArrayIterator.h"
using CSC2110::ListArrayIterator;
#include "CD.h"
using CSC2110::CD;

#include <iostream>
using namespace std;

void deleteCDs(ListArray<CD>* list)
{
   ListArrayIterator<CD>* iter = list->iterator();

   while(iter->hasNext())
   {
      CD* cd = iter->next();
      delete cd;
   }

   delete iter;
}

int main()
{
   //the unsorted ListArray of cds
   ListArray<CD>* cds = CD::readCDs("cds.txt");
   int num_items = cds->size();
   cout << num_items << endl << endl;

   //test the binary search tree
   //insert all of the cds
   ListArrayIterator<CD>* iter = cds->iterator();
   BinarySearchTree<CD>* bst = new BinarySearchTree<CD>(&CD::compare_items, &CD::compare_keys);
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      bst->insert(cd);
   }
   delete iter;

   
   //DO THIS
   //test your tree sort method


   int num_itemss = cds->size();		//num_itemss again.. gf spelling.

   //CD** unsorted_cds = cds->toArray();
   CD** sorted_cds = BinarySearchTree<CD>::treeSort(cds->toArray(), cds->size(), &CD::compare_items, &CD::compare_keys);
   for (int i = 0; i < num_itemss; i++)
   {
	   CD* cd = sorted_cds[i];
	   String* title = cd->getKey();
	   title->displayString();
	   cout << endl;
   }

   cout << "leggo.. (hit enter)";
   cin.get();
   cout << endl << endl;

   //tests insert
   iter = cds->iterator();
   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   bst->insert(cd);
   }
   delete iter;

   //tests remove
   iter = cds->iterator();
   int count = 1;
   while (iter->hasNext() && count <= num_itemss)	//make sure it doesnt remove more 
   {
	   CD* cd = iter->next();
	   bst->remove(cd->getKey());
	   count++;
   }
   delete iter;

   BinaryTreeIterator<CD>* bst_iter = bst->iterator();
   bst_iter->setInorder();
   while (bst_iter->hasNext())
   {
	   CD* cd = bst_iter->next();
	   cd->displayCD();
   }
   delete bst_iter;

   iter = cds->iterator();
   bst = new BinarySearchTree<CD>(&CD::compare_items, &CD::compare_keys);

   while (iter->hasNext())
   {
	   CD* cd = iter->next();
	   bst->insert(cd);
   }
   delete iter;

   deleteCDs(cds);
   delete cds;
   return 0;
}
