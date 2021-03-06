// 2.5 You have two numbers represented by a linked list, where each node
// contains a single digit. The digits are stored in reverse order, such 
// that the 1's digits at the head of the list. Write a function that adds
// the two numbers and returns the sum as a linked list.
// EXAMPLE:
// Input: (7 -> 1 -> 6) + (5 -> 9 -> 2) that is: 617 + 295
// Output: 2 -> 1 -> 9. That is 912
// FOLLOW UP:
// Suppose the digits are stored in forward order. Repeat the above problem.
// EXAMPLE:
// Input: (6 -> 1 -> 7) + (2 -> 9 -> 5) that is: 617 + 295
// Output: 9 -> 1 -> 2. That is 912

// 
// Section 2, test case: 9653 + 653
// Section 2, test case 2: 9912 + 88
// Section 2, test case 3: 8912 + 88

#include "..\inc\utils.h"

int addTwoLinkedListDesOrder(Node<int>* la, Node<int>* lb)
{
    if(nullptr == la && nullptr == lb) {
        return -1;        
    } else if (nullptr == la) {
        return linkedListToNumDesOrder<int>(lb);
    } else if (nullptr == lb) {
        return linkedListToNumDesOrder<int> (la);
    } else {
        size_t sa = la->size();
        size_t sb = lb->size();
        Node<int> *curP1 = nullptr;
        Node<int> *curP2 = nullptr;
        size_t s1 = 0, s2 = 0, s1anchor = 0;
        if (sa >= sb) {
            curP1 = la; s1 = sa; s1anchor = sa;
            curP2 = lb; s2 = sb;
        } else {
            curP1 = lb; s1 = sb; s1anchor = sb;
            curP2 = la; s2 = sa;
        }        
        Node<int>* head = nullptr;

        while (s1 > s2) {
            if (head) {
                head->appendToTail(curP1->data);                
            } else {
                head = new Node<int>(curP1->data);                
            }
            curP1 = curP1->next;
            s1--;
        }

        while (s1) {            
            int temp = curP1->data + curP2->data;
            int additional = temp > 9 ? 1 : 0;
            temp = additional ? temp - 10 : temp;

            if (additional) {
                int updatePos = head->size() - 1;
                head->appendToTail(temp);
                while (additional && updatePos >= 0) {
                    temp = (*head)[updatePos] + additional;
                    additional = temp > 9 ? 1 : 0;
                    (*head)[updatePos] = additional ? temp - 10 : temp;
                    updatePos--;
                }
                // The first element still have additional, then we need to extend the existing link into another one.
                if (additional) {
                    Node<int>* newHead = new Node<int>(1);
                    size_t oldListSize = head->size();
                    for (size_t i = 0; i < oldListSize; i++) {
                        newHead->appendToTail((*head)[i]);
                    }                    
                    head->deallocateWholeLinkedList();
                    head = newHead;
                }
            } else {
                head->appendToTail(temp);
            }
            curP1 = curP1->next;
            curP2 = curP2->next;
            s1--;
        }
        return linkedListToNumDesOrder(head);

    }
}

int C2Q5_part2()
{
    bool debug = false;
    
    // Test case 1: 9643 + 653 = 
    int arr1_1[4] = {9, 6, 5, 3};
    int arr1_2[3] = {6, 5, 3};
    Node<int> *l1 = new Node<int>(arr1_1, 4);
    Node<int> *l2 = new Node<int>(arr1_2, 3);
    
    if (debug) {
        std::cout << "print list l1 is: "; l1->printList();
        std::cout << "print list l2 is: "; l2->printList();
        std::cout << "L1 size is: " << l1->size() << std::endl;
        std::cout << "L2 size is: " << l2->size() << std::endl;
    
        std::cout << "l1Num in Descend order is: " << linkedListToNumDesOrder<int>(l1) << std::endl;
        std::cout << "l2Num in Descend order is: " << linkedListToNumDesOrder<int>(l2) << std::endl;
    }
    
    std::cout << "Test case 1: " << linkedListToNumDesOrder<int>(l1) << " + " << linkedListToNumDesOrder(l2) << " = " << addTwoLinkedListDesOrder(l1, l2) << std::endl;
    
    l1->deallocateWholeLinkedList();    l1 = nullptr;
    l2->deallocateWholeLinkedList();    l2 = nullptr;

    // Section 2, test case 2: 9912 + 88
    int arr2_1[4] = {9, 9, 1, 2};
    int arr2_2[2] = {8, 8};
    l1 = new Node<int>(arr2_1, 4);
    l2 = new Node<int>(arr2_2, 2);

    std::cout << "Test case 2: " << linkedListToNumDesOrder<int>(l1) << " + " << linkedListToNumDesOrder(l2) << " = " << addTwoLinkedListDesOrder(l1, l2) << std::endl;
    
    // Section 2, test case 3: 8912 + 88
    int arr3_1[4] = {8, 9, 1, 2};
    int arr3_2[2] = {8, 8};
    l1 = new Node<int>(arr3_1, 4);
    l2 = new Node<int>(arr3_2, 2);

    std::cout << "Test case 3: " << linkedListToNumDesOrder<int>(l1) << " + " << linkedListToNumDesOrder(l2) << " = " << addTwoLinkedListDesOrder(l1, l2) << std::endl;
    return 0;
}