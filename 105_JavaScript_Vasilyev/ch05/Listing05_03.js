document.write("<h4>Массив</h4>")
// Создание массива:
var nums=new Array(10,true,30,"текст",75)
// Отображение содержимого массива:
for(var k=0;k<nums.length;k++){
   document.write(nums[k]+" | ")
}