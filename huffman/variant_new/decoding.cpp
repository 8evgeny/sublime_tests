#include "main.h"
using namespace std;

struct Decoding::Impl {
  Impl();
  void readConfig(const char*);
  void decoding();
  po::variables_map config;
  int numbit = 0;
  long lench_origin = 0;
};

Decoding::Impl::Impl() {}

Decoding::Decoding() : _d{make_unique<Impl>()} {
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

  int map_size;  //Общее число символов в таблице
  int lenth_in;  //Длина сжатых данных
  FILE* in;
  in = fopen((config["decoding.input_path"].as<std::string>() +
              config["decoding.input_name"].as<std::string>())
                 .c_str(),
             "rb");
  //Получаем длину таблицы и длину сжатого файла
  fread(&map_size, sizeof map_size, 1, in);
  fread(&lenth_in, sizeof lenth_in, 1, in);
  cout << "map_size:" << map_size << endl;
  cout << "lenth_in:" << lenth_in << endl;
  //В зависимости от полученных значений создаем 3 массива
  int DIG[map_size];
  char SYM[map_size];
  vector<char> v_input_char{};
  char cc;
  //Читаем в массивы данные
  fread(SYM, sizeof SYM, 1, in);
  fread(DIG, sizeof DIG, 1, in);
  fread(&lench_origin, sizeof lench_origin, 1, in);
  cout << "numbit:" << numbit << endl;
  for (int z = 0; z < lenth_in; ++z) {
    fread(&cc, sizeof cc, 1, in);
    v_input_char.push_back(cc);
  }

  fclose(in);

  // Восстанавливаем кодовую таблицу - создаем map
  pair<char, int> p;
  map<char, int> m;
  int i = 0;
  for (i = 0; i < map_size; ++i) {
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
  ofstream data_out((config["decoding.output_path"].as<std::string>() +
                     config["decoding.output_name"].as<std::string>())
                        .c_str(),
                    ios::out | ios::binary);
  int numout = 0;
  Node* pp = root;
  int count = 0;
  char byte;
  //Процедура декодирования
  for (int i = 0; i < lenth_in;) {
    byte = v_input_char[i];
    bool b = byte & (1 << (7 - count));
    if (b)
      pp = pp->right_branch;
    else
      pp = pp->left_branch;

    if (pp->left_branch == nullptr && pp->right_branch == nullptr) {
      ++numout;
      data_out << pp->char_in_node;
      pp = root;
      if (numout == lench_origin) break;
    }

    ++count;
    if (count == 8) {
      count = 0;
      ++i;
    }
  }
  data_out.close();
  cout << "numout:" << numout << endl;
  cout << "Creating output file " << endl;
}
