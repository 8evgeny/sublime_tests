#include "main.h"
using namespace std;

struct Decoding::Impl {
  Impl();
  void readConfig(const char*);
  void decoding();
  po::variables_map config;
};

Decoding::Impl::Impl() {}

Decoding::Decoding() : _d{make_unique<Impl>()} {
  cout << "Decodding_constructor" << endl;
  _d->readConfig("../../config.ini");
  _d->decoding();
  //    _d->writeFile();
}
Decoding::~Decoding() {}

void Decoding::Impl::readConfig(const char* conf_file) {
  po::options_description decoding("decoding");
  decoding.add_options()("decoding.input_path,in", po::value<std::string>(),
                         "input_path")("decoding.output_path,out",
                                       po::value<std::string>(),
                                       "output path decoding")(
      "decoding.input_name,iname", po::value<std::string>(),
      "input_name coding")("decoding.output_name,oname",
                           po::value<std::string>(), "output_name decoding");
  po::options_description desc("Allowed options");
  desc.add(decoding);
  try {
    po::parsed_options parsed = po::parse_config_file<char>(
        conf_file, desc,
        true);  //флаг true разрешает незарегистрированные опции !
    po::store(parsed, config);
  } catch (const po::reading_file& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  po::notify(config);
  std::cout << config["decoding.input_path"].as<std::string>() << std::endl;
  std::cout << config["decoding.input_name"].as<std::string>() << std::endl;
  std::cout << config["decoding.output_path"].as<std::string>() << std::endl;
  std::cout << config["decoding.output_name"].as<std::string>() << std::endl;
}

void Decoding::Impl::decoding() {
  cout << "Start decoding file" << endl;

  int NUMBER;    //Общее число символов в таблице
  int lenth_in;  //Длина сжатых данных
  FILE* in;
  in = fopen((config["decoding.input_path"].as<std::string>() +
              config["decoding.input_name"].as<std::string>())
                 .c_str(),
             "rb");
  //Получаем длину таблицы и длину сжатого файла
  fread(&NUMBER, sizeof NUMBER, 1, in);
  fread(&lenth_in, sizeof lenth_in, 1, in);
  cout << "NUMBER:" << NUMBER << endl;
  cout << "lenth_in:" << lenth_in << endl;
  //В зависимости от полученных значений создаем 3 массива
  int DIG[NUMBER];
  char SYM[NUMBER];
  vector<char> V_IN{};
  char cc;
  //Читаем в массивы данные
  fread(SYM, sizeof SYM, 1, in);
  fread(DIG, sizeof DIG, 1, in);

  for (int z = 0; z < lenth_in; ++z) {
    fread(&cc, sizeof cc, 1, in);
    V_IN.push_back(cc);
  }

  fclose(in);

  // Восстанавливаем кодовую таблицу - создаем map
  pair<char, int> p;
  map<char, int> m;
  int i = 0;
  for (i = 0; i < NUMBER; ++i) {
    p.first = SYM[i];
    p.second = DIG[i];
    m.insert(p);
  }

  //Список указателей на узлы нашего дерева
  list<Node*> t;

  //Проходим по map и для каждого символа создаем узел дерева node и помещаем
  //его в list
  map<char, int>::iterator itmap;
  for (itmap = m.begin(); itmap != m.end(); ++itmap) {
    Node* p = new Node;
    p->char_in_node = itmap->first;
    p->num_in_node = itmap->second;
    t.push_back(p);
  }

  //Строим дерево
  while (t.size() != 1)  // Цикл пока в контейнере не останется корень
  {
    t.sort(Compare_Node());
    Node* SONL = t.front();
    t.pop_front();
    Node* SONR = t.front();
    t.pop_front();
    Node* parrent = new Node(SONL, SONR);
    t.push_back(parrent);
  }
  // на выходе цикла остался 1 элемент - он-же корень
  Node* root = t.front();

  //Печать дерева
  //               cout<<endl<<"--------------------    BINARE TREE
  //               ------------------------- "<<endl; PrintTree(root);

  cout << "Данные будем писать в файл"
       << (config["decoding.output_path"].as<std::string>() +
           config["decoding.output_name"].as<std::string>())
       << endl;
  ofstream DATA_OUT((config["decoding.output_path"].as<std::string>() +
                     config["decoding.output_name"].as<std::string>())
                        .c_str(),
                    ios::out | ios::binary);
  int numout = 0;
  Node* pp = root;
  int count = 0;
  char byte;
  //Процедура декодирования
  byte = V_IN[0];
  for (int i = 1; i < (lenth_in);) {
    bool b = byte & (1 << (7 - count));
    if (b)
      pp = pp->right_branch;
    else
      pp = pp->left_branch;
    if (pp->left_branch == nullptr && pp->right_branch == nullptr) {
      ++numout;
      DATA_OUT << pp->char_in_node;
      pp = root;
    }
    ++count;
    if (count == 8) {
      count = 0;
      byte = V_IN[i];
      ++i;
    }
  }
  DATA_OUT.close();
  cout << "numout:" << numout << endl;
  cout << "Creating output file " << endl;
}
