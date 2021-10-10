// Вспомогательная функция для отображения массива:
function show(name,array){
   document.write(name+" = "+array.join(" | ")+"<br>")
}
// Массив с числовыми элементами:
var A=[1,2,3,4,5]
show("A",A)
// Копирование массива:
var B=A.slice(0)
document.write("После присваивания <code>B = A.slice(0)</code>:<br>")
show("B",B)
// Изменение значения элемента массива:
A[0]=100
document.write("После присваивания <code>A[0] = 100</code>:<br>")
show("A",A)
show("B",B)
document.write("Массив содержит среди элементов другой массив:<br>")
// Массив с элементом - массивом:
var C=[1,[2,3],4,5]
show("C",C)
// Копирование массива:
var D=C.slice(0)
document.write("После присваивания <code>D = C.slice(0)</code>:<br>")
show("D",D)
// Изменение значений элементов массива:
C[1][0]=200
C[3]=500
document.write("После выполнения команд <code>C[1][0] = 200</code> и <code>C[3] = 500</code>:<br>")
show("C",C)
show("D",D)