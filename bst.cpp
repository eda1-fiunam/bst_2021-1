/*Copyright (C)
 * 2019 - eda1 dot fiunam @ yahoo dot com dot mx
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */


// para compilar:
//     g++ -Wall -std=c++99 -obst.out bst.cpp


#include <iostream>
// para cout, cin, y cerr

#include <fstream>
// para usar archivos

class Bst;


//----------------------------------------------------------------------
//  Class Item
//----------------------------------------------------------------------
struct Item
{
   int val = 0;
   // para simplificar hacemos que la 'info' sea pública

   Item();
   Item( int value );

   bool operator<( Item& rhs ) { return this->val < rhs.val; }
   // le enseñamos a C++ a comparar objetos Item

   bool operator==( Item& rhs ) { return this->val == rhs.val; }
   // le enseñamos a C++ a comparar objetos Item

   friend std::ostream& operator<<( std::ostream& os, const Item& item );
   // le enseñamos a C++ a imprimir objetos Item
};

Item::Item( int value ) : val{ value }
{
   // nada
}

// constructor sin argumentos. Lo podemos usar para crear arreglos de objetos.
Item::Item() : val{ 0 }
{
   // nada
}

   std::ostream& // devolver una referencia a flujo permite encadenar comandos
operator<<( std::ostream& os, const Item& item )
{
   os << item.val;
   // permitimos que el objeto llamador formatee la salida, por eso no ponemos
   // espacios en blanco, saltos de línea, etc.

   return os;
}




//----------------------------------------------------------------------
//  Class Node
//----------------------------------------------------------------------
struct Node
{
   Item item;
   Node* left = nullptr;
   Node* right = nullptr;
};


//----------------------------------------------------------------------
//  Class Bst
//----------------------------------------------------------------------
class Bst
{
private:
   Node* root = nullptr;
   size_t len = 0L;

   Node* new_node(  Item& item );
   Node* insert(    Node* node, Item& item );
   Node* find(      Node* node, Item& item );
   void  clear_all( Node* node );
   void  inorder(   Node* node, void (*pfun)( Item& ) );
   void  preorder(  Node* node, void (*pfun)( Item& ) );
   void  postorder( Node* node, void (*pfun)( Item& ) );

public:
   enum class Dir { INORDER, PREORDER, POSTORDER };
   // la vamos a usar en la función Traverse()

   Bst();
   ~Bst();

   bool Insert( Item item );
   bool Remove( Item& item );
   bool Find( Item& item );
   void Traverse( Bst::Dir dir, void (*pfun)( Item& item ) );
   void Delete_all();

   size_t Len() { return this->len; }

   Node* Get_root();
   // devuelve la referencia al nodo raíz
};


//----------------------------------------------------------------------
//              Recursive and private functions
//----------------------------------------------------------------------

Node* Bst::new_node( Item& item )
{
   Node* n = new( Node );
   // crea un nuevo objeto en el heap

   // inicializa al nuevo objeto

   return n;
}

Node* Bst::insert( Node* node, Item& item )
{
}

Node* Bst::find( Node* node, Item& item )
{
}

void Bst::clear_all( Node* node )
{

   // borra todos los nodos (de forma recursiva)

   delete node;
   // borra el nodo raíz del sub-árbol
}

void Bst::inorder( Node* node, void (*visit)( Item& item ) )
{
}

void Bst::preorder( Node* node, void (*visit)( Item& item ) )
{
}

void Bst::postorder( Node* node, void (*visit)( Item& item ) )
{
}

//----------------------------------------------------------------------
//                  Interfaz implementation
//----------------------------------------------------------------------
Bst::Bst()
{
   // nada
}

Bst::~Bst()
{
   clear_all( this->root );
   // llamamos a clear_all
}

void Bst::Delete_all()
{
   // llamamos a clear_all

   // reiniciamos los atributos de la clase
}


bool Bst::Insert( Item item )
{
}

bool Bst::Find( Item& item )
{
}

// recorremos el árbol en la dirección dada por dir. En cada nodo visitado aplicamos visit
void Bst::Traverse( Bst::Dir dir, void (*visit)( Item& item ) )
{

   if( this->root != nullptr ){
      switch( dir ){
         case Dir::INORDER:   inorder(   this->root, visit ); break;
         case Dir::PREORDER:  preorder(  this->root, visit ); break;
         case Dir::POSTORDER: postorder( this->root, visit ); break;
      }
   }
}

