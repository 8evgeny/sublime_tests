var n=100,s=0,k=1
var txt="1<sup>2</sup> + 2<sup>2</sup> + ... + "
txt+=n+"<sup>2</sup> = "
// Первый блок и тело оператора пустые:
for(;k<=n;s+=k*k,k++);
document.write(txt+s)