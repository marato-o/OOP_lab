#ifndef COLLECTION_H
#define COLLECTION_H

#include "string"
#include "iostream"
#include "fstream"
#include "algorithm"
#include "functional"

#include "QListWidget"


#define DEF_SIZE 6
#define DEF_RESIZE 0.75

template <typename Type>
class Collection
{
public:
    Collection();
    Collection(const Collection&);
    ~Collection();

    //Hash
    int HashFunc(const Type&) const;
    void Rehash();


    //Methods
    void Clear();
    void Add(const Type&);
    void Remove(const Type&);
    bool Find(const Type&) const;
    int GetSize() const;
    void CopyCol(const Collection&);

    //Operators
    void operator << (const Type&);
    bool operator [] (const Type&) const;
    bool operator == (const Collection&) const;
    Collection operator && (const Collection&) const;

    //Reading and writing
    void PrintC() const;
    void Print(QListWidget *) const;
    void Export(const std::string& path) const;
    void Import(const std::string& path);

    //for widgets
    std::string GetName();
    void SetName(std::string new_name);

private:
    struct Node
    {
        Type value;
        Node *next;
        Node() = default;
        Node(const Type& new_value);
    };
    Node** arr;
    int size;
    int table_size = DEF_SIZE;
    std::hash<Type> hasher;
    std::string name;
};

// REALISATION

// THE CONSTRUCTORS
template<typename Type> Collection<Type>::Node::Node(const Type& new_value)
{
    value = new_value; 
    next = nullptr;
}

template<typename Type> Collection<Type>::Collection()
{
    arr = new Node* [table_size];
    size = 0;
    name = "Just_a_table";
    for (int i = 0; i < table_size; i++)
        arr[i] = nullptr;
}

template<typename Type> Collection<Type>::Collection(const Collection& cop)
{
    name = "Coppy_of_"+cop.name;
    table_size = cop.table_size;
    arr = new Node* [table_size];
    size = cop.size;
    Node* new_node;
    Node* cop_curr;
    Node* additional;

    for (int i = 0; i < table_size; i++){
        arr[i] = nullptr;
        cop_curr = cop.arr[i];
        while (cop_curr){
            new_node = new Node(cop_curr->value);
            new_node->next = nullptr;

            if (arr[i] == nullptr){
                arr[i] = new_node;
                additional = new_node;
            }
            else{
                additional->next = new_node;
                additional = additional->next;
            }
            cop_curr = cop_curr->next;
        }
    }
}

template<typename Type> Collection<Type>::~Collection()
{
    Clear();
}
// END OF THE CONSTRUCTORS


// THE HASH
template<typename Type> int Collection<Type>::HashFunc(const Type& value) const
{
    int hash = hasher(value);
    hash = hash%table_size;
    return hash;
}

template<typename Type> void Collection<Type>::Rehash()
{
    table_size *= 2;
    Node** new_arr = new Node* [table_size];
    for (int i = 0; i < table_size; i++)
        new_arr[i] = nullptr;
    Node* curr;

    /*
    for (size_t i = 0; i < table_size/2; i++){
        curr = arr[i];
        while (curr){
            if (curr == nullptr) break;
            int h = HashFunc(curr->value);
            if (!new_arr[h]){
                new_arr[h] = curr;
                new_arr[h]->next = nullptr;
                ++size;
            }
            else{
                Node* new_curr = new_arr[h];
                while(new_curr->next != nullptr)
                    new_curr = new_curr->next;
                new_curr->next = curr;
                (new_curr->next)->next = nullptr;
                ++size;
            }
            curr = curr->next;
        }
    }
    */


    for (int i = 0; i < table_size/2; i++){
        curr = arr[i];
        while (curr){
            if (curr == nullptr) break;
            int h = HashFunc(curr->value);
            Node* new_curr = curr;
            curr = curr->next;
            new_curr->next = new_arr[h];
            new_arr[h] = new_curr;
        }
    }
    delete [] arr;
    arr = new_arr;
}

// END OF THE HASH METHODS



// THE METHODS
template<typename Type> void Collection<Type>::Clear()
{
    Node* curr;
    for (int i = 0; i < table_size; i++)
    {
        while (arr[i]){
            curr = arr[i];
            arr[i] = arr[i]->next;
            delete (curr);
            --size;
        }
    }
    if (size != 0) std::cerr << "Errors with the clear method\n";
}

template<typename Type> void Collection<Type>::Add(const Type &new_value)
{
    if (size + 1 > DEF_RESIZE*table_size) Rehash(); // увеличививаем размер таблицы и перезаписываем её
    int h = HashFunc(new_value); // запоминаем хеш нового выражения
    if (!arr[h]){ // если цепочки с таким хешем нет, выделяем память и добавляем элемент в начало цепочки
        Node* newNode = new Node(new_value);
        arr[h] = newNode;
        ++size;
    }
    else
    {
        Node* curr = arr[h]; // ставим указатель на начало цепочки
        bool found = false;
        if (arr[h]->value == new_value) found = true;
        else{
            for (; curr->next != nullptr && !found; curr = curr->next){
                if ((curr->next)->value == new_value) found = true;
            } // цикл завершается, когда указатель оказывается на последнем элементе цепочки или когда находим дублирование данных
        }
        if (!found){ // если в цепочке не нашелся такой элемент, который мы хотим добавить
            Node* newNode = new Node(new_value);
            curr->next = newNode; // последний элемент в цепочке теперь указывает на новый элемент
            ++size;
        }
    }
}

