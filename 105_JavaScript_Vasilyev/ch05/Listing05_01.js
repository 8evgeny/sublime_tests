document.write("<h4>Создание массива</h4>")
// Создание массива:
var nums=[10,true,30,"текст",75]
// Отображение содержимого массива:
document.write(nums+"<br>")
for(var k in nums){
   document.write(nums[k]+" | ")
}