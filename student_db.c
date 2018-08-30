#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void tostring(char [], int);
 
struct student{
    char name[25],id[10],mail[50];
    int rollno;
    unsigned long long mobileno;
};

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

int main()
{
    FILE *fp,*ft,*fb;;
    struct student std;
    int choice,n;
    char stdid[25],another;
    time_t T= time(NULL);
    struct  tm tm = *localtime(&T);
    char s[20] = "back/Backup_";
    char str[10],m;
		    	
    while(1){
	    fp=fopen("students.txt","ab+");
	    rewind(fp);
	    printf("Menu :=\n\t1.Add records\n");
	    printf("\t2.Search student record\n");
	    printf("\t3.View records\n");
	    printf("\t4.Modify records\n");
	    printf("\t5.Delete records\n");
	    printf("\t6.Backup records\n");
	    printf("\t7.Restore records\n");
	    printf("\t0.Exit\n");
	    printf("Enter your choice (0-7) :");
	    scanf("%d",&choice);
	    printf("Your choice : %d\n\n",choice);
	    switch(choice){
		case 1 :
		    another='y';
		    while(another=='y'){
		        printf("Enter details of students !\n");
		        printf("\tEnter name : ");
		        scanf("%s",std.name);
		        printf("\tEnter ID : ");
		        scanf("%s",std.id);
		        printf("\tEnter Roll number : ");
		        scanf("%d",&std.rollno);
		        printf("\tEnter you Email :");
		        scanf("%s",std.mail);
		        printf("\tEnter mobile number : ");
		        scanf("%llu",&std.mobileno);
		        fwrite(&std,sizeof(std),1,fp);
		        printf("You entered : \n Name : %s\n ID : %s\n Roll No: %d\n Email: %s\n Mobile No : %llu\n",std.name, std.id, std.rollno, std.mail, std.mobileno);   
		        printf("Do you want to add ANOTHER Student records? (y/n) ");
		        scanf(" %c",&another);
		    }
		    fclose(fp);
		    //printf("%c",another);
		    break; 
		case 2 :
		    //fclose(fp);
		    //fp=fopen("students.txt","r+");
		    another='y';
		    while(another=='y'){
		    	fseek(fp, sizeof(std), SEEK_SET);
		        printf("Enter the ID of a Student: ");
		        scanf("%s",stdid);
		        int flag = 0;
		        while(fread(&std,sizeof(std),1,fp)==1){
		            if(strcmp(std.id,stdid)==0){
		            	printf("Details of Student := \n Name : %s\n ID : %s\n Roll No: %d\n Email: %s\n Mobile No : %llu\n\n",std.name, std.id, std.rollno, std.mail, std.mobileno);
		                flag = 1;
		            }
		        }
		        if(flag == 0)
		        	printf("Record is not found\n");
		        printf("Do you want to search ANOTHER Student records? (y/n) ");
		        scanf(" %c",&another);
		    }
		    fclose(fp);   
		    break;
			
		    
		case 3 :
			fseek(fp, sizeof(std), SEEK_CUR);
			if(fp==NULL){
        			printf("File doesn't exist !");
			        exit(1);
    			}
    			printf("Student Details := \n Name \t ID No \t   Roll No: \t Email \t\t\t Mobile No \n");   

			while(fread(&std,sizeof(std),1,fp)==1){
			printf("%s\t %s \t %d\t %s\t %llu\n",std.name, std.id, std.rollno,  std.mail, std.mobileno);
		    }
		    printf("\n");
		    fclose(fp);
		    break;
		case 4 :
		    fclose(fp);
		    fp=fopen("students.txt","r+");
		    another='y';
		    while(another=='y'){
		        printf("Enter the ID of a Student : ");
		        scanf("%s",stdid);
		        int flag = 0;
		        char m = 'y';
		        int point = 0;
		        ft=fopen("temp.txt","w+");
		        rewind(fp);
		        while(fread(&std,sizeof(std),1,fp)==1){
		            point++;
		            if(strcmp(std.id,stdid)==0){
		            	printf("Details of Student := \n Name : %s\n ID : %s\n Roll No: %d\n Email: %s\n Mobile No : %llu\n",std.name, std.id, std.rollno,  std.mail, std.mobileno);
		            	printf("\nDo you want modify? (y/n)");
		            	scanf(" %c",&m);
		            	if(m == 'n'){
		            		fwrite(&std,sizeof(std),1,ft);
		            		flag=1;
		            	}else{
		                printf("Enter new details of students !\n");
		                printf("Enter name : ");
		                scanf("%s",std.name);
		                printf("\nEnter ID : ");
		                scanf("%s",std.id);
		                printf("\nEnter Roll number : ");
		                scanf("%d",&std.rollno);
		                printf("\nEnter Email : ");
		                scanf("%s",std.mail);
		                printf("\nEnter Mobile Number : ");
		                scanf("%llu",&std.mobileno);
		                printf("You entered : \n Name : %s\n ID : %s\n Roll No: %d\n Email: %s\n Mobile No : %llu\n",std.name, std.id, std.rollno, std.mail, std.mobileno);
		                //fseek(fp, (point * sizeof(std)), SEEK_CUR);
		                fwrite(&std,sizeof(std),1,ft);
		                flag = 1;
		                }
		            }else{
		            	fwrite(&std,sizeof(std),1,ft);
		            }
		        }
		        if(flag == 0)
		        	printf("Record is not found\n");
		        fclose(fp);
		        fclose(ft);
		        rename("temp.txt","students.txt");
		        fp=fopen("students.txt","rb");
		        printf("Do you want to modify ANOTHER Student records? (y/n) ");
		        scanf(" %c",&another);
		        //printf("%c",another);
		    }
		    fclose(fp);       
		    break;
		case 5 :
		     another = 'y';
		    while(another=='y'){
		        printf("Enter the Student ID to delete : ");
		        scanf("%s",stdid);
		        char m = 'y';
		        printf("Do you want to delte %s records? (y/n)",stdid);
		        scanf(" %c",&m);
		        int flag = 0;
		        if(m == 'y'){
		        	
				ft=fopen("temp.txt","w+");
				rewind(fp);
				
				while(fread(&std,sizeof(std),1,fp)==1){
				    if(strcmp(std.id,stdid)!=0){
				        fwrite(&std,sizeof(std),1,ft);
				    }else
				    	flag = 1;
				}
				fclose(fp);
				fclose(ft);
				//remove("std.txt");
				rename("temp.txt","students.txt");
				fp=fopen("students.txt","rb");
			}else{ flag=1;}
			if(flag == 0)
		        	printf("Record is not found\n");
		        printf("Do you want to delete ANOTHER Student records? (y/n) ");
		        scanf(" %c",&another); 
		    }
		    fclose(fp);       
		    break;
		case 6 :		    	
		    	tostring(str, tm.tm_mday);  
		    	strcat(s,str);  
		    	if(tm.tm_mon+1 < 10)
		    		strcat(s,"0");
		    	tostring(str, tm.tm_mon+1);  
		    	strcat(s,str);
		    	tostring(str, tm.tm_year+1900);  
		    	strcat(s,str);
		    	strcat(s,".DAT");
		    	
			ft=fopen("backup.txt","w+");
			fb=fopen(s,"w+");
			rewind(fp);
				
			while(fread(&std,sizeof(std),1,fp)==1){
				        fwrite(&std,sizeof(std),1,ft);
				        fwrite(&std,sizeof(std),1,fb);
			}
			fclose(fp);
			fclose(ft);
			fclose(fb); 
				
		        printf("\n\tSuccessfully backuped!\n");
		    	fclose(fp);
		    	break;
		case 7 :
		    	m = 'y';
		        printf("Your current records will be no long available? (y/n)");
		        scanf(" %c",&m);
		        int flag = 0;
		        if(m == 'y'){
		        	fb = fopen("backup.txt","r+");
				ft=fopen("temp.txt","w+");
				rewind(fp);
				
				while(fread(&std,sizeof(std),1,fb)==1){
				        fwrite(&std,sizeof(std),1,ft);
				}
				fclose(fb);
				fclose(fp);
				fclose(ft);
				//remove("std.txt");
				rename("temp.txt","students.txt");
				fp=fopen("students.txt","rb");
			}
		        printf("\n\tRestored successfully completed !\n");		    
		    	fclose(fp);       
		    	break;
		case 0 :
		    printf("\nBye, Have a great day!\n");
		    fclose(fp);
		    exit(0);
	    }
	}
    return 0;
}
