%% FUNCION QUE CALCULA LA DIST DEL PUNTO AL QUE QUIERO LLEGAR AL LIMITE DEL ESPACIO DE TRABAJO
function d= dist_espt(sp)

XMAX=500;
XMIN=-505;
YMAX=120;
YMIN=-120;
ZMAX=0;
ZMIN=-350;

if sp(1)>0
d(1)=XMAX-sp(1);
else d(1)=-XMIN+sp(1);
end 

if sp(2)>0
d(2)=YMAX-sp(2);
else d(2)=-YMIN+sp(2);
end 

if sp(3)>0
d(3)=ZMAX-sp(3);
else d(3)=-ZMIN+sp(3);
end 

end