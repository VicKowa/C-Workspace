#include <stdio.h>
#include <stdlib.h>
#define RAMSize 1024   // max. Hauptspeichergröße in kByte
#define SegmentSize 16 // min. Segmentgröße in kB

typedef struct node
{
    unsigned int segNum;  // segement number
    unsigned int segSize; // size of segment
    char segStatus;       // status if a segment: free, splitted, used
    struct node *parent;  // pointer to parent
    struct node *lsSucc;
    struct node *rsSucc;

} node;

node *root;
void buddy_fuse_segments(node * temp);
// funktionsprototypen
unsigned int buddy_alloc(unsigned int size);
// gibt eine eindeutige Semgmentnummer zurück
void buddy_free(unsigned int segNum);
// Segment mit der Nummer segNum wird zur De-Allokierung freigegeben
unsigned int buddy_find_segment(unsigned int site, node *temp);
void split_segment(node *root);
node* buddy_search_segment(unsigned int num, node* temp);




unsigned int buddy_alloc(unsigned int size)
{
    
    unsigned int seg = 0;//segment num
    // if input size smaller than min segement size
    if (size < SegmentSize)
    {
        size = SegmentSize;
    }
    // if input size smaller than max segment size round to the next power of 2
    if (size < RAMSize && size > SegmentSize)
    {
        int pow = 16;
        while (size > pow)
        {
            pow *= 2;
        }
        size = pow;
    }
    // if input size greater than max segment size
    if (size > RAMSize)
    {
        return 0;
    }
    //intialize root if not already there
    if(root == NULL)
    {
        root = malloc(sizeof(node));
        root->parent = NULL;
        root->segNum = 1;
        root->segSize = RAMSize;
        root->lsSucc = NULL;
        root->rsSucc = NULL;
        root->segStatus = 'f';
    }
    

    // if(size != RAMSize)
    // {
    //    root->segStatus = 's';
    // }
    // return buddy_alloc_recursive(size, root);

    while(((seg = buddy_find_segment(size, root)) == 0) && size < RAMSize/2) {
        size *= 2;
    }
    return seg;

}
unsigned int buddy_find_segment(unsigned int size, node *temp)
{
    if (temp->segStatus == 'u')
    {
        return 0;
    }
    else
    {
        if (temp->segSize == size && temp->segStatus == 'f' )
        {
            temp->segStatus = 'u';
            return temp->segNum;
        }
        else
        {
            unsigned int res;
            if (temp->segStatus == 'f')
            {
                split_segment(temp);
            }

            
            res = buddy_find_segment(size, temp->lsSucc);
            if(res == 0) {
                res =  buddy_find_segment(size, temp->rsSucc);
                return res;
            } else {
                return res;
            }
            
        }
    }
}

node* buddy_search_segment(unsigned int num, node* temp)
{
    if (temp == NULL) {
        return NULL; // Wenn der Baum leer ist oder das Ziel nicht gefunden wurde
    }

    // Überprüfen, ob die ID des aktuellen Knotens übereinstimmt
    if (temp->segNum == num) {
        return temp;
    }

    // Überprüfen, ob die ID im linken Teilbaum ist
    if (num % 2 == 0) {
        return buddy_search_segment(num, temp->lsSucc);
    }

    // Überprüfen, ob die ID im rechten Teilbaum ist
    if (num % 2 == 1) {
        return buddy_search_segment(num, temp->rsSucc);
    }

    return NULL; // Wenn die ID nicht gefunden wurde

}



void split_segment(node *root)
{
    node *temp;
    root->segStatus = 's';
    root->lsSucc = malloc(sizeof(node));
    root->rsSucc = malloc(sizeof(node));

    temp = root->lsSucc;

    temp->parent = root;
    temp->rsSucc = NULL;
    temp->lsSucc = NULL;
    temp->segNum = 2 * (root->segNum);
    temp->segSize = (root->segSize) / 2;
    temp->segStatus = 'f';

    temp = root->rsSucc;

    temp->parent = root;
    temp->rsSucc = NULL;
    temp->lsSucc = NULL;
    temp->segNum = (2 * (root->segNum)) + 1;
    temp->segSize = (root->segSize) / 2;
    temp->segStatus = 'f';
}

void buddy_free(unsigned int segNum) 
{
    if(root == NULL)
    {
        perror("No data allocated");
    }
    node *todel = buddy_search_segment(segNum, root);
    if(todel == NULL)
    {
        perror("Segment Number not found");
    } 
    
    todel->segStatus = 'f';
    
    buddy_fuse_segments(root);

}

void buddy_fuse_segments(node * temp)
{
    if(temp->lsSucc != NULL)
    {
        buddy_fuse_segments(temp->lsSucc);
    }
    if(temp->rsSucc != NULL)
    {
        buddy_fuse_segments(temp->rsSucc);
    }
    if(temp->lsSucc != NULL 
        && temp->rsSucc != NULL 
        && (temp->lsSucc->segStatus == 'f') 
        && (temp->rsSucc->segStatus == 'f'))
    {
            free(temp->lsSucc);
            free(temp->rsSucc);

            temp->lsSucc = NULL;
            temp->rsSucc = NULL;

            temp->segStatus = 'f';
    }
    
}



int main(int argc, char **argv)
{
    int test = buddy_alloc(128);
    int test2 = buddy_alloc(64);
    int test3 = buddy_alloc(256);
    int test4 = buddy_alloc(256);

    printf("%d\n", test);
    printf("%d\n", test2);
    printf("%d\n", test3);
    printf("%d\n", test4);

    buddy_free(test);
    buddy_free(test3);
    buddy_free(test2);
    buddy_free(test4);

    // printf("%d\n", seg->segNum);
    // printf("%d\n", seg->segSize);
    return 0;
}
