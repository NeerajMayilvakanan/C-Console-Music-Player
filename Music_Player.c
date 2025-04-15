#include<stdio.h>
#include<stdlib.h>
#include<string.h>
short rno=1,pos=0;
struct songs{
	short sno;
	char name[40];
	short min;
	short sec;
	struct songs *pre;
	struct songs *next;
}*head=NULL,*last;
void player();
void add_song();
void allsong();
void success_msg();
void play_song();
short search(short id);
void delete_song();
void space(short i){
	short j=0;
	for(;j<i;j++)
		printf("\n");
}
int main(){
	player();
}
void player(){
	short i;
	system("CLS");
	system("COLOR 4F");
	space(17);
	printf("\t\t\tMusic Player\n\n");
	printf("\t\t\t1.Add Song \n\t\t\t2.Play Song \n\t\t\t3.Delete Song \n\t\t\t4.All_Songs\n\t\t\t5.Exit \n\t\t\tEnter Your Choice :  ");
	scanf("%hd",&i);
	switch(i){
		case 1:
			add_song();
			break;
		case 2:
			play_song();
			break;
		case 3:
			delete_song();
			break;
		case 4:
			allsong();
			break;
		case 5:
			exit(1);
			break;
		default:
			printf("\n\t\t\tWrong Input\a \n\n\t\t\tPress Any Key To Continue...");
			getch();
	}
	player();
}
void success_msg(){
	system("CLS");
	system("COLOR 4F");
	space(17);
	printf("\t\t\"Song Added Successfully\"\n\n\t\tPress Any Key to Continue...");
	getch();
	pos++;
}
void allsong(){
	system("CLS");
	system("COLOR 4F");
	space(10);
	struct songs *temp=head;
	if(temp==NULL){
		printf("\a No Songs Available \nPress any key to continue...");
		getch();
		return ;
	}
	printf("\nSong_Id  Name                  		           Min    Sec\n");
	while(temp!=NULL){
		printf("%-8hd %-40s %3hd    %3hd\n",temp->sno,temp->name,temp->min,temp->sec);
		temp=temp->next;
	}
	printf("\nPress Any Key To Continue...");
	getch();
}
void add_song(){
	short i;
	char name[40];
	system("CLS");
	system("COLOR 4F");
	space(17);
	printf("\t\t\tAdd Song\n\n");
	struct songs *n=(struct songs *) malloc(sizeof(struct songs));
	n->sno=rno++;
	fflush(stdin);
	printf("\n\t\tEnter Song Name : ");
	scanf("%[^\n]",name);
	strcpy(n->name,name);
	printf("\n\t\tEnter Minutes : ");
	scanf("%hd",&n->min);
	printf("\n\t\tEnter Seconds : ");
	scanf("%hd",&n->sec);
	n->pre=NULL;
	n->next=NULL;
	if(pos==0){
		head=n;
		last=n;
		success_msg();
		return ;
	}
	if(pos==1){
		n->pre=head;
		head->next=n;
		success_msg();
		last=n;
		return;
	}
	printf("\t\t\t1.Insert At First \n\t\t\t2.Insert at Middle \n\t\t\t3.Insert at End \n\t\t\t4.Back \n\t\t\t5.Exit \n\t\t\tEnter Your Choice :  ");
	scanf("%hd",&i);
	if(i==1){
		n->next=head;
		head->pre=n;
		head=n;
		success_msg();
	}
	else if(i==2){
		struct songs *temp=head;
		if(n->sno==3){
			n->pre=temp;
			n->next=temp->next;
			temp->next->pre=n;
			temp->next=n;
		}
		else{
			int place,ins_ch=1;
			while(ins_ch){
				printf("\n Position available between 1 and %d \n After which position do you want to add?  ",pos);
				scanf("%d",&place);
				if((place<1) || (place>=pos))
					printf("\a\n\n***Requested Position not available...***\n");
				else
					ins_ch=0;
			}
			for(i=1;i<place;i++){
				temp=temp->next;
			}
			n->pre=temp;
			n->next=temp->next;
			temp->next->pre=n;
			temp->next=n;				
		}
		success_msg();
	}
	else if(i==3){
		last->next=n;
		n->pre=last;
		success_msg();
	}
	else if(i==4){
		free(n);
		return;
	}
	else{
		free(n);
		exit(1);
	}
}
void play_song(){
	short i;
	struct songs *temp=head;
	if(head==NULL){
		system("CLS");
		system("COLOR 4F");
		space(17);
		printf("\n\tNo Songs Available...\n\tPress Any Key To Continue...");
		getch();
		return ;
	}
	short c=0,d=0;
	while(1){
		system("CLS");
		system("COLOR 4F");
		space(17);
		printf("\t\tCurrently Playing\n\n");
		printf("\t\t%s\n\n",temp->name);
		if(temp->pre!=NULL){
			printf("\n\t\t1.Previous");
			c=1;
		}
		if(temp->next!=NULL){
			printf("\n\t\t2.Next");
			d=1;
		}
		printf("\n\t\t3.Stop Playing");
		short ch,l=1;
		do{
			printf("\n\t\tEnter your Choice : ");
			scanf("%hd",&ch);
			if(ch==1){
				if(c==0){
					printf("\a\n\t\tInvalid Input");
					l=1;
				}
				else
					l=0;
			}
			else if(ch==2){
				if(d==0){
					printf("\a\n\t\tInvalid Input");
					l=1;
				}
				else
					l=0;
			}
			else if(ch==3)
				l=0;
			else
				printf("\n\a\t\tInvalid Input");
		}while(l);
		switch(ch){
			case 1:
				temp=temp->pre;
				break;
			case 2:
				temp=temp->next;
				break;
			case 3:
				return;
		}
		c=0;
		d=0;
	}
}
short search(short id){
	short i;
	struct songs *temp=head;
	while(temp!=NULL){
		if(temp->sno==id)
			return 1;
		temp=temp->next;
	}
	return 0;
}
void delete_song(){
	short a,id;
	system("CLS");
	system("COLOR 4F");
	space(17); 
	printf("\t\tEnter Song Id : ");
	scanf("%hd",&id);
	a=search(id);
	if(a==0){
		printf("\n\a\t\tSong Id Not Found\n\t\tPress Any Key To Continue...");
		getch();
		return ;
	}
	struct songs *temp=head,*ptr;
	while(temp!=NULL){
		if(temp->sno==id)
			break;
		temp=temp->next;
	}
	if(temp->pre==NULL && temp->next==NULL){
		ptr=head;
		head=NULL;
		free(ptr);
		printf("\n\n\t\tDeletion Successfull\n\t\tPress Any Key to Continue...");
		getch();
		pos--;
		return;
	}
	if(temp->pre==NULL){
		ptr=head;
		head=ptr->next;
		head->pre=NULL;
		free(ptr);
	}
	else if(temp->next==NULL){
		ptr=temp;
		temp->pre->next=NULL;
		last=ptr->pre;
		free(ptr);
	}
	else{
		ptr=temp;
		temp->pre->next=ptr->next;
		temp->next->pre=ptr->pre;
		free(ptr);
	}
	printf("\n\n\t\tDeletion Successfull\n\t\tPress Any Key to Continue...");
	getch();
	pos--;
}
