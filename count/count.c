#include <stdio.h>
#include <stdlib.h>

#define BUZZ_SIZE 64

struct node
{
    unsigned long data;
    struct node *next;
};

int main(int argc, char* argv[]){
	//test case 1: make sure that if file 1 is empty it prints out 0
	if(argc!=2){
    	printf("error\n");
    	return 1;
    }

	char* name = argv[1]; 
    FILE* file;
	file = fopen(name, "r");
	//if file does not exist 
	if(!file){
		printf("error\n");
		return 1;
	}

	int elements = 1000;
	char buff[BUZZ_SIZE];
	//struct node* array[1000]={NULL};
	//you can change what the node points to
	struct node** array = (struct node**)malloc(sizeof(struct node*)*elements);

	int initialsize = 0;
	int counter = 0;

	//scans the lines line by line 
	  while(1){

		fgets(buff, BUZZ_SIZE, file); //buff 

		if(feof(file)){
			printf("%d\n", counter);
	  		break;
	  	}
	  	//printf("String read: %s\n", buff);

	  	unsigned long n = strtoul(buff, NULL, 16); 

	  	//printf("The value of the decimal is %lu\n", n);

	  	int pos = n%elements;

		struct node* temp; //Node we need to add in to linked list

		//case 1: there is no node in the linked list
		if(array[pos]==NULL){

			temp=(struct node*)malloc(sizeof(struct node)*1);
			temp->data=n;
			temp->next=NULL;

			array[pos]=temp;
			counter++;
			
			if((0.75*elements) <= counter){
				//rehash
				initialsize = elements*2;
				struct node** array2 =  {(struct node**)malloc(sizeof(struct node*)*initialsize)};
					int pos1;
					//insert elements from array1 into array2
					//for loop goes through each linked list (1000 linked lists)
					for(int i =0; i < elements; i++){
						//pointing to the first element of the linked list 
						struct node* ptr = array[i];
						while(1){
							//going to keep going until ptr->next is null
							if(ptr == NULL){
								break;
							}
							pos1 = (ptr->data) % (elements*2);

							if(array2[pos1]==NULL){
								//add temp to the front
								temp=(struct node*)malloc(sizeof(struct node)*1);
								temp->data=ptr->data;
								temp->next=NULL;
								array2[pos1]=temp;
							} else {
								struct node* ptr1; //pointer that initially points to beginning of the linked list in that position of array
								ptr1 = array2[pos1];
								while(ptr1->next!=NULL){
									if(ptr1==NULL){
										break;
									}
									ptr1 = ptr1->next;
								}
								//add temp
								temp=(struct node*)malloc(sizeof(struct node)*1);
								temp->data=ptr->data;
								ptr1->next=temp;
								temp->next = NULL;
							}
							ptr = ptr->next;
						}

					}
					//frees every element in old array
					for(int i = 0; i< elements; i ++){
						//have to free every node 
						//then set pointer that points to array to array2
						if(array[i]==NULL){
							continue;
						}
						struct node* temp2 = array[i];
						struct node* next2 = NULL;
						while(temp2!=NULL){
							next2 = temp2->next;
							free(temp2);
							temp2 = next2;
					}
				}
				free(array);
				array = array2;
				elements = elements*2;
			}
	
		} else {
			//case 2: there is more than one element in the linked list 
			struct node* ptr; //pointer that initially points to beginning of the linked list in that position of array
			ptr = array[pos];

			while(ptr->data!=n){ 
				if(ptr->next==NULL){
					break; 
				} else {
					ptr=ptr->next;
				}
			}

			if(ptr->data == n){

			} else {
				//add temp
				temp=(struct node*)malloc(sizeof(struct node)*1);
				temp->data=n;
				//printf("The value of temp->data is %lu\n", ptr->data);

				ptr->next=temp;
				temp->next = NULL;

				counter++;

				if((0.75*elements) <= counter){
					//rehash
					
					initialsize = elements*2;
					struct node** array2 = (struct node**)malloc(sizeof(struct node*)*initialsize);
					int pos1;
					//insert elements from array1 into array2
					//for loop goes through each linked list (1000 linked lists)
					for(int i =0; i < elements; i++){
						struct node* ptr = array[i];
						while(1){
							//printf("transfering addresses");
							//printf("%d", i);
							//pointing to the first element of the linked list 
							//going to keep going until ptr->next is null
							if(ptr == NULL){
								break;
							}
							pos1 = (ptr->data) % (elements*2);

							if(array2[pos1]==NULL){
								//add temp to the front
								temp=(struct node*)malloc(sizeof(struct node)*1);
								temp->data=ptr->data;
								temp->next=NULL;
								array2[pos1]=temp;
							} else {
								struct node* ptr1; //pointer that initially points to beginning of the linked list in that position of array
								ptr1 = array2[pos1];
								while(ptr1->next!=NULL){
									if(ptr1==NULL){
										break;
									}
									ptr1 = ptr1->next;
								}
								//add temp
								temp=(struct node*)malloc(sizeof(struct node)*1);
								temp->data=ptr->data;
								ptr1->next=temp;
								temp->next = NULL;
							}
							ptr = ptr->next;
						}
					}
					//frees every element in old array
					for(int i = 0; i< elements; i ++){
						//have to free every node 
						//then set pointer that points to array to array2
						if(array[i]==NULL){
							continue;
						}
						struct node* temp2 = array[i];
						struct node* next2 = NULL;
						while(temp2!=NULL){
							next2 = temp2->next;
							free(temp2);
							temp2 = next2;
						}
					}
				free(array);
				array = array2;
				elements = elements*2;
				}
			}
		}
	}
	
	fclose(file);
}