Node* Bst::Get_root()
{
   return this->root;
}


//----------------------------------------------------------------------
//  Para dibujar el árbol
//----------------------------------------------------------------------

#include <string>
#include <vector>

struct Vertex
{
   int data;
   std::string name;
   int left;
   int right;

   Vertex( int data, std::string name, int left, int right ) :
      data{ data }, name{ name }, left{ left }, right{ right }
   {
      // nada
   }
};

void draw_bst_rec( Node* node, std::vector<Vertex>& list )
{
   if( node == nullptr ) return;

   draw_bst_rec( node->left, list );

   list.push_back( Vertex(
         node->item.val,
         "node_" + std::to_string( node->item.val ),
         node->left ? node->left->item.val : -1,
         node->right ? node->right->item.val : -1 )
      );

   draw_bst_rec( node->right, list );
}

void draw_bst( Bst& tree )
{
   Node* root = tree.Get_root();

   std::vector<Vertex> list;

   draw_bst_rec( root, list );
   // genera la lista de vértices

   std::string file_name = "my_bst.dot";

   std::fstream file;
   file.open( file_name, std::ios::out );

   if( not file ){
      std::cerr << "Error creando al archivo: " << file_name << std::endl;
      return;
   }

   file << "digraph g {\n" "node [shape=record];\n";


   // crea las etiquetas:

   for( auto& n : list ){
      file << n.name + "[label=\"<f0>|<f1>";
      file << std::to_string( n.data ) + "|<f2>\"];\n";
   }


   // crea las relaciones:

   for( auto& n : list ){
      if( n.left != -1 ){
         file << "\"" + n.name << "\":f0 -> ";
         file << "\"node_" << n.left << "\":f1;\n";
      }

      if( n.right != -1 ){
         file << "\"" + n.name << "\":f2 -> ";
         file << "\"node_" << n.right << "\":f1;\n";
      }
   }

   file << "}\n";
}


// esta es la función que vamos a usar en cada 'visita'
void print( Item& item )
{
   std::cout << item.val << std::endl;

   // ¿funciona?
   // std::cout << item << std::endl;
}



//----------------------------------------------------------------------
//  Driver program
//----------------------------------------------------------------------
int main()
{
   Bst arbol;

   //  int datos[] = { 30, 15, 45, 7, 22, 37, 52, 4, 10, 18, 26, 34, 40 };
   int datos[] = { 100, 20, 200, 10, 30, 150, 300 };

   for( int x : datos ){ arbol.Insert( Item( x ) ); }

   // muevan la siguiente línea conforme vayan avanzando con la escritura de las funciones
#if 0
   std::cout << "\n=== INORDER ===\n";
   arbol.Traverse( Bst::Dir::INORDER, print );

   std::cout << "\n=== PREORDER ===\n";
   arbol.Traverse(
         Bst::Dir::PREORDER,
         [](Item& item)
         {
            std::cout << item << std::endl;
         } );

   std::cout << "\n=== POSTORDER ===\n";
   arbol.Traverse( Bst::Dir::POSTORDER, [](Item& item){ std::cout << item << std::endl; } );


   int val;
   std::cout << "Valor a buscar\n? ";
   std::cin >> val;

   Item item( val );

   std::cout << "El valor " << val << (arbol.Find( item ) == true ? " sí " : " no ") << "se encuentra\n";
#endif

   // ¿y dónde está el destructor?


   //draw_bst( arbol );
   // para usar esta función debes tener instalado el programa "dot", el cual
   // viene en el paquete graphviz:
   //
   //       $ sudo apt install graphviz
   //
   // Esta función genera un archivo my_bst.dot el cual tienes que renderizar
   // con el programa "dot". Para obtener una imagen del grafo en formato png:
   //
   //       $ dot -Tpng my_bst.dot -omy_bst.png
   //
   // Pero si la quisieras como svg (más pequeña (en tamaño) y funcional):
   //
   //       $ dot -Tsvg my_bst.dot -omy_bst.svg
   //
}
