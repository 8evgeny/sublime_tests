
# Создание 200 файлов

# def open_new_file(name):
# 	s="Z:\\CODDING\\files_fo_primery\\"+str(name)+".txt"
# 	file = open(s, "w")  #Создание нового файла

# 	return file.name    #  Возвращает только имя созданного файла
# 	# при возврате из функции файл закрывается
# 	# если убрать метод name будет возвращать все параметры файла


# for ii in range(1,201):
# 	x=open_new_file(ii)
# 	print("Создан файл:",x) # ВАЖНО!!  при печати разные типы данных отделяются запятыми
# 	file = open(x, "w")
# 	file.write("Python  COOL!!!!!!  RAHU!!!!")
# 	file.close()
#
#                           Выше вариант через новую функцию
# H:\1\Python\files_fo_primery
for ii in range(1,501):
	s="H:\\1\\Python\\files_fo_primery\\"+str(ii)+".txt"
	file = open(s, "w")  #Создание нового файла
	print("Создан файл:",file.name) # ВАЖНО!!  при печати разные типы данных отделяются запятыми
	FileWrite= "Это файл №" ,ii, "OM SHIVAYA  NAMAHA !!!!"
	file.write (str(FileWrite))
	file.close()
