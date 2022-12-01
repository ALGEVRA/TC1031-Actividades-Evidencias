#include "matriz.h"

template <class Vertex>
UMatrix_graph<Vertex>::UMatrix_graph(unsigned int c_size,
                                     std::optional<bool> c_direction)
    : size(c_size), direction(c_direction.value_or(true))
{
    next = 0;
    vertexes.resize(size);
    edges.resize(size);

    for (size_t i{}; i < size; ++i)
    {
        edges[i].resize(size, false);
        edges[i][i] = true;
    }
}

//Grado de complejidad O(1)
template <class Vertex>
int UMatrix_graph<Vertex>::get_next() const
{
    return next;
}

//Grado de complejidad O(1)
template <class Vertex>
unsigned int UMatrix_graph<Vertex>::get_size() const
{
    return size;
}
//Grado de complejidad O(1)
template <class Vertex>
bool UMatrix_graph<Vertex>::get_direction() const
{
    return direction;
}

//Grado de complejidad O(1)
template <class Vertex>
std::vector<Vertex> UMatrix_graph<Vertex>::get_vertexes() const
{
    return vertexes;
}

//Grado de complejidad O(n)
template <class Vertex>
std::set<Vertex> UMatrix_graph<Vertex>::get_neighbours(Vertex vertex) const
{
    std::set<Vertex> neighbours;

    for (size_t i{}; i < size; ++i)
        if (edges[vertex][i])
            neighbours.insert(i);

    return neighbours;
}

//Grado de complejidad O(n^2)
template <class ostream>
std::ostream &operator<<(std::ostream &os,
                         const std::shared_ptr<UMatrix_graph<ostream>> &graph)
{
    os << "Graph size: " << graph->get_size() << std::endl
       << std::endl;

    os << "Adjacent Matrix: " << std::endl;

    for (size_t i{}; i < graph->get_next(); ++i)
        os << graph->vertexes[i] << " ";

    os << std::endl
       << std::endl;

    os << "Edges: " << std::endl;

    for (size_t i{}; i < graph->get_next(); ++i)
    {
        for (size_t j{}; j < graph->get_next(); ++j)
            os << graph->edges[i][j] << " ";

        os << std::endl;
    }

    os << std::endl
       << "Adjacent list: " << std::endl;

    for (size_t i{}; i < graph->size; ++i)
    {
        os << graph->vertexes[i] << " -> ";

        for (size_t j{}; j < graph->size; ++j)
            if (graph->edges[i][j])
                os << graph->vertexes[j] << " ";

        os << std::endl;
    }

    return os;
}

//Grado de complejidad O(n)
template <class Vertex>
Vertex UMatrix_graph<Vertex>::index_of(Vertex vertex) const
{
    for (size_t i{}; i < size; ++i)
        if (vertexes[i] == vertex)
            return i;

    return -1;
}

//Grado de complejidad O(n)
template <class Vertex>
bool UMatrix_graph<Vertex>::is_edge(Vertex vertex1, Vertex vertex2) const
{
    return edges[vertex1][vertex2];
}

//Grado de complejidad O(n)
template <class Vertex>
bool UMatrix_graph<Vertex>::is_vertex(Vertex vertex) const
{
    return index_of(vertex) != -1;
}

//Grado de complejidad O(n^2)
template <class Vertex>
void UMatrix_graph<Vertex>::load_graph(std::fstream &input_file)
{
    int from, to;

    while (true)
    {
        input_file >> from >> to;

        if (!from && !to)
            break;

        add_edge(from, to);
    }
}

//Grado de complejidad O(n)
template <class Vertex>
void UMatrix_graph<Vertex>::add_edge(Vertex from_vertex, Vertex to_vertex)
{
    if (!is_vertex(from_vertex))
        add_vertex(from_vertex);

    if (!is_vertex(to_vertex))
        add_vertex(to_vertex);

    int index1 = index_of(from_vertex), index2 = index_of(to_vertex);
    edges[index1][index2] = true;

    if (!direction)
        edges[index2][index1] = true;
}

//Grado de complejidad O(n)
template <class Vertex>
void UMatrix_graph<Vertex>::remove_edge(Vertex from_vertex, Vertex to_vertex)
{
    if (!is_vertex(from_vertex) || !is_vertex(to_vertex))
        throw std::invalid_argument("Vertex not found");

    if (!is_edge(from_vertex, to_vertex))
        throw std::invalid_argument("Edge does not exist");

    edges[from_vertex][to_vertex] = false;

    if (!direction)
        edges[to_vertex][from_vertex] = false;
}

//Grado de complejidad O(n)
template <class Vertex>
void UMatrix_graph<Vertex>::add_vertex(Vertex vertex)
{
    if (is_vertex(vertex))
        throw std::invalid_argument("Vertex already in the graph");

    if (next == size)
        throw std::invalid_argument("Graph is full");

    vertexes[next] = vertex;
    ++next;
}

//Grado de complejidad O(n^2)
template <class Vertex>
void UMatrix_graph<Vertex>::remove_vertex(Vertex vertex)
{
    if (!is_vertex(vertex))
        throw std::invalid_argument("Vertex not found");

    for (size_t i{}; i < size; ++i)
    {
        edges[index_of(vertex)][i] = false;
        edges[i][index_of(vertex)] = false;
    }

    for (size_t i{index_of(vertex)}; i < size - 1; ++i)
        vertexes[i] = vertexes[i + 1];

    --next;
}

//Grado de complejidad O(n)
template <class Vertex>
bool UMatrix_graph<Vertex>::contains_vertex(Vertex vertex) const
{
    return is_vertex(vertex);
}

//Grado de complejidad O(n)
template <class Vertex>
bool UMatrix_graph<Vertex>::contains_edge(Vertex vertex1, Vertex vertex2) const
{
    return is_edge(vertex1, vertex2);
}

//Grado de complejidad O(n^2)
template <class Vertex>
std::set<Vertex> UMatrix_graph<Vertex>::dfs(const Vertex &start) const
{
    std::set<Vertex> visited;
    std::stack<Vertex> stack;

    stack.push(start);

    while (!stack.empty())
    {
        auto v = stack.top();
        stack.pop();

        if (visited.find(v) == visited.end())
        {
            visited.insert(v);
            std::set<Vertex> neighbors = get_neighbours(v);

            for (const auto &neightbor : neighbors)
                stack.push(neightbor);

        } 
    }     

    return visited;
}

//Grado de complejidad O(n^2)
template <class Vertex>
std::set<Vertex> UMatrix_graph<Vertex>::bfs(const Vertex &start) const
{
    std::set<Vertex> visited;
    std::queue<Vertex> queue;

    queue.push(start);

    while (!queue.empty())
    {
        Vertex v = queue.front();
        queue.pop();

        if (visited.find(v) == visited.end())
        {
            visited.insert(v);
            std::set<Vertex> neighbors = get_neighbours(v);

            for (const auto &neighbor : neighbors)
                queue.push(neighbor);
        } 
    }     

    return visited;
}
