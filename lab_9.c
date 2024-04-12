//HASH TABLE

#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;

    // create a next pointer (for linkedlist structure)
    struct RecordType *next;
};

// Fill out this structure
struct HashType
{
    // create a pointer to a RecordType
	struct RecordType *pointer;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    // hash function is x % tableSize
	return x % tableSize;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    // call the hash function to get the index
	int index = hash(record -> id, tableSize);
    // if the RecordType at that index is NULL
	if(hashTable[index].pointer == NULL){
		// set 'record' equal to the HashType pointer in the table at index
		hashTable[index].pointer = record;
	}
    // else
	else{
		// traverse to the end of the linkedlist and add 'record' to the end of it
		struct RecordType *current = hashTable[index].pointer;
		while(current->next != NULL){
			current = current -> next;
		}
		current -> next = record;
	}
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    for(int i = 0; i < tableSize; i++)
    {
        // Assigning a pointer to the linked list on the hashTable
        struct RecordType *current = hashTable[i].pointer;

        // Check if index is occupied
        if (current != NULL)
        {
            // Print only if it is occupied
            printf("Index %d ->", i);

            // Loop through the linked list and print all records
            while(current != NULL)
            {
                printf(" %d, %c, %d", current->id, current->name, current->order);
                current = current->next;

                // Add "->" if there is another record in the list
                if (current != NULL)
                {
                    printf(" ->");
                }
            }

            // Move to the next line after finishing this index
            printf("\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);


    // Initialize the hash table
    struct HashType *hashTable = NULL;

    // create a variable hashTableSize and assign it a value
    int hashtableSize = 23;

    // initialize a hashTable and alloc mem.
    hashTable = (struct HashType*)calloc(sizeof(struct HashType), hashtableSize);

    // insert function
    int n = recordSz;
    for (int i = 0; i<n; i++)
    {
        insertRecord(hashTable, &pRecords[i], hashtableSize);

    }

    // call the display records function
    displayRecordsInHash(hashTable, hashtableSize);
    
    // free all the allocated memory
    free(pRecords);
    free(hashTable);

    return 0;
}
