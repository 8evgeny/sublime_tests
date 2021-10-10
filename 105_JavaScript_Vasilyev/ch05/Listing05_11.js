// Функция для отображения содержимого массива:
function show(name,array){
   document.write(name+" = "+array.join(" | ")+"<br>")
}
// Функция для копирования массивов:
function makeCopy(array){
   // Создание массива:
   var tmp=new Array(array.length)
   // Поэлементное копирование значений:
   for(var k=0;k<tmp.length;k++){
      // Если копируемый элемент - массив:
      if(Array.isArray(array[k])){
         // Рекурсивный вызов функции:
         tmp[k]=makeCopy(array[k])
      }
      // Если копируемый элемент - не массив:
      else{
         tmp[k]=array[k]
      }
   }
   // Результат функции - массив:
   return tmp
}
// Массив с числовыми элементами:
var A=[1,2,3,4,5]
show("A",A)
// Создание копии массива:
var B=makeCopy(A)
document.write("После присваивания <code>B = makeCopy(A)</code>:<br>")
show("B",B)
// Присваивание значения элементу массива:
A[0]=100
document.write("После присваивания <code>A[0] = 100</code>:<br>")
show("A",A)
show("B",B)
document.write("Массив содержит среди элементов другой массив:<br>")
// Массив с элементом - массивом:
var C=[1,[2,3],4,5]
show("C",C)
// Создание копии массива:
var D=makeCopy(C)
document.write("После присваивания <code>D = makeCopy(C)</code>:<br>")
show("D",D)
// Присваивание значений элементам массива:
C[1][0]=200
C[3]=500
document.write("После выполнения команд <code>C[1][0] = 200</code> и <code>C[3] = 500</code>:<br>")
show("C",C)
show("D",D)