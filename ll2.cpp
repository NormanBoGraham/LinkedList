// Norman Graham
// 607-201-5322
//
// construct a double linked list, 
// and add, and delete, and show test results.
//

#include <iostream>   
#include <cstring> 

// DataPart, to re "referenced"
// for now, give it an id. 
class DataPart { 
	// 
	static long Sequence ;  // some key generator for testing.
	long id; 
	public: 
	DataPart():id(Sequence++) { }; 
	void test_print() { 
             std::cout << "Item: " << id << "\n"; 
	}; 
	bool operator == ( const DataPart &di2) { 
		return this->id == di2.id ? true : false; 
	}; 
}; 

long DataPart::Sequence = 0; 

// These are the references for the linked list, to test.
#define MaxTest 5
static DataPart diArray[MaxTest];  // just have an array of data items for testing.

// Node contains pointers, and DataPart.
class NodeItem { 
	public: 
	DataPart &di; 
	NodeItem *next; 
	NodeItem *prev; 
	public: 
        NodeItem(DataPart &di_): di(di_), next(nullptr), prev(nullptr) {}; 

	//  operator ==, returns true false.
	bool IsIt( const DataPart &di_)const { return di == di_; }; 
}; 

// Linked List container.
class LL { 
	NodeItem *head; 
	public: 
	LL(): head(nullptr) {}; 
	~LL() {
          while (head) { 
		  NodeItem *prev = head; 
		  head = head->next; 
		  delete prev; 
	  }
	}; 

	// for testing, I want to clear the list.
	void clearList() { 
          while (head) { 
		  NodeItem *prev = head; 
		  head = head->next; 
		  delete prev; 
	  }
	}; 

	// find the Data reference in the list.
	NodeItem *findItem( const DataPart &di_) { 
		NodeItem *p = head; 
		NodeItem *L = nullptr; 
		for (; p ; p=p->next) { 
			if ( p->di == di_ ) { // found.
				return p; 
			}
			L = p; 
		} 
		return nullptr; 
	}; 

	// remove item from list.
        bool removeItem( DataPart &di_ ) { 

	    // find in list.
            NodeItem *found = findItem( di_ ) ; 
	    if ( !found ) 
	        return false; // cannot remove, it's not here. 
	    else { 
		// if we remove the head item, we have to set head ptr.
		if ( !found->prev ) { 
                      head = found->next; 
		      found->next = nullptr; // decouple from rest of list, we are about to delete.
		      delete found; 
		      if ( head) 
			      head->prev = nullptr; 
		      return true; 
		} 
		else {  // not first node, so, there is a prev node. 
			if ( found->prev) 
				found->prev->next = found->next; 
			if ( found->next ) 
				found->next->prev = found->prev; 
                        delete found; 
			return true; 
		} 
	    }
	} ; 

	bool addItem( DataPart &di_) 
	{ 
            NodeItem *found = findItem( di_) ; 
            if ( found ) 
		    return false; // do not add twice. 
	    else { 
		    NodeItem *z = new NodeItem( di_ ) ; 
		    if ( head ) 
			 head->prev = z; // set head's prev to new.
		    z->next  = head;  // next new item, next to head.

		    head = z; 
		    return true; 
	    }
	}; 

	void dump() { 
           NodeItem *p = head; 
	   for (;  p ; p=p->next) { 
		   p->di.test_print(); 
	   }; 
	}; 
	void dump2() { // dump, and show, what pointers point at. 
           NodeItem *p = head; 
	   for (;  p ; p=p->next) { 
		   p->di.test_print(); 
		   if ( p->prev ) { 
			   std::cout << "   prev : " ; 
			   p->prev->di.test_print(); 
		   } 
		   else { 
			   std::cout << "   no prev\n"; 
		   }
		   if ( p->next ) { 
			   std::cout << "   next : " ; 
			   p->next->di.test_print(); 
		   }
		   else { 
			   std::cout << "  no next\n" ; 
		   }
	   }; 
	}; 
}; 



static bool UnitTest() 
{ 
        LL ll; 

        
	ll.addItem( diArray[4] ); 
	ll.addItem( diArray[3] ); 
	ll.addItem( diArray[2] ); 
	ll.addItem( diArray[1] ); 
	ll.addItem( diArray[0] ); 

        std::cout << "Print linked list" 
	          << "-----------------\n"; 

	ll.dump( );

	std::cout << "\n"; 
	std::cout << "Remove head element" 
		     "-------------------\n";
        ll.removeItem(diArray[0]); 
	ll.dump(); 

	std::cout << "\n"; 
	std::cout << "Remove internal element" ; 
	std::cout << "-----------------------\n" ; 
        ll.removeItem(diArray[2]); 
	ll.dump(); 

        std::cout << "\n"; 
        std::cout << "dump and show pointers\n"; 
        std::cout << "----------------------\n"; 
	ll.dump2(); 
        	
        ll.clearList(); 	
	std::cout << "\n"; 
	std::cout << "empty list print\n"; 
	std::cout << "----------------\n"; 
	ll.dump(); 
 
	return true; 
} 


int main() 
{ 
   UnitTest(); 
   return 0; 
} 
