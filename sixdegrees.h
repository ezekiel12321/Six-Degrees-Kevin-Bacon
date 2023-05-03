#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <stdexcept>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <tuple>
#include <queue>
#include <unordered_map>
#include <set>
#include <unordered_set>

using namespace std;

class Node{
	public:
		string Movie;
		string Actor;
		Node(string act, string mov){
			Actor = act;
			Movie = mov;
		}
		// taken from https://cplusplus.com/forum/general/145841/
		bool operator<(const Node& a) {
    	return std::make_pair(Movie,Actor) < std::make_pair(a.Movie,a.Actor);
		}	
};


class Graph{
	public:
		unordered_map<string, vector<Node*>> m;

		Graph(){

		}
		

		void insert(vector<Node*> vec){
			vector<Node*> copy;
			copy = vec;
			for(int x = 0; x < copy.size(); x++){
				Node* front = copy.front();
				string front_string = front->Actor;
				//cout << "front string is " + front_string <<endl;
				copy.erase(copy.begin());
				
				if(!m.count(front_string)){
					vector<Node*> new_vec;
					m[front_string] = new_vec;
					m[front_string].insert(m[front_string].end(), copy.begin(), copy.end());
					//cout << "debug print";
					//debug_print(m[front_string]);
				}
				else{
					vector<Node*> new_vec;
					new_vec = m[front_string];
					m[front_string].insert(m[front_string].end(), copy.begin(), copy.end());
					
				}
				copy.push_back(front);
				

			}
			

		}
		void debug_print(vector<Node*> vec){
		
		
			for(Node* v : vec){
				cout << v->Actor + " ";
			}
			cout << endl;
			
		}

		string retrace_path(string source, string destination){

			if(!m.count(source)){
				return "Not present";
			}
			if(source == destination){
				return source;
			}
			unordered_map<Node*, Node*> predecessor;
			Node* final_dest;
			string final_str = "";
			if(bfs(source, destination, &predecessor, &final_dest) == false){
				return "Not present";
			}
			
			//cout << "final destination is" + final_dest->Actor <<endl;
			stack<string> movies;
			stack<string> actors;
			while(predecessor.count(final_dest)){
				//cout << "final dest is " + final_dest->Actor << endl;;
				actors.push(final_dest->Actor);
				movies.push(final_dest->Movie);
				final_dest = predecessor[final_dest];

			}
			final_str += source;
			while(!movies.empty() && !actors.empty()){
				//cout << "Hopefully its saved" << endl;
				string mov = movies.top();
				movies.pop();
				string act = actors.top();
				actors.pop();

				string fixed_mov = " -(" + mov + ")- ";
				final_str = final_str + fixed_mov + act;
			}
			return final_str;

		}

		
		bool bfs(string source, string destination, unordered_map<Node*, Node*> *predecessor, Node** final_dest){
			unordered_map<Node*, bool> visited;
			queue<Node*> q;
			vector<Node*> starting_vec = m[source];
			Node* node = new Node(source, "999999");
			q.push(node);
			/*

			for(int x = 0; x < m[source].size(); x++){
				q.push(m[source][x]);
				//cout << "starting vec " + to_string(x) + " is " + starting_vec[x]->Actor <<endl;
			}
			*/
			while(!q.empty()){
				Node* top = q.front();
				q.pop();
				for(Node* x : m[top->Actor]){
					//cout << "node is " + x->Actor << endl;
					if(!visited.count(x)){
						//cout << "hope we run this" << endl;
						q.push(x);
						visited[x] = true;
						(*predecessor)[x] = top;
						if(x->Actor == destination){
							*final_dest = x;
							return true;
						}
					}

				}
				
			}
			return false;		
		}
		
		
		

	


};


/*

class Actor{
	public:
		string name;
		vector<Movie> movie;
		Node(string name_insert, Movie mov){
			name = name_insert;
			movie.push_back(mov);
		}
		void add_movie(Movie mov){
			movie.push_back(mov);
		}
};

class Movie{
	public:
		string name;
		vector<Actor> actor;
		Node(string movie_name){
			movie = movie_name;
			actor = name;
		}
		void add_actor(Actor act){
			actor.push_back(act);
		}
	
	
};


class LinkedList{
	public: 
		Node* head;

		void insert(string actor, string movie){
			Node* node = new Node(actor);
			node->movie = movie;
			head->next = node;
			head = node;
		}
		

}

void insert(string actor, string movie, string actor2){
			if(!m.count(actor)){
				vector<Node*> vec;
				m[actor] = vec;
				Node node_to_add = new Node(actor2, movie);
				vec.push_back(node_to_add);
			}
			else{
				vector<Node*> vec = m[actor];
				Node node_to_add = new Node(actor2, movie);
				vec.push_back(node_to_add);
			}
			
		}
*/