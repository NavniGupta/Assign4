#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include <vector>
#include <set>
#include <list>
using namespace std;

unsigned int n;
string str;
struct Edge{
    unsigned v1,v2;
};

typedef std::vector<unsigned> VertexVec;
typedef std::list<unsigned > VertexList;
typedef std::vector<VertexList> AdjacencyList;
typedef std::vector<VertexList> VertexCover;
vector<unsigned int> outputE_copy;
vector<unsigned int> outputV;

struct Graph{

    AdjacencyList adjacency;
    VertexCover vertex_cover;
    void init(unsigned num_vertices);
    void add(Edge e);
    void clear(unsigned v);
};

void vsplit()
{
    outputV.clear();
    outputE_copy.clear();

    std::vector<std::string> a;
     std::size_t prev_pos = 0, pos;
         while ((pos = str.find_first_of(" ", prev_pos)) != std::string::npos)
         {
            if (pos > prev_pos)
              a.push_back(str.substr(prev_pos, pos-prev_pos));
            prev_pos= pos+1;
         }
        if (prev_pos< str.length())
            a.push_back(str.substr(prev_pos, std::string::npos));





for (auto &s : a) {
    std::stringstream parser(s);
    unsigned int x = 0;

    parser >> x;

    outputV.push_back(x);
}
n=outputV[1];

}


void Source_Dest(Graph &gp)
{
    gp.init(n);

    unsigned int u,v;
    for(unsigned int j=1; j<outputE_copy.size(); j=j+2)
       {
           u=outputE_copy[j-1];
           v=outputE_copy[j];
           gp.add({u,v});


       }
}

/*

void APPROX_VC2(Graph &graph)
{
    Graph &graph_input = graph;
    bool visited[n];
    for (unsigned int i=0; i<n; i++)
        visited[i] = false;

    list<unsigned int>::iterator i;

    // Consider all edges one by one
    for (unsigned int u=0; u<n; u++)
    {
        // An edge is only picked when both visited[u] and visited[v]
        // are false
        if (visited[u] == false)
        {
            // Go through all adjacents of u and pick the first not
            // yet visited vertex (We are basically picking an edge
            // (u, v) from remaining edges.
            for (i= graph_input.adjacency[u].begin(); i != graph_input.adjacency[u].end(); ++i)
            //for (i= graph_input.adjacency[u].begin(); i != graph_input.adjacency[u].end(); ++i)

            {
                int v = *i;
                if (visited[v] == false)
                {
                     // Add the vertices (u, v) to the result set.
                     // We make the vertex u and v visited so that
                     // all edges from/to them would be ignored
                     visited[v] = true;
                     visited[u]  = true;
                     break;
                }
            }
        }
    }

    // Print the vertex cover
    for (unsigned int i=0; i<n; i++)
        if (visited[i])
          cout << i << " ";

}
*/
void APPROX_VC1(Graph &graph)
{

Graph &graph_input = graph;
VertexVec &C = *new VertexVec();

while(n>0)
{
     auto v = std::max_element(
                graph_input.adjacency.begin(),graph_input.adjacency.end(),
                [](VertexList &list1, VertexList &list2)->bool{ return list1.size()<list2.size(); } //?
        );
    unsigned i = (unsigned)(v-graph_input.adjacency.begin());
    C.push_back(i);
    graph_input.clear(i);


}
std::sort( C.begin(), C.end(), std::less<int>());
    std::cout<<"APPROX-VC-1: "<< C;
//    return &C;
}
void Esplit()
{
    Graph &graph_input = *new Graph();
    //adjaceny_matrix.clear();
    vector<string> b;
     std::size_t prev_pos = 0, pos;
         while ((pos = str.find_first_of("{<,>}", prev_pos)) != std::string::npos)
         {
            if (pos > prev_pos)
              b.push_back(str.substr(prev_pos, pos-prev_pos));
            prev_pos= pos+1;
         }
        if (prev_pos< str.length())
            b.push_back(str.substr(prev_pos, std::string::npos));
    vector<unsigned int> outputE;



    for (auto &s : b) {

        std::stringstream parser(s);
        unsigned int x = 0;

        parser >> x;

    outputE.push_back(x);
}

unsigned int check=0;
   for (unsigned int i=1; i<outputE.size(); i++)
   {
        if(outputE[i]>=0 && outputE[i]<n)
        {
            outputE_copy.push_back(outputE[i]);
        }
       else{
        check=1;
       }
   }

if(check==1)
{
    cout<<"Error: Edges out of range"<<endl;
}

 Source_Dest(graph_input);

 //APPROX_VC2(graph_input);
APPROX_VC1(graph_input);

}


void Graph::init(unsigned n){
    adjacency.clear();
    //num_edges = 0;
    adjacency.resize(n,{});
}

void Graph::add(Edge e) {
    auto &list1 = adjacency[e.v1];
    auto &list2 = adjacency[e.v2];
    list1.push_back(e.v2);
    list2.push_back(e.v1);
    //num_edges ++;
}

void Graph::clear(unsigned v){
    if(v >= adjacency.size()) return;
    for(auto u : adjacency[v]){
        auto &list2 = adjacency[u];
        auto i2 = std::find(list2.begin(),list2.end(),v);
        if(i2 != list2.end()){
            list2.erase(i2);
            --n;
        }
    }
    adjacency[v].clear();
}

int main(int argc, char **argv)
{

     while(getline(cin,str))

    {

                if(str[0]=='v' || str[0]=='V')
                {
                    vsplit();

                }
                else if(str[0]=='e' || str[0]=='E')
                {

                    Esplit();


                }


    }

    return 0;
}

