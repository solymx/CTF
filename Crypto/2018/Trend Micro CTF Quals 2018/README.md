# Trend Micro CTF Quals 2018 - Notes

## Offensive-Analysis 300
> Description:
>
> There is going to be a party tommorow. Eva sent an invitation to her friends. Securely, of course!
> 
> Download the message.txt file from the link to check the secure invitation message Download the file

給了三個 n 但 e 相同，先猜 common factor attack
```python
#!/usr/bin/env python
import libnum

e = 65537
ac = 18700320110367574655449823553009212724937318442101140581378358928204994827498139841897479168675123789374462637095265564472109735802305521045676412446455683615469865332270051569768255072111079626023422
an = 23795719145225386804055015945976331504878851440464956768596487167710701468817080174616923533397144140667518414516928416724767417895751634838329442802874972281385084714429143592029962130216053890866347 

bc = 27979368157170890767030069060194038526134599497456846620984054211906413024410400026053694007247773572972357106574636186987337336771777265971389911503143036021889778839064900818858188026318442675667707
bn = 46914096084767238967814493997294740286838053572386502727910903794939283633197997427383196569296188299557978279732421725469482678512672280108542428152186999218210536447287087212703368704976239539968977 

cc = 24084879450015204136831744759734371350696278325227327049743434712309456808867398488915798176282769616955247276506807739249439515225213919008982824219656080794207250454008942016125074768497986930713993
cn = 24543003393712692769038137223030855401835344295968717177380639898023646407807465197761211529143336105057325706788229129519925129413109571220297378014990693203802558792781281981621549760273376606206491 

abp = libnum.gcd(an,bn)
aq = an / abp
d = libnum.invmod(e, (aq-1)*(abp-1))
am = libnum.n2s(pow(ac,d,an))
print "a: ",am

bq = bn / abp
d = libnum.invmod(e, (bq-1)*(abp-1))
bm = libnum.n2s(pow(bc,d,bn))
print "b: ",bm
```
