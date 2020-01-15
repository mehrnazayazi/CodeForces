#include <iostream>
using namespace std;

int n,m;
int Head[80200], Cost[80200];
int End[80200];
int Y[80200], Next[80200];
int p[80200], l[80200],e[80200];
bool PathExists= true;



void AddEdge(int head, int end, int cost, int name){
    int i = 0, next;
    Head[name] = head;
    End[name] = end;
    Cost[name] = cost;
    if( Y[head]== -1){
        Y[head] = name;
    }else{
        int former = Y[head];
        int next = Next[former];
        while(next!= -1){//TODO change it to get back to head;
            former = next;
            next = Next[former];
        }
        Next[former] = name;
    }
}

void DeleteEdge(int name){
    bool secondHalf = false;
    bool isY = false, isOtherY = false;
    if(name >=m){
        secondHalf = true;
    }
    Head[name] = -1;
    End[name] = -1;
    int next  = Next[name];
    if(secondHalf){
        Head[name-m] = -1;
        End[name - m] = -1;
        int otherNext = Next[name - m];
        for (int i = 0; i < n; ++i) {
            if(Y[i] == name){
                Y[i] = next;
                isY = true;
            }
            if(Y[i]== name - m){
                Y[i] = otherNext;
                isOtherY = true;
            }
        }
        for (int j = 0; j < 2*m ; ++j) {
            if(!isY){
                if(Next[j] == name){
                    Next[j] = next;
                }
                if(!isOtherY){
                    if (Next[j] == name - m){
                        Next[j] = otherNext;
                    }
                }

            }

        }
    } else{
        Head[name+m] = -1;
        End[name+m] = -1;
        int otherNext = Next[name + m];
        for (int i = 0; i < n; ++i) {
            if(Y[i] == name){
                Y[i] = next;
                isY = true;
            }
            if(Y[i]== name + m){
                Y[i] = otherNext;
                isOtherY = true;
            }
        }
        for (int j = 0; j < 2*m ; ++j) {
            if(!isY){
                if(Next[j] == name){
                    Next[j] = next;
                }
                if(!isOtherY){
                    if (Next[j] == name - m){
                        Next[j] = otherNext;
                    }
                }

            }

        }
    }

}


void Dijktra(){
    bool uncoloured[n];
    l[0] = 0;
    p[0] = 0;
    e[0] = 0;
    uncoloured [0] = true;
    for (int i = 1; i < n; ++i) {
        p[i] = 0;
        uncoloured[i] = true;
        l[i] = INT_MAX;
        e[i] = -1;
    }
    bool uncoloured_exist = true;
    int u = 0;
    int counter = 0;
    while(uncoloured_exist){
        counter++;
        if(counter> 4 * m+3){
            if(l[n - 1] < INT_MAX){
                return;
            }
            PathExists = false;
            return;
        }
        uncoloured[u] = false;
        uncoloured_exist = false;
        int next = Y[u];
        while(next!=-1){
            int neighbor = End[next];
            if(uncoloured[neighbor]){
                if(l[neighbor] > l[u]+ Cost[next]){
                    l[neighbor] = l[u] + Cost[next];
                    e[neighbor] = next;
                    p[neighbor] = u;
                }
            }
            next = Next[next];
        }
        int min = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if(uncoloured[i]){
                uncoloured_exist = true;
                if(l[i] < min){
                    min = l[i];
                    u = i;
                }
            }
        }
    }
}


int main() {

    int x,y,w;
    cin>>n>>m;

    for(int i=0; i < n; i++){
        Y[i] = -1;
    }
    for(int i=0; i < 2 * m; i++){
        Next[i] = -1;
    }
    for (int i = 0; i <m ; ++i) {
        cin>>x>>y>>w;
        AddEdge(x-1,y-1,w,i);
        AddEdge(y-1,x-1,w,m+i);
    }
    Dijktra();
    if(!PathExists){
        cout<<"No solution";
        cout.flush();
        return 0;
    }
    int cost1 = 0, steps1 = 0;
    int path1[n];
    int i = n-1;
    while (i!=0){
        cost1+= Cost[e[i]];
        path1[steps1] = i;
        steps1++;
        DeleteEdge(e[i]);
        i = p[i];
    }
    path1[steps1] = 0;



    Dijktra();
    if(!PathExists){
        cout<< "No solution";
        cout.flush();
        return 0;
    }
    int cost2 = 0, steps2 = 0;
    int path2[n];
    i = n-1;
    while (i!=0){
        cost2+= Cost[e[i]];
        path2[steps2] = i;
        steps2++;
        i = p[i];
    }
    path2[steps2] = 0;

    if(cost1!=cost2){
        cout<<"No solution";
        cout<<endl;
        cout.flush();
        return 0;
    } else{
        for (int j = steps1; j >-1 ; --j) {
            cout<<path1[j]+1<<" ";
        }
        cout<<endl;
        cout.flush();
        for (int j = steps2; j >-1 ; --j) {
            cout<<path2[j]+1<<" ";
        }
        cout<<endl;
        cout.flush();

    }


}
