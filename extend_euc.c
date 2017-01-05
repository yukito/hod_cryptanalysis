int Ex_Euc(int aa,int bb)
{
  int a=aa,b=bb,c;
  int u1=1,u2=-1*(b/(a%b)),v1=a/b,v2=1+(b/(a%b))*(a/b);

  if(aa==1) return 1; 
  c=b;
  b=b%(a%b);
  a=a%c;
  while(1){
    if(b==0) break;
    if(b==1) return (u2+bb)%bb;
    u1=u1-(a/b)*u2;
    v1=v1-(a/b)*v2;
    c=b; b=a%b; a=c;
    if(b==1) return (u1+bb)%bb;
    u2=u2-(a/b)*u1;
    v2=v2-(a/b)*v1;
    c=b; b=a%b; a=c;
  }
  return 0;
}
