document.write("<h4>Числа Фибоначчи</h4>")
// Размер массива и индексная переменная:
var n=15,k
// Создание массива из двух элементов:
var fibs=new Array(1,1)
// Заполнение массива числами:
for(k=2;k<n;k++){
   fibs[k]=fibs[k-1]+fibs[k-2]
}
// Отображение содержимого массива:
for(k=0;k<fibs.length;k++){
   document.write(fibs[k]+" | ")
}