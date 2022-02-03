#include "test.h"

void ConstructorTest()
{
    std::cerr << "Constructor test...\n";
    Collection<std::string> new_table;
    assert(new_table.GetSize() == DEF_N);

    new_table << DEF_T1;
    new_table << DEF_T2;
    //new_table.Print();

    Collection<std::string> copy_table(new_table);
    //copy_table.Print();
    assert(new_table == copy_table);

    std::cerr << "No errors for constructor class\n\n";
}

void AdditionTest()
{
    std::cerr << "Methods and operators test...\n";
    Collection<std::string> new_table;
    new_table.Add(DEF_T1);
    new_table.Add(DEF_T2);
    new_table.Add(DEF_T3);

    assert(new_table.GetSize() == DEF_N3);

    new_table.Add(DEF_T2);
    assert(new_table.GetSize() == DEF_N3);

    std::cerr << "No errors for add method\n";
}

void ClearTest()
{
    Collection<std::string> new_table;
    Collection<std::string> just_a_table;

    just_a_table.Add(DEF_T1);
    just_a_table.Add(DEF_T2);
    just_a_table.Add(DEF_T3);
    just_a_table.Clear();

    assert(new_table.GetSize() == DEF_N);
    assert(new_table.GetSize() == just_a_table.GetSize());
    std::cerr << "No errors for clear method\n";
}

void FindTest()
{

    Collection<std::string> new_table;
    new_table<<DEF_T1;
    assert(new_table[DEF_T1] == 1);
    assert(new_table[DEF_T2] == 0);
    std::cerr << "No errors for find method and operator\n";
}

void RemoveTest()
{
    Collection<std::string> new_table;
    new_table<<DEF_T1;
    new_table<<DEF_T2;
    new_table<<DEF_T3;
    //std::cout << "Before remove:\n";
    //new_table.Print();

    new_table.Remove(DEF_T2);
    //std::cout << "After remove:\n";
    //new_table.Print();
    assert(new_table.GetSize() == DEF_N2);
    new_table.Remove(DEF_T4);
    assert(new_table.GetSize() == DEF_N2);

    std::cerr << "No errors for remove method\n";
}

void WriteReadTest()
{
    Collection<std::string> table;
    table.SetName("Intresting_information");
    table<<DEF_T1;
    table<<DEF_T2;
    table<<DEF_T3;
    table<<DEF_T4;
    table.Export(PATH);

    Collection<std::string> new_table;
    new_table.Import(PATH);

    //table.PrintC();

    //new_table.PrintC();
    assert(table == new_table);
    std::cerr << "No errors for export and import methods\n";
}

void RehashTest()
{
    Collection<std::string> table;
    table<<DEF_T1;
    table<<DEF_T2;
    table<<DEF_T3;
    table<<DEF_T4;
    table<<DEF_T5;
    table<<DEF_T6;
    table<<DEF_T7;
    //table.Print();

    table<<DEF_T8;
    table<<DEF_T9;
    //table.Print();

    std::cerr << "No errors for rehash method\n";
}

void CreateTableTest()
{
    Collection<std::string> table;
    table<<DEF_T1;
    table<<DEF_T2;
    table<<DEF_T3;
    table<<DEF_T4;
    Collection<std::string> new_table;
    Collection<std::string> gen_table = table&&new_table;

    assert(gen_table == new_table);

    new_table << DEF_T1;
    new_table << DEF_T3;
    new_table << DEF_T5;
    Collection<std::string> create_table;
    create_table = new_table&&table;
    table.SetName("the_first");
    new_table.SetName("the_second");
    create_table.SetName("create_table");
    table.PrintC();
    new_table.PrintC();
    create_table.PrintC();

    std::cerr << "No errors for && operator method\n\n";
}

