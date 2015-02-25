import os

# Pomocna funkcia na zapis implikacie do suboru
def impl(subor, a, b):
        subor.write( "{0:d} {1:d} 0\n".format(-a, b) )
        
class NQueens():
    def solve(self,n):
        subor_in=open("vstup.txt","w");
        for y1 in range(n):
            for x1 in range(n):
                    
                for x2 in range(n):
                    if x1!=x2:
                        impl(subor_in,n*y1+x1+1,(n*y1+x2+1)*(-1))
                        
                for y2 in range(n):
                    if y1!=y2:
                        impl(subor_in,n*y1+x1+1,(n*y2+x1+1)*(-1))

                x2=x1-1
                y2=y1-1
                while x2>=0 and y2>=0:
                    impl(subor_in,n*y1+x1+1,(n*y2+x2+1)*(-1))
                    x2-=1;
                    y2-=1;

                x2=x1-1
                y2=y1+1
                while x2>=0 and y2<n:
                    impl(subor_in,n*y1+x1+1,(n*y2+x2+1)*(-1))
                    x2-=1;
                    y2+=1;

                x2=x1+1
                y2=y1-1
                while x2<n and y2>=0:
                    impl(subor_in,n*y1+x1+1,(n*y2+x2+1)*(-1))
                    x2+=1;
                    y2-=1;

                x2=x1+1
                y2=y1+1
                while x2<n and y2<n:
                    impl(subor_in,n*y1+x1+1,(n*y2+x2+1)*(-1))
                    x2+=1;
                    y2+=1;

            for x1 in range(n):
                print(n*y1+x1+1,end=" ",file=subor_in)
            print("0",file=subor_in);
        subor_in.close()

        cesta_k_SAT= "C:\\Users\\Anima\\Downloads\\udvl-master\\udvl-master\\tools\\win\\MiniSat_v1.14.exe";
        os.system("{} vstup.txt vystup.txt".format(cesta_k_SAT))

        subor_out=open("vystup.txt","r")
        sat=subor_out.readline()
        if sat=="SAT\n":
            riesenie=subor_out.readline()
            res=[]
            for cislo in riesenie.split():
                cislo=int(cislo)
                if cislo>0:
                    x=(cislo-1)%n
                    y=(cislo-1)//n
                    res.append((x,y));
            return res;    
        return []
        
