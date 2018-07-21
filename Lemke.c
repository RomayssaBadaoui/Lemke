
#include <stdio.h>
#include <stdlib.h>


float**remplir_matrice(int n){
int i,j;
float**matrice;
matrice= (float**)calloc(n, sizeof(float*));
for (i=0 ; i<n ; i++){
matrice[i] = (float*)calloc(n, sizeof(float));
}
printf("Enter the matrix line by line  \n");
for(i=0;i<n;i++){
for(j=0;j<n;j++){
scanf("%f",&matrice[i][j]);
}

}
return matrice;
}
float*remplir_vecteur(int n){
int i;
float*q;
q=(float*)malloc(n*sizeof(float));
printf("Enter the vector q : \n");
for(i=0;i<n;i++){
scanf("%f",&q[i]);
}
return q;
}

float**tabl(float**M,int tailleM,float*q){
	float**mat;
	int i,j;
mat= (float**)calloc(tailleM+1, sizeof(float*));
for (i=0 ; i<tailleM+1 ; i++){
mat[i] = (float*)calloc(2*tailleM+3, sizeof(float));
}
for(i=0;i<tailleM+1;i++){
mat[i][0]=i;
}
for(j=0;j<2*tailleM+3;j++){
mat[0][j]=j;
}
for(i=1;i<=tailleM;i++){
for(j=1;j<=tailleM;j++){
if(i==j){
mat[i][j]=1;
}else{mat[i][j]=0;}
}
}
for(i=0;i<tailleM;i++){
for(j=0;j<tailleM;j++){
mat[i+1][tailleM+1+j]=-M[i][j];
}
}

for(i=1;i<tailleM+1;i++){
mat[i][2*tailleM+2]=q[i-1];
mat[i][2*tailleM+1]=-1;
}
return mat;
}
void mat_pivot(int lp,int cp,float**A,int n,int m){
int j,k=1;
float v,u;
u=A[lp][cp];
for(j=1;j<m;j++){
A[lp][j]=(A[lp][j])/u;
}
while(k<n){
if(k!=lp){
u= A[k][cp]/A[lp][cp];
for(j=1;j<m;j++){
v=A[lp][j];
A[k][j]=A[k][j]-u*v;
}
if(k==lp){

}
}
k++;
}
}

int test1(float** A,int n,int m){
int i,j=0;
float min=1000;
for(i=1;i<n;i++){
if((A[i][m-1]<0) && (min>A[i][m-1])){
min=A[i][m-1];
j=i;
}
}
return j;
}
int test2(int colone,float**A,int n,int m){
int i,p=0;
float min=1000;
for(i=1;i<n;i++){
if(A[i][colone]>0 && min > A[i][m-1]/A[i][colone]){
min=A[i][m-1]/A[i][colone];
p=i;
}
}
return p;
}
void permute(int i,int j,float**A){
float x;
x=A[i][0];
A[i][0]=A[0][j];
A[0][j]=x;
}
int  lemke( float**A,int n,int m){
	int r=test1( A, n, m);
	int i,p,c,E;
	E=1;
if(r!=0 ){;
mat_pivot(r,m-2,A, n, m);
A[r][0]=m-2;
c=r+(n-1);
do{
p=c;
i=test2(c,A,n,m);
if(i==0){
E=0;
}else if(i!=0){
E=1;
mat_pivot(i,c,A, n, m);
if(A[i][0]<=n-1){
c=A[i][0]+n-1;
A[i][0]=A[0][p];
}else if(A[i][0]>n-1 && A[i][0]<m-2){
c=2*(n-1)-A[i][0];
A[i][0]=A[0][p];
}
}
}while(i!=0 && A[i][0]!=m-2);
A[i][0]=A[0][c];
}
return E;
 }

 void afficher_solution(float**A,float*q,int n,int m){
    int i,p,j=2*(n-1);
    float*s;
 	s = (float*)malloc(j*sizeof(float));
 	for(i=0;i<j;i++){
 	s[i]=0;
	}
 	for(i=1;i<n;i++){
 	p=A[i][0];
 	s[p-1]=A[i][m-1];
	 }
	 for(i=0;i<n-1;i++){
	printf("w(%d)=  %.000f \n",i+1,s[i]);
	 }
	 j=1;
	 for(i=n-1;i<2*(n-1);i++){
	printf("z(%d)=  %.000f \n",j ,s[i]);
	j++;
	 }
 }

int main() {
	int e,n;
	float*q;
	float**tab=0;
	float **m;
	printf("Enter the size of the square matrix : \n");
	scanf("%d",&n);
m=remplir_matrice(n);
q=remplir_vecteur(n);
 tab=tabl(m,n,q);
 printf("\n");
e=lemke( tab,n+1,2*n+3);
 if(e!=0){
 	 printf("The solution is : \n");
 afficher_solution(tab,q,n+1,2*n+3);
 }else{
printf("No solution");
 }

	return 0;
}

