#include<iostream>
#include<cmath>
#include<vector>
#define t 5       //max linking length
#define minobjects 3 //min objects required to form clusters
// object class to store details of an object
using namespace std;
class object 
{
    public:
    double x,y,z;
     object()
    {
        x=0.0;
        y=0.0;
        z=0.0;
    }
}; 
// this function calculates the distance between obj1 and obj 2
float dist(object obj2,object obj1)
    {
        double x1 = pow((obj2.x- obj1.x),2);
        double y1 = pow((obj2.y- obj1.y),2);
        double z1 = pow((obj2.z- obj1.z),2);
        return sqrt(x1+y1+z1);
    }
bool is_safe(int j,vector<int> cluster,object ob[])
{
    double distance;
    int flag=0;
    for(int i=0;i<cluster.size();i++)
    {
        int ind=cluster[i]; //all indexes of cluster store index values of objects present in cluster
       distance = dist(ob[j],ob[ind]);
       if(distance>t || distance ==0)
       {
       return false;
       }
    }
    return true;
}
vector<vector<int>> getclusters(object ob[],int n,vector<int> &visited)    
{
    vector<vector<int>> clusters;
    for(int i=0;i<n;i++)
    {
        if(!visited[i])
        {
            bool tempvisit[n]={false};
            vector<int> cluster;
            tempvisit[i]=true;
            cluster.push_back(i);
            for(int j=i+1;j<n;j++)
            {
              if(!visited[j])
              {
                if(is_safe(j,cluster,ob))
                {
                    cluster.push_back(j);
                    tempvisit[j]=true;
                }
              }
            }
            if(cluster.size()>=minobjects)
            {
               for(int j=i;j<n;j++)
               {
                if(tempvisit[j]) visited[j]=true;
               }
               clusters.push_back(cluster);
            }
        }
    }
    return clusters;
}
void display(vector<vector<int>> clusters,object ob[],vector<int> & visited)
{
    int i;
     cout<<"\n******************************************************************************\n";
    cout<<"\n\n A cluster is  formed only if "<<minobjects<<" or more objects are such that \n distance of every point from each other is less than or equal to "<<t<<" . \n\n";
    cout<<"\n______________________________________________________________________________\n";
    for(i=0;i<clusters.size();i++)
    {
        cout<<"\n Cluster "<< i+1<<" include objects >  \n"; 
        for(int j=0;j<clusters[i].size();j++)
        {
         int oind=clusters[i][j];
          cout<<"                             "<< oind+1 <<" :  ("<<ob[oind].x<<" , "<<ob[oind].y<<" , "<<ob[oind].z<<")\n";
        }
        cout<<endl;
    }
   
    cout<<" Total number of clusters formed : "<<i<<endl;
     cout<<" Objects not included in any cluster : \n \n ";
     int l=visited.size();
     bool flag=false;
     for(int i=0; i<l;i++)
     {
         if(!visited[i])
         {
            flag=true;
            cout<<"                             "<< i+1 <<" :  ("<<ob[i].x<<" , "<<ob[i].y<<" , "<<ob[i].z<<")\n";
         }
     }
     if(!flag)
     cout<<" none \n";
    cout<<"\n______________________________________________________________________________\n";

}
int clustersidentification()
{
    int number;
    double scale;
    cout<<"Enter the number of astronimical objects  :  ";
    cin>>number;
    cout<<"\n Enter the scale : ";
    cin>>scale;//scale will be 10 if user inputs 3 for distance 30
    object *ob=new object[number] ;//creating 'number' number of objects
    double x,y,z;
    for(int i=0;i<number;i++)//initialising all objects
    {
        cout<<"\n Enter the x ,y , z coordinates of object "<<i+1 <<" : ";
        cin>>ob[i].x>>ob[i].y>>ob[i].z;
    } 
    vector<int> visited(number,0);
 
     vector<vector<int>> ans=getclusters(ob,number,visited);
    display(ans,ob,visited);
    return 0;
}
