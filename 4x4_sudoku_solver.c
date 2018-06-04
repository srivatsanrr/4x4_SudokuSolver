#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
Author: Srivatsan
Date: 03/06/2018 
A 4x4 sudoku solver built during tea time this evening :)
Change init function to try different sudoku problems

*/

int size = 4; 
int box[4][4]; 
const int step = 2; 



int dispKer(int (*ker)[2])
{
	int i, j; 
	for (i=0; i<2; i++){
	
	for (j = 0; j<2; j++)
	printf("%d\t", ker[i][j]); 
		printf("\n"); 
}

}

int init(int def){// call with 0 for custom input problem
	int ret=1, i, j, k, n;
	for (i=0; i<size; i++)
	for (j=0; j<size; j++){
		
		box[i][j] = -1; 
	}
	//problem init - 
	if (def){
		box[0][1]=3;
		box[0][2]=4;
		box[1][3]=2;
		box[2][3]=4;
		box[3][1]=4;
		box[3][2]=2;		
	}
	else
		{
			
			printf("Enter 4x4 Sudoku problem (Enter -1 for empty spaces)\n\n");  
			for (i=0; i<size; i++)
			for (j=0; j<size; j++){
				scanf("%d",&n); 
				if(n!=-1)
				box[i][j] = n; 
			}
		}
	
	if (box==NULL)
	ret = 0; 
	return (ret); 
}

int assignKernel(int (*kernel)[2], int s){
	int r, c, k = 0, l = 0, i, j; 
	switch(s){
		case 0:
			r = step;
			c = step;  
			break; 
			
		case 1:
			r = step;
			c = step*2;  
			break; 
			
		case 2:
			r = step*2;
			c = step*2;  
			break; 
			
		case 3:
			r = step*2;
			c = step;  
			break; 
	}
	for (i = r-step; i<r; i++)
		for (j = c-step; j<c; j++){
			if (k==step)
			{
				k = 0; 
				l++; 
			}
			kernel [k][l++] = box[i][j]; 
		}
		if(kernel==NULL)
		return (0);
		 
		return(1); 
	}
	
int assignAdjacent(int  (*adjr)[2], int (*adjc)[2], int kno){
	switch(kno){
	case 0:
	assignKernel(adjr,1);
	assignKernel(adjc, 3);  
	
	break; 
	
	case 1:
	assignKernel(adjr,0);
	assignKernel(adjc, 2);  
	
	break; 
	
	case 2:
	assignKernel(adjr, 3);
	assignKernel(adjc, 1);  
	
	break; 
	
	case 3:
	assignKernel(adjr, 2);
	assignKernel(adjc, 0);  
	
	break; 
	
	}
	if  (adjr && adjc)
	return (1); 
	else 
	return (0); 
	
}


int checkdone(){
	int ret = 1, i, j;
	for(i= 0; i<size; i++)
	for(j =0; j<size; j++)
	if(box[i][j]==-1)
	{
	ret = 0; 
	break; 
	}
	return (ret); 
	
}
int  * posofnum(int (*arr)[2], int n){
 	int i, j, * pos = NULL; 
 	
 	for (i = 0; i<step; i++){
 		for (j = 0; j<step; j++)
 			if (arr[i][j]==n)
 			{
 			 pos = (int*)malloc(2*sizeof(int)); 
			 int pos1 [2]= {i,j};  
			 pos = pos1; 
			 break; 
			}
	 }
	 return (pos);  
 }

int updateboxwithkernel(int kernel[][2], int s){
		int r, c, k = 0, l = 0, i, j; 
	switch(s){
		case 0:
			r = step;
			c = step;  
			break; 
			
		case 1:
			r = step;
			c = step*2;  
			break; 
			
		case 2:
			r = step*2;
			c = step*2;  
			break; 
			
		case 3:
			r = step*2;
			c = step;  
			break; 
	}
	for (i = r-step; i<r; i++)
		for (j = c-step; j<c; j++){
			if (k==step)
			{
				k = 0; 
				l++; 
			}
			box[i][j] = kernel [k][l++]; 
		}
}

int disp_board(){
	int i, j; 
	for(i= 0; i<size; i++)
	{
	for(j =0; j<size; j++)
	printf("%d\t", box[i][j]); 
	printf("\n"); 
	}
	printf("\n"); 
	return; 
}

int main(){
	int i, j, k, num, l1, l2, nos[4] ={1, 2, 3, 4}, cnt=0, str, *strpos, t, def;
	char ch;
	int adjr[step][step], adjc[step][step], kernel[step][step], *pos; 
	int solved = 0; 
	int nr, nc;
	printf("Enter 0 for custom problem 1 otherwise \n"); 
	scanf("%d", &def); 
	
	if(!init(def)){
		printf("Memory Unavailable\n");
		exit(1);  //erroneous exit
	}  
	printf("Initial Sudoku!\n"); 
	disp_board(); 
	getch(); 
	while(!solved){
		for (i = 0; i<size; i++)// to iterate through each of the sub-boxes; could iterate the kernel row,col wise (-towards generalising to other sizes) but no time
		{
			if(!assignKernel(kernel, i)){
				
			printf("Kernel Unavailable\n");
			exit(1);  //erroneous exit
			}	
			if(!assignAdjacent(adjr,adjc, i)){
				
			printf("Kernel Adjacents Unavailable\n");
			exit(1);  //erroneous exit
			}

			for (j=0; j<step; j++)
			for (k = 0; k<step; k++){
				num = adjc[j][k]; 
				nr = nc = -1; 
				
				//first case
				if (num>-1){

					pos = posofnum(adjr, num);
					if(pos!=NULL)
					{
						nr = ((pos[0]==0)?1:0); 
						nc = k==0?1:0; 
					}
					if (posofnum(kernel, num)==NULL && nr!=-1)
						{
						kernel[nr][nc] = num;

						}
				
				//second case
				nc = k==0?1:0;
				l1 = !(kernel[0][k]==num || kernel[1][k]==num) &&nc!=-1 && (posofnum(kernel, num)==NULL); //logic1
				if( l1 && kernel[0][nc]>-1)
					kernel[1][nc] = num; 
				else if(l1 &&kernel[1][nc]>-1)
					kernel[0][nc] = num; 
				updateboxwithkernel(kernel, i); 
				}
				
				//third case
				num = adjr[j][k]; 
				if(num>-1){
				nr = j==0?1:0;
				l2 = !(kernel[j][0]==num || kernel[j][1]==num)&&nr!=-1 && (posofnum(kernel, num)==NULL); //logic2
				if( l2 && kernel[nr][0]>-1)
					kernel[nr][1] = num; 
				else if(l2 &&kernel[nr][1]>-1)
					kernel[nr][0] = num;  	
				}
						
					
				}
				//fourth case
				cnt=0; 
				for (t= 0; t<size; t++)
				{
					pos = posofnum(kernel, t+1); 
					if(pos != NULL)
					cnt++; 
					else
					{
					str = t+1;
					}
				}					

				pos = posofnum(kernel, -1); 
				if (cnt==3)
				kernel[pos[0]][pos[1]] = str; 
				
				updateboxwithkernel(kernel, i);//updates big box with minibox values
		
		}	
//		disp_board(); 
		solved = checkdone(box); 
//		ch = getch(); 
//		
//		if(((int)ch)==27)
//		break; 
			
	}
	printf("Solved Sudoku!\n"); 
	disp_board(); 
	getch(); 
	return(0); 
	}
	

