
/* 
Nombre: main.cpp
Autor: Francisco Alejandro Velázquez Ledesma
 */

#include <iostream>
#include <fstream>
#include <memory>
#include "matriz.cpp"

using namespace std;

int main() {
    fstream input_file("grafica.txt", ios::in);
    if (!input_file) {
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    int first_line;
    input_file >> first_line;

    shared_ptr<UMatrix_graph<string>> graph =
        make_shared<UMatrix_graph<string>>(first_line);

    graph->add_edge("A", "B");
    graph->add_edge("A", "C");
    graph->add_edge("A", "D");
    graph->add_edge("A", "E");
    graph->add_edge("B", "C");
    graph->add_edge("B", "E");
    graph->add_edge("C", "D");
    graph->add_edge("C", "E");
    graph->add_edge("C", "A");
    graph->add_edge("D", "A");
    graph->add_edge("D", "F");
    graph->add_edge("D", "C");
    graph->add_edge("D", "B");
    graph->add_edge("E", "A");
    graph->add_edge("E", "B");
    graph->add_edge("E", "C");
    graph->add_edge("E", "D");
    graph->add_edge("E", "F");
    graph->add_edge("F", "D");
    graph->add_edge("F", "E");

    cout << graph << endl;
}
