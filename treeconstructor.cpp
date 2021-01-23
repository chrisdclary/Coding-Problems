#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <unordered_map>

template< class T >
class optional
{

  T content;
  bool hasValue = false;

  public:

    optional<T>& operator = ( T const &obj ) {
      content = obj;
      hasValue = true;
      return *this;
    }
    
    optional() = default;

    optional( T const &obj ) {
      content = obj;
      hasValue = true;
    }

    T value() {
      return content;
    }

    bool has_value() {
      return hasValue;
    }

    void reset() {
      hasValue = false;
    }
};

// Convert strings to edges, throw an error if given an invalid string
std::pair<int, int> strToEdge(std::string& input)
{
  optional<size_t> commaPos = input.find(',');
  // Pair must begin with '(', end with ')', and contain a comma
  if(input.empty() || input.front() != '(' || input.back() != ')' || !commaPos.has_value())
    throw std::runtime_error("Invalid input: " + input);
  
  std::pair<int, int> edge;
  edge.first = std::stoi(input.substr(1, commaPos.value() - 1));
  edge.second = std::stoi(input.substr(commaPos.value() + 1,input.length() - commaPos.value() - 1));

  return edge;
  
}

struct Node {
  optional<int> parent;
  std::vector<int> children;

  bool visited = false;
};

//  Start at root node, use DFS and mark all connected nodes
void visitNodes(Node& current, std::unordered_map<int, Node>& tree)
{
  current.visited = true;
  for (auto child : current.children)
    visitNodes(tree[child], tree);

}

std::string TreeConstructor(std::string strArr[], int arrLength) 
{
  std::unordered_map<int, Node> tree;
    
  // Build the tree out of the strings
  for (int i = 0; i < arrLength; i++){
    
    // First is the child, second is the parent
    auto edge = strToEdge(strArr[i]);

    Node& parentNode = tree[edge.second];
    parentNode.children.push_back(edge.first);
    if (parentNode.children.size() > 2)
      return "false";
    

    Node& childNode = tree[edge.first];
    if (childNode.parent.has_value())
      return "false";
    childNode.parent = edge.second;

  }


  // Find the root node, return false if there is more than one
  optional<int> root;
  for (auto& [v, n] : tree){
    if(!n.parent.has_value()){
        if(root.has_value())
            return "false";
        root = v;
    }
        
  }

  // If there is no root node, there is a cycle and the tree is invalid
  if (!root.has_value())
    return "false";

  // Mark all nodes connected to root as visited
  visitNodes(tree[root.value()], tree);
  
  // If any nodes are unmarked, the tree is not connected
  for (auto& [v, n] : tree){
    if(!n.visited)
      return "false";
  }

  // code goes here  
  return "true";

}

int main(void) 
{ 
   
  // keep this function call here
  std::string A[] = coderbyteInternalStdinFunction(stdin);
  int arrLength = sizeof(A) / sizeof(*A);
  std::cout << TreeConstructor(A, arrLength);
  return 0;
    
}