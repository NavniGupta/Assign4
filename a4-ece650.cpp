#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
#include "minisat/core/Solver.h"
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
vector<unsigned int> outputE_copy;
vector<unsigned int> outputV;

struct Graph{

    AdjacencyList adjacency;

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



void Vertex_Cover(Graph &graph)
{
Graph &graph_input = graph;
VertexVec &C = *new VertexVec();


    unsigned int high = graph_input.adjacency.size();
    unsigned int low = 0;
    unsigned int k = 0;
    bool res;
    k=(low+high)/2;
    while (low <= high)
    {
         std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());


        std::vector<std::vector<Minisat::Lit>> nk_matrix(graph_input.adjacency.size());
        for (unsigned int i = 0; i < graph_input.adjacency.size(); i++)
            for (unsigned int j = 0; j < k; j++) {
                Minisat::Lit l = Minisat::mkLit(solver->newVar());
                nk_matrix[i].push_back(l);
            }
        // first condition
        for (unsigned int i = 0; i < k; i++) {
            Minisat::vec<Minisat::Lit> save_literal;
            for (unsigned int j = 0; j < graph_input.adjacency.size(); j++) {
                save_literal.push(nk_matrix[j][i]);
            }
            solver->addClause(save_literal);
        }

// second condition
        for (unsigned int m = 0; m < graph_input.adjacency.size(); m++)
            for (unsigned int p = 0; p < k; p++)
                for (unsigned int q = p + 1; q < k; q++) {
                    solver->addClause(~nk_matrix[m][p], ~nk_matrix[m][q]);
                }
//third condition
        for (unsigned int m = 0; m < k; m++)
            for (unsigned int p = 0; p < graph_input.adjacency.size(); p++)
                for (unsigned int q = p + 1; q < graph_input.adjacency.size(); q++) {
                    solver->addClause(~nk_matrix[p][m], ~nk_matrix[q][m]);
                }


//forth condition
        for(unsigned v1 = 0 ; v1 < graph_input.adjacency.size(); ++v1) {
            for (auto v2 : graph_input.adjacency[v1]) {
                if(v2 < v1) continue;
                Minisat::vec<Minisat::Lit> edge_lit;
                for (unsigned int w = 0; w < k; w++) {
                    edge_lit.push(nk_matrix[v1][w]);
                    edge_lit.push(nk_matrix[v2][w]);
                }

                solver->addClause(edge_lit);
            }
        }
        res = solver->solve();
        if (res )
        {   C.clear();
            for ( unsigned int i = 0; i < graph_input.adjacency.size(); i++)
                for ( unsigned int j =0; j < k; j++)

                    if ( Minisat::toInt(solver->modelValue(nk_matrix[i][j])) == 0)
                    {
                        C.push_back(i);
                    }

            high=k-1;
        }
        else {
            solver.reset(new Minisat::Solver());
            low=k+1;
        }
        k=(low+high)/2;
    }
    std::sort( C.begin(), C.end(), std::less<int>());
    for (unsigned j=0; j < C.size(); j++){
            std::cout<<C[j];
            if(j + 1 != C.size()){
                std::cout<<' ';
            }
        }
        std::cout<<std::endl;



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

 Vertex_Cover(graph_input);


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