template<typename Type> void Collection<Type>::Remove(const Type& value)
{
    int h = HashFunc(value);
    if (arr[h])
    {
        Node* curr = arr[h];
        bool ok = true;

        if (curr->value == value) ok = false;

        while (curr->next && ok){
            if (curr->next->value == value) ok = false;
            curr = curr->next;
        }
        if (!ok)
        {
            if (arr[h]->value == value){
                arr[h] = arr[h]->next;
                delete (curr);
            }
            else{
                Node* temp = curr->next;
                if (temp->next) curr->next = temp->next;
                else curr->next = nullptr;
                delete (temp);
            }
            --size;
        }

    }
}

template<typename Type> bool Collection<Type>::Find(const Type& value) const
{
    int h = HashFunc(value);
    if (!arr[h]) return 0;
    Node* curr = arr[h];
    while (curr){
        if (curr->value == value) return 1;
        curr = curr->next;
    }
    return 0;
}

template<typename Type> int Collection<Type>::GetSize() const
{
    return size;
}

template<typename Type> void Collection<Type>::CopyCol(const Collection& cop)
{
    name = cop.name;
    table_size = cop.table_size;
    arr = new Node* [table_size];
    size = cop.size;
    Node* new_node;
    Node* cop_curr;
    Node* additional;

    for (int i = 0; i < table_size; i++){
        arr[i] = nullptr;
        cop_curr = cop.arr[i];
        while (cop_curr){
            new_node = new Node(cop_curr->value);
            new_node->next = nullptr;

            if (arr[i] == nullptr){
                arr[i] = new_node;
                additional = new_node;
            }
            else{
                additional->next = new_node;
                additional = additional->next;
            }
            cop_curr = cop_curr->next;
        }
    }
}
// END OF THE METHODS


// THE OPERATORS
template<typename Type> void Collection<Type>::operator << (const Type &T)
{
    Add(T);
}

template<typename Type> bool Collection<Type>::operator [] (const Type &T) const
{
    return Find(T);
}

template<typename Type> bool Collection<Type>::operator == (const Collection &cop) const
{
    if (size != cop.size) return 0;
    Node* curr;
    Node* cop_Node;
    bool ok;
    for (int i = 0; i < table_size; i++){
        curr = arr[i];
        if ((curr && !cop.arr[i])||(!curr && cop.arr[i])) return 0;
        while (curr){
            cop_Node = cop.arr[i];
            ok = 0;
            while (cop_Node){
                if (curr->value == cop_Node->value) ok = 1;
                cop_Node = cop_Node->next;
            }
            if (!ok) return 0;
            curr = curr->next;
        }
    }
    return 1;
}

template<typename Type> Collection<Type> Collection<Type>::operator && (const Collection &cop) const
{
    Collection result;

    if (cop.size == 0 || size == 0) return result;

    Node* curr;
    for (int i = 0; i < this->table_size; i++){
        curr = this->arr[i];
        while (curr){
            if (cop[curr->value]){
                result.Add(curr->value);
            }
            curr = curr->next;
        }
    }

    /*
    else{
        for (int i = 0; i < cop.table_size; i++){
            curr = cop.arr[i];
            while (curr){
                if (this->Find(curr->value)){
                    result << curr->value;
                    ++result.size;
                }
                curr = curr->next;
            }
        }
    }
    */

    return result;
}
// END OF THE OPERATORS


// THE READING AND WRITING METHODS
template<typename Type> void Collection<Type>::PrintC() const
{
    std::cout<<"Collection: "<< name <<"\n";
    std::cout<<"brackets = " << table_size << "\n";
    std::cout<<"amount of elements = " << size << "\n";
    for (int i = 0; i < table_size; i++){
        std::cout << i << ": ";
        Node* curr = arr[i];
        for (curr; curr != nullptr; curr = curr->next)
            std::cout <<"'"<< curr->value << "' ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

template<typename Type> void Collection<Type>::Print(QListWidget *list) const
{
    for (int i = 0; i < table_size; i++){
        Node* curr = arr[i];
        for (curr; curr != nullptr; curr = curr->next)
            list->addItem(QString::fromStdString(curr->value));
    }
}

template<typename Type> void Collection<Type>::Export(const std::string &path) const
{
    std::ofstream outputFile(path);
    outputFile << this->name << std::endl;
    outputFile << this->size << std::endl;
    Node *curr;
    for (int i = 0; i < table_size; i++)
    {
        curr = arr[i];
        while (curr){
            outputFile << curr->value << std::endl;
            curr = curr->next;
        }
    }
    outputFile.close();
}

template<typename Type> void Collection<Type>::Import(const std::string &path)
{
    this->Clear();
    std::ifstream inputFile(path);
    std::string text;
    int size = 0;
    if (!inputFile.eof())
    {
        inputFile >> name;
        inputFile >> size;
    }
    while (!inputFile.eof() && size > 0)
    {
        inputFile >> text;
        this->Add(text);
        --size;
    }
    if (size != 0)
        std::cerr<< "Error with the import process" << std::endl;
    inputFile.close();
}
// END OF THE READING AND WRITING METHODS

// FOR WIDGETS
template<typename Type> std::string Collection<Type>::GetName()
{
    return name;
}

template<typename Type> void Collection<Type>::SetName(std::string new_name)
{
    name = new_name;
}


#endif // COLLECTION_H
