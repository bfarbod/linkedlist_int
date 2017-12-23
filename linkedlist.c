#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool global_deleted = false;


typedef struct _entry
{
  int data;
  struct _entry *next;
}entry;

int main ()
{
  // ----------------------------------------------------
  // prototypes
  entry * insert (entry *list_pointer, int value);
  entry * delete (entry *list_pointer, int value);
  void deleteAll (entry *list_pointer);
  bool isEmpty (entry *list_pointer);
  void printList (entry *list_pointer);
  void instructions (void);
  // ----------------------------------------------------
  // Initial variables
  entry *startPtr = NULL;         // Initially there are no nodes
  unsigned int choice;        // user's choice
  int value;         // integer entered by user


  // ----------------------------------------------------
  // Loop while user does not choose 3
  do
    {

      instructions ();
      scanf ("%u", &choice);

      switch ( choice )
        {

          // ----------------------------------------------------
          // Insert a value

        case 1:
          printf ("\nEnter a number: ");
          scanf ("%i", &value);
          startPtr = insert (startPtr, value);
          printList (startPtr);
          break;

          // ----------------------------------------------------
          // Delete a vlue

        case 2:

          if ( isEmpty (startPtr) )
              printf ("List is empty.\n");

          else
            {
              printf ("\nEnter a value to be deleted: ");
              scanf ("%i", &value);
              startPtr = delete (startPtr, value);
              if ( global_deleted )
                {
                  printf ("\n\"%i\" was deleted\n", value);
                  printList (startPtr);
                }

              else
                {
                  printf ("\n\"%i\" was not found\n\n", value);
                }
            }
          break;

          // ----------------------------------------------------
          // Exit

        case 3:
          break;

          // ----------------------------------------------------
        default:
          printf ("\nINVALID CHOICE.\n\n");
          instructions ();
          scanf ("%u", &choice);
          break;

        }

    }
  while ( choice != 3);


  // In order to prevent memory leak, we're going to delete every node
  if ( !isEmpty (startPtr) )
    deleteAll (startPtr);

  return 0;
}

// ------------------------------------------------------------------------------------
// instructions
// ------------------------------------------------------------------------------------

void instructions ( void )
{
  printf ("1 to insert an element.\n"
            "2 to delete an element.\n"
            "3 to quit.\n"
          "Enter your choice: ");
}

// ------------------------------------------------------------------------------------
// printList
// ------------------------------------------------------------------------------------

void printList ( entry *list_pointer)
{
  /*
  Because we're going to use isEmpty in printList
  then we need to declare it before using it just
  like in main function
  */
  // prototypes
  bool isEmpty (entry *list_pointer);

  // head of linked list should not be changed at all because we're going to lose it
  entry *tempPtr = list_pointer;

  if ( isEmpty (tempPtr) )
    printf ("\nList is empty.\n");

  else
    {
      printf ("\nLinked list: ");

      while ( tempPtr ) // OR ( tempPtr != NULL ) OR ( tempPtr != ( entry *) 0)
        {
          printf ("%i --> ", tempPtr -> data);
          tempPtr = tempPtr -> next;
        }

      printf ("NULL \n\n");
    }
}

// ------------------------------------------------------------------------------------
// isEmpty
// ------------------------------------------------------------------------------------


bool isEmpty (entry *list_pointer)
{
  return list_pointer == NULL;

  // I prefer the above because it's much cleaner and it's just one line of code
  // Who do you want to be?
  // The above or below?
  /*
    if ( list_pointer == NULL) // OR ( list_pointer == (entry *) 0)
      return true;
    else
      return false;
  */
}


// ------------------------------------------------------------------------------------
// insert
// ------------------------------------------------------------------------------------
// Insert the node at it's rightful position

entry * insert (entry *list_pointer, int value)
{
  /*
  Here there's no need to create a tempPtr
  because the head of linked list (list_pointer)
  will be the head even after putting the node
  at the begining
  */
  entry *newPtr, *previousPtr, *currrentPtr;
  newPtr = (entry *) malloc ( sizeof (entry) );

  if ( newPtr == NULL)
    printf ("%i cannot be inserted, No memory available.\n", value);

  else
    {
      newPtr -> data = value; // place value in the node
      newPtr -> next = NULL; // node does not link to another node

      previousPtr = NULL;
      currrentPtr = list_pointer;

      // loop to find the current location in the list
      while ( currrentPtr != NULL && value > currrentPtr -> data)
        {
          previousPtr = currrentPtr;
          currrentPtr = currrentPtr -> next;
        }

      if ( previousPtr == NULL) // insert node at begining
        {
          newPtr -> next = list_pointer;
          list_pointer = newPtr;
        }

      else
        {
          previousPtr -> next = newPtr;
          newPtr -> next = currrentPtr;
        }

    }

  return list_pointer;
}

// ------------------------------------------------------------------------------------
// delete
// ------------------------------------------------------------------------------------


entry * delete (entry *list_pointer, int value)
{
  entry *previousPtr, *currentPtr, *tempPtr, *head;

  head = list_pointer;

  // if the node that you're looking for is at the begining of linkedlist
  // then don't bother looping the linkedlist
  if ( value == list_pointer -> data)
    {
      tempPtr = list_pointer;
      list_pointer = list_pointer -> next;
      free (tempPtr);
      global_deleted = true;
      return list_pointer;
    }

  else
    {
      previousPtr = list_pointer;
      currentPtr = list_pointer -> next;

      while ( currentPtr != NULL && currentPtr -> data != value)
        {
          previousPtr = currentPtr;
          currentPtr = currentPtr -> next;
        }

      // delete node at currentPtr
      if ( currentPtr != NULL)
        {
          tempPtr = currentPtr;
          previousPtr -> next = currentPtr -> next;
          free (tempPtr);
          global_deleted = true;
          return head;
        }
    }

  // if node couldn't be found then return the head of linked list
  global_deleted = false;
  return head;
}


// ------------------------------------------------------------------------------------
// deleteAll
// ------------------------------------------------------------------------------------
// Delete all the nodes recursively
/*
  we're going to the end of the linked list until we reached NULL then
  we're going to delete each node from last to first

  for more information see singly linked list CS50: https://www.youtube.com/watch?v=zQI3FyWm144
*/
void deleteAll (entry *list_pointer)
{
  if ( !list_pointer ) // OR ( list_pointer == NULL ) OR ( list_pointer == (entry *) 0)
    return;

  else
    {
      deleteAll (list_pointer -> next);
      free (list_pointer);
    }
}
