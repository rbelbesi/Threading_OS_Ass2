/*Team members: Noor Omar Burini 136799
		Roaa Ziad Batta 137307
		Sarah Ahmad Mhaidat 135140 */

#include <iostream>
#include <cmath>
#include <pthread.h>
#include <set>
using namespace std;

int numOfPrimes=0;
int TotalNums=0;
set <int> PrimeList;

struct arg
{
int i;
int start;
int end;
int range;
};

void * prime(void *par){
  
  arg * x = (arg*)par;

  if(x->i >= x->range)
  cout<<"ThreadID="<< x->i <<" : not needed."<<endl;
 
  else
  {
  cout<<"ThreadID="<< x->i ;
  cout<<", startNum="<< x->start ;
  cout<<", endNum="<< x->end << endl;
  }
 
  bool flag=false; // local variable it is independent for each thread
  int i;
  
  if(x->i == 0)
 	i = x->start;
  else
  	i = x->start+1;
  
  
  for(i ; i<= x->end ; i++)
  {      
    for(int j=2 ; j <= sqrt(i) ; j++)
    {
      if(i%j==0)
      { 
        flag=true;
        break;
      }     
    }
       
   if(flag == false)
    {
      PrimeList.insert(i);   	
      numOfPrimes++;
    }
    
    flag=false;  
    TotalNums++;
  }  
  return NULL;
}

int main(int argc , char* argv[]){
  
  int start,end,T;

  freopen("in.txt","r",stdin);
  cin>>start;
  cin>>end;
  
  if(argc >= 2){
    T = strtol(argv[1],NULL,10); 
    pthread_t *threads = new pthread_t[T];
    int rng=end-start , num , point=start , mod=0;
    arg x;
    x.range=rng;
    
    if(rng%T==0)
      num=rng/T;
    else
      {
      mod=rng%T;
      rng-=mod;
      num=rng/T;
      } 
      
    for(int i =0; i<T ; i++){
      x.i=i;          
      if(mod==0)
      {
        x.start=point;
        x.end=point+num;
        pthread_create(&threads[i] ,NULL , prime , (void *)&x);   
        point+=num;  
        pthread_join(threads[i],NULL);
       }     
      else
      {
        x.start=point;
        x.end=point+num+1; 
        pthread_create(&threads[i] ,NULL , prime , (void *)&x);     
        mod--;
        point+=(num+1);
        pthread_join(threads[i],NULL);
      }
    }   
  }
  cout<< "numOfPrime=" << numOfPrimes << " , totalNums="<< TotalNums << endl; 

  freopen("out.txt","w",stdout);
    
  cout << "the prime numbers are: " << endl; 
  
  for(auto &n:PrimeList)
  	cout<<n<<endl;
}