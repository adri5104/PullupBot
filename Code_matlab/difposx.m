%% FUNCION PARA DIFERENCIA ENTRE POSICION FINAL E INICIAL EN X

 function difx =difposx(pi,pf)
 
 XDELTA=230;
 
 if pf(1)>0 difx = pi(1)+pi(4)+XDELTA;    %comparo la pi del stepper con la x max del delta 
 else difx = pi(1)+pi(4)-XDELTA;
 end 
     
 end