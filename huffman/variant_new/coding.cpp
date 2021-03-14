#include "main.h"
using namespace std;

struct Coding::Impl {
  Impl();

  void Print_tree(Node*, unsigned);
  void BuildCodeTable(Node*);
  void PrintTable();
  void readConfig(const char*);
  po::variables_map config;

  void codding();
  void writeFile();
  vector<bool> code;
  map<char, vector<bool>> codeTabl;

  list<Node*> list_pNode;  //Список указателей на узлы нашего дерева
  map<char, int> m;  //Главная map куда складываем символы
  vector<char> codding_file;  //Закодированный файл
  long lenth_in;
  long lenth_out = 0;
};

Coding::Impl::Impl() {}
Coding::Coding() : _d{make_unique<Impl>()} {
  cout << "Codding_constructor" << endl;
  _d->readConfig("../../config.ini");
  _d->codding();
  _d->writeFile();
}
Coding::~Coding() {}

Node::Node() {
  left_branch = nullptr;
  right_branch = nullptr;
}
Node::Node(Node* left, Node* right) {
  left_branch = left;
  right_branch = right;
  num_in_node = left->num_in_node + right->num_in_node;
}

void Coding::Impl::readConfig(const char* conf_file) {
  po::options_description coding("coding");
  coding.add_options()("coding.input_path,in", po::value<std::string>(),
                       "input_path")(
      "coding.output_path,out", po::value<std::string>(), "output path coding")(
      "coding.input_name,iname", po::value<std::string>(), "input_name coding")(
      "coding.output_name,oname", po::value<std::string>(),
      "output_name coding")("coding.print_Character_frequency_table,print1",
                            po::value<bool>(),
                            "print_Character_frequency_table")(
      "coding.print_tree", po::value<bool>(), "print_tree")(
      "coding.print_CODDING_TABL,print2", po::value<bool>(),
      "print_CODDING_TABL");
  po::options_description desc("Allowed options");
  desc.add(coding);
  try {
    po::parsed_options parsed = po::parse_config_file<char>(
        conf_file, desc,
        true);  //флаг true разрешает незарегистрированные опции !
    po::store(parsed, config);
  } catch (const po::reading_file& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  po::notify(config);
  std::cout << config["coding.input_path"].as<std::string>() << std::endl;
  std::cout << config["coding.input_name"].as<std::string>() << std::endl;
  std::cout << config["coding.output_path"].as<std::string>() << std::endl;
  std::cout << config["coding.output_name"].as<std::string>() << std::endl;
}

void Coding::Impl::Print_tree(Node* root, unsigned k = 0) {
  if (root != nullptr) {
    Print_tree(root->left_branch, k + 4);
    for (unsigned i = 0; i < k; i++) {
      cout << "  ";
    }
    if (root->char_in_node)
      cout << root->num_in_node << " (" << root->char_in_node << ") " << endl;
    else
      cout << root->num_in_node << endl;
    Print_tree(root->right_branch, k + 3);
  }
}

//Строим таблицу кодирования
void Coding::Impl::BuildCodeTable(Node* root) {
  if (root->left_branch != nullptr) {
    code.push_back(0);
    BuildCodeTable(root->left_branch);
  }  // Рекурсия
  if (root->right_branch != nullptr) {
    code.push_back(1);
    BuildCodeTable(root->right_branch);
  }

  if (root->left_branch == nullptr && root->right_branch == nullptr)
    codeTabl[root->char_in_node] = code;  //лист

  code.pop_back();  // один символ из vector убираем - фактически встаем на
                    // предыдущий элемент
}

void Coding::Impl::PrintTable() {
  cout << endl
       << "--------------------    CODDING TABL   ------------------------- "
       << endl;
  int l = 1;
  for (auto i : codeTabl) {
    cout << l << "\t" << i.first << " - ";
    auto itboolvector = i.second.begin();
    for (itboolvector = i.second.begin(); itboolvector != i.second.end();
         ++itboolvector) {
      cout << *itboolvector;
    }
    cout << endl;
    ++l;
  }
}

void Coding::Impl::codding() {
  const std::chrono::time_point<std::chrono::steady_clock> start =
      std::chrono::steady_clock::now();

  cout << "Coding file started" << endl;
  cout << "read file: "
       << config["coding.input_path"].as<std::string>() +
              config["coding.input_name"].as<std::string>()
       << endl;

  ifstream in(config["coding.input_path"].as<std::string>() +
                  config["coding.input_name"].as<std::string>(),
              ios::in | ios::binary);
  //  string str{};
  //  while (!in.eof()) {
  //    char c = in.get();
  //    str.append(&c);
  //  }
  //  stringstream ss{str};

  const std::chrono::time_point<std::chrono::steady_clock> stop_read =
      std::chrono::steady_clock::now();

  cout << "Time_read - "
       << std::chrono::duration_cast<std::chrono::milliseconds>(stop_read -
                                                                start)
              .count()
       << " milliseconds" << endl
       << endl;

  cout << "First scan of the file: " +
              config["coding.input_name"].as<std::string>()
       << endl;
  while (!in.eof()) {
    char c = in.get();
    //Записывааем символ в map и увеличиваем на 1 число вхождений
    m[c]++;
  }

  if (config["coding.print_Character_frequency_table"].as<bool>()) {
    // Выводим таблицу частоты символов
    cout << " ------------------  Character frequency table  --------------- "
         << endl;
    int k = 1;
    for (auto i = m.begin(); i != m.end(); ++i) {
      cout << k << "\t" << i->first << " - " << i->second << endl;
      ++k;
    }
  }

  cout << "Creating a binary tree" << endl;
  //Проходим по map и для каждого символа создаем узел дерева node и
  //помещаем его в list
  int char_all{0};
  map<char, int>::iterator itmap;
  for (itmap = m.begin(); itmap != m.end(); ++itmap) {
    Node* p = new Node;
    p->char_in_node = itmap->first;
    p->num_in_node = itmap->second;
    char_all += itmap->second;
    list_pNode.push_back(p);
  }
  cout << "char_all: " << char_all << endl;

  //Работаем с деревом
  while (list_pNode.size() != 1) {  // пока не останется 1
    //  list_pNode.sort(execution::par, Compare_Node());
    list_pNode.sort(Compare_Node());
    Node* left_son = list_pNode.front();
    list_pNode.pop_front();
    Node* right_son = list_pNode.front();
    list_pNode.pop_front();
    Node* parrent = new Node(left_son, right_son);
    list_pNode.push_back(parrent);
  }
  // на выходе цикла остался 1 элемент - он-же корень
  Node* root = list_pNode.front();

  lenth_in = root->num_in_node;
  cout << "sourse file - " << lenth_in << " bytes" << endl;

  if (config["coding.print_tree"].as<bool>()) {
    //Печать дерева
    cout << endl
         << "--------------------    BINARE TREE    ------------------------- "
         << endl;
    Print_tree(root);
  }

  // Ассоциируем символы с кодами - создаем структуру map  codeTabl
  BuildCodeTable(root);

  if (config["coding.print_CODDING_TABL"].as<bool>())
    // Печатаем codeTabl
    PrintTable();

  const std::chrono::time_point<std::chrono::steady_clock> stop_stage1 =
      std::chrono::steady_clock::now();

  cout << "Time_stage1 - "
       << std::chrono::duration_cast<std::chrono::milliseconds>(stop_stage1 -
                                                                stop_read)
              .count()
       << " milliseconds" << endl
       << endl;

  // Перемещаем указатель в начало файла
  cout << "Second scan of the file: " +
              config["coding.input_name"].as<std::string>() +
              " - start encodding"
       << endl;
  in.clear();
  in.seekg(0);
  //  ss.clear();
  //  ss.seekg(0);

  //        ofstream out_code("CODDING_DATA", ios::out | ios::binary);
  int count = 0;
  char buf = 0;  //Буфер вывода

  while (!in.eof()) {
    //Получаем символ из файла
    char c = in.get();
    //Код, соответствующий полученному символу берем из таблицы
    //кодирования
    vector<bool> kod_simvola = codeTabl[c];
    //Формируем выходной поток битов (по 8)
    for (int n = 0; n < kod_simvola.size(); ++n) {
      buf = buf | kod_simvola[n] << (7 - count);
      count++;
      if (count == 8) {
        count = 0;
        codding_file.push_back(buf);
        buf = 0;
        ++lenth_out;
      }
    }
  }

  cout << "Codding finishing" << endl;

  const std::chrono::time_point<std::chrono::steady_clock> stop_stage2 =
      std::chrono::steady_clock::now();

  cout << "Time_stage2 - "
       << std::chrono::duration_cast<std::chrono::milliseconds>(stop_stage2 -
                                                                stop_stage1)
              .count()
       << " milliseconds" << endl
       << endl;

  cout << "Time_stage_read+1+2 - "
       << std::chrono::duration_cast<std::chrono::milliseconds>(stop_stage2 -
                                                                start)
              .count()
       << " milliseconds" << endl
       << endl;
}

void Coding::Impl::writeFile() {
  // Для декодирования нам нужно будет построить дерево - для этого
  // нужно передать все символы и частоту вхождения каждого символа
  // Выдаем колл. символов таблицы, колл символов сжатого файла и три
  // массива
  FILE* out;
  //  char* NAME = argv[1];

  //    char *SUFFIX = {".Huffman"};
  //    string NAME_STRING = NAME;
  //    string SUFFIX_STRING = SUFFIX;
  //    string FULLNAME = NAME_STRING+SUFFIX_STRING;
  //    const char *NAME_CHAR = FULLNAME.c_str();

  out = fopen((config["coding.output_path"].as<std::string>() +
               config["coding.output_name"].as<std::string>())
                  .c_str(),
              "wb");

  int NUMBER;
  NUMBER = m.size();
  int DIG[m.size()];
  char SYM[m.size()];

  int l = 0;
  for (auto i = m.begin(); i != m.end(); ++i) {
    DIG[l] = i->second;
    SYM[l] = i->first;
    ++l;
  }
  cout << "NUMBER:" << NUMBER << endl;
  cout << "lenth_out:" << lenth_out << endl;

  fwrite(&NUMBER, sizeof NUMBER, 1, out);
  fwrite(&lenth_out, sizeof lenth_out, 1, out);
  fwrite(SYM, sizeof SYM, 1, out);
  fwrite(DIG, sizeof DIG, 1, out);
  char cc;
  for (int z = 0; z < lenth_out; ++z) {
    cc = codding_file[z];
    fwrite(&cc, sizeof cc, 1, out);
  }

  fclose(out);

  cout << "Creating file: " << config["coding.output_name"].as<std::string>()
       << " - " << lenth_out << " bytes" << endl;
  cout << "ratio  " << 100 - (100 * lenth_out / lenth_in) << "%" << endl;
}
