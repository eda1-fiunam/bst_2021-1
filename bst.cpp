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

// esta es la función que vamos a usar en cada 'visita'
void print( Item& item )
{
   std::cout << item.val << std::endl;

   // ¿funciona?:
   // std::cout << item << std::endl;
}

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

}
