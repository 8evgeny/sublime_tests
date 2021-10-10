var txt,name,msg
txt="Давайте познакомимся! Как Вас зовут?"
msg="Жаль, но Вы не представились!"
name=prompt(txt)
if(name!=""){
   msg="Приятно познакомиться, "+name+"!"
}
document.write(msg)