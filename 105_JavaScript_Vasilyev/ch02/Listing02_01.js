var txt,name
txt="Давайте познакомимся! Как Вас зовут?"
name=prompt(txt)
if(name==""){
   document.write("Жаль, но Вы не представились!")
}
else{
   document.write("Приятно познакомиться, "+name+"!")
}