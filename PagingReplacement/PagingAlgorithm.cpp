//This model implements three different algorithm for paging replacement: FIFO,　OPT, and LRU
    /*Paging algorithms mainly implement the replacement policy. 
     * There are two groups of paging algorithms used in virtual memory management: 
     * (1) those based on static frame allocation and static paging algorithms and 
     * (2) those based on dynamic frame allocation and dynamic paging algorithms. 
     * This project consists of designing and executing a program using any IDE (C, C++, or Java) 
     * to implement one the following static paging algorithms:
     * FIFO algorithm (Hint: refer to section 10.7.1.1 for detailed algorithm starting on page 283.)
     * Optimal algorithm (Hint: refer to section 10.7.1.3 for detailed algorithm starting on page 288.)
     * Least Recently Used algorithm
     */
    #include<iostream>
     
    using namespace std;
     
    int found(int x,int *l,int max)
    {
        for(int i=0;i<max;i++)
            if(l[i]==x)
                return i;
        return(-1);
    }
    
    int nextreplace(int x,int j, int f[], int length)
    {
        for(int i=j+1;i<length;i++)
            if(x==f[i])
                return i-j;
        return length-j;
    }
    
    int findmaxindex(int f[],int length)
    {
        int max=0;
        for(int i=1;i<length;i++)
            if(f[i]>f[max])
                max=i;
        return max;
    }
    
    void FIFO(int *l, int max, int f[], int length)
    {
        int x;
        int j=0,k=0,c=0,res;
        cout<<"\n\nEnter the sequence of page requests(enter -1 to stop):\t";
            while(j<length)
            {
                    x=f[j];
                    if(x==-1) {cout<<"\n\n";break;}
                    else{
                   
                    if(k<max)
                    {
                            if((res=found(x,l,max))!=-1) 
                            {
                                cout<<"\n\npage "<<x<<" already exists in frame "<<res<<" in MM";
                            }
                            else
                            {
                                    cout<<"\n\npage "<<x<<" has been allocated a frame "<<k<<" in MM.";
                                    l[k++]=x;
                            }
                            cout<<"\n\nNext page:"<<f[j++]<<endl;
                            cout<<"\nNow our frames are: "<<endl;
                            for(int i=0;i<max;i++)
                                cout<<"P"<<i<<" is "<<l[i]<<endl;
                    }
                    else
                    {
                            if((res=found(x,l,max))!=-1) 
                            {
                                cout<<"\n\npage "<<x<<" already exists in frame "<<res<<" in MM";
                            }
                            else
                            {
                                cout<<"\n\npage fault has occured";
                                cout<<"\n\npage "<<x<<" has been allocated frame "<<c<<" in MM by replacing page "<<l[c];
                                l[c]=x;
                                c=(c+1)%max;
                            }
                            cout<<"\n\nNext page:"<<f[j++]<<endl;
                            cout<<"\nNow our frames are: "<<endl;
                            for(int i=0;i<max;i++)
                                cout<<"P"<<i<<" is "<<l[i]<<endl;
                    }
                    }
            }
    }
    
    void OPT(int *l, int max, int f[], int length)
    {
        int x;
        int j=0,k=0,res;
        cout<<"\n\nEnter the sequence of page requests(enter -1 to stop):\t";
            while(j<length)
            {
                    x=f[j];
                    if(x==-1) {cout<<"\n\n";break;}
                    else{
                        if(k<max)
                            {
                                if((res=found(x,l,max))!=-1) 
                                    {
                                        cout<<"\n\npage "<<x<<" already exists in frame "<<res<<" in MM";
                                    }
                                else
                                    {
                                        cout<<"\n\npage "<<x<<" has been allocated a frame "<<k<<" in MM.";
                                        l[k++]=x;
                                    }
                            cout<<"\n\nNext page:"<<f[j++]<<endl;
                            cout<<"\nNow our frames are: "<<endl;
                            for(int i=0;i<max;i++)
                                cout<<"P"<<i<<" is "<<l[i]<<endl;
                            }
                        else
                            {
                                if((res=found(x,l,max))!=-1) 
                                {
                                    cout<<"\n\npage "<<x<<" already exists in frame "<<res<<" in MM";
                                }
                                else
                                    {
                                        int r=0,res;
                                        for(int i=0;i<max;i++)
                                            if(r<nextreplace(l[i],j,f,length))
                                            {
                                                r=nextreplace(l[i],j,f,length);
                                                res=l[i];
                                            }
                                        for(int c=0;c<max;c++)
                                            if(l[c]==res)
                                            {
                                                l[c]=x;
                                                cout<<"\n\npage fault has occured";
                                                cout<<"\n\npage "<<x<<" has been allocated frame "<<c<<" in MM by replacing page "<<l[c];
                                            }
                                    }
                                    cout<<"\n\nNext page:"<<f[j++]<<endl;
                                    cout<<"\nNow our frames are: "<<endl;
                                    for(int i=0;i<max;i++)
                                        cout<<"P"<<i<<" is "<<l[i]<<endl;
                            }
                    }
            }
    }
    
    void LRU(int *l, int max, int f[], int length)
    {
        int x;
        int j=0,k=0,c=0,res;
        int use[]={0,0,0};
        cout<<"\n\nEnter the sequence of page requests(enter -1 to stop):\t";
            while(j<length)
            {
                    x=f[j];
                    if(x==-1) {cout<<"\n\n";break;}
                    else{
                   
                    if(k<max)
                    {
                            if((res=found(x,l,max))!=-1) 
                            {
                                cout<<"\n\npage "<<x<<" already exists in frame "<<res<<" in MM";
                                use[res]=0;
                            }
                            else
                            {
                                cout<<"\n\npage "<<x<<" has been allocated a frame "<<k<<" in MM.";
                                for(int i=0;i<k;i++)
                                    if(i!=k)
                                        use[i]=use[i]+1;
                                    else
                                        use[i]=0;
                                l[k++]=x;
                            }
                            cout<<"\n\nNext page:"<<f[j++]<<endl;
                            cout<<"\nNow our frames are: "<<endl;
                            for(int i=0;i<max;i++)
                                cout<<"P"<<i<<" is "<<l[i]<<endl;
                    }
                    else
                    {
                            if((res=found(x,l,max))!=-1) 
                            {
                                cout<<"\n\npage "<<x<<" already exists in frame "<<res<<" in MM";
                                for(int i=0;i<max;i++)
                                {
                                    if(i!=res)
                                        use[i]=use[i]+1;
                                }
                                use[res]=0;
                            }
                            else
                            {
                                c=findmaxindex(use,max);
                                l[c]=x;
                                cout<<"\n\npage fault has occured";
                                cout<<"\n\npage "<<x<<" has been allocated frame "<<c<<" in MM by replacing page "<<l[c];
                                for(int i=0;i<max;i++)
                                {
                                    if(i!=c)
                                        use[i]=use[i]+1;
                                }
                                use[c]=0;
                            }
                            cout<<"\n\nNext page:"<<f[j++]<<endl;
                            cout<<"\nNow our frames are: "<<endl;
                            for(int i=0;i<max;i++)
                                cout<<"P"<<i<<" is "<<l[i]<<endl;
                    }
                    }
            }
    }
     
    int main()
    {
            cout<<"Enter the maximum number of frames in the main memory:\t";
            int max;
            cin>>max;
            int *l=new int[max];
            for(int i=0;i<max;i++)
                l[i]=-1;
            int f[]={1,2,3,4,2,3,4,1,2,1,1,3,1,4};
            cout<<"The following sequence are replacement pages: ";
            for(int i=0;i<14;i++)
                cout<<f[i]<<" ";
            cout<<endl;
            cout<<"Select 1 for FIFO, Select 2 for OPT, Select 3 for LRU. Enter the number you select for paging replacement algorithm"<<endl;
            int s;
            cin>>s;
            if(s==1)
                FIFO(l,max,f,14);
            else if(s==2)
                OPT(l,max,f,14);
            else if(s==3)
                LRU(l,max,f,14);
            else
                cout<<"Invalid Input"<<endl;
    }