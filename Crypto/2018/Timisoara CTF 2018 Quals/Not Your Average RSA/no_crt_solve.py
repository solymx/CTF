#!/usr/bin/env python
import libnum

pri= [23554169,24525821 ,31703933 ,25671797 ,24996157 ,27739163 ,20013121 ,17673199 ,29488469 ,30580789 ,21321539 ,31881917 ,25808239 ,22685197 ,30342329 ,24946057 ,16904777 ,18646361 ,19459483 ,31696261 ,22050221 ,20010041 ,25963459 ,20197313 ,21891889 ,31737131 ,33098557 ,29511773 ,28863719 ,20390129 ,17901463 ,18145913 ,33381329 ,27289543 ,27409927 ,33322589 ,17730961 ,27138691 ,22576643 ,27606707 ,21647243 ,18313601]

e = 65537
c=9074407119435549226216306717104313210750146895081726439798095976354600576814818348656600684713830051655944443364224597709641982342039946659987121376590618828822446965847273448794324003758131816407702456966504389655568712152599077538994030379567217702587542326383955580601916478060973206347266442527564009737910
n=18086135173395641986123054725350673124644081001065528104355398467069161310728333370888782472390469310073117314933010148415971838393130403883412870626619053053672200815153337045022984003065791405742151350233540671714100052962945261324862393058079670757430356345222006961306738393548705354069502196752913415352527


phi = 1
for i in pri:
	phi *= (i-1)
d = libnum.invmod(e, phi)
print libnum.n2s(pow(c,d,n))