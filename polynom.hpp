#include <iostream>
#include <cmath>
#include <vector>
#include <memory.h>
//класс Polynom
template <typename T>
class Polynom{
private:
    unsigned int deg; //степень полинома
    T *coefficient; //указатель на массив коэффициентов полинома, coefficient[i] - коэффициент при i-й степени
public:
    Polynom(unsigned int count)
    {
        deg=count;
        coefficient=new double[deg+1];
    }
    Polynom():deg(0){
        coefficient=new double[deg+1];
        coefficient[0]=0.0;
    }

    Polynom(unsigned int new_deg, T *new_coefficient){//new_coefficient[i] - коффициент при i-й степени      new_deg-степень создаваемого полин.
        deg=0;
        for(int i=0;i<=new_deg;i++)//cтепень полинома-наибольший номер
            if(new_coefficient[i]!=0){
                deg=i;   //инициализация переменной степени
            }
        coefficient=new T[deg+1];
        //прописываем что при iтой степень коэффецет будет = new_koef[i]
        for(int i=0;i<=deg;i++)
            coefficient[i]=new_coefficient[i]; //инициализация массива коэффициентов
    }

    //копирующий конструктор
    Polynom(const Polynom &pol){
        deg=pol.deg;
        coefficient=new T[deg+1];
        for(int i=0;i<=deg;i++)
            coefficient[i]=pol.coefficient[i];
    }
    //деструктор
    ~Polynom(){
        delete[] coefficient;

    }
    //сеттеры
    void set_deg(int deg_){
        this->deg = deg_;
    }
    void set_coef(int i, T coefficent){
        this->coefficient[i] = coefficent;
    }
    //геттеры

    // функция получения степени полинома
    unsigned int GetDeg(){
        return this->deg;
    }
    // функция получения коэффициента при i-й степени
    double GetСoefficient(unsigned int i){
        if(i<=deg)
            return coefficient[i];
        else
            return 0.0;
    }
    Polynom operator[] (unsigned int i){
        if(i<=deg)
            return coefficient[i];
        else
            return 0.0;
    }


    //оператор сложения двух полиномов
    Polynom operator+ (const Polynom &t){
        int i;
        Polynom *result;

        if(deg>=t.deg){ //если степень первого полинома больше степени второго
            result=new Polynom(deg,coefficient);
            for(i=0;i<=t.deg;i++)
                result->coefficient[i]=result->coefficient[i]+t.coefficient[i];
        }
        else{ //если степень второго полинома больше степень первого
            result=new Polynom(t.deg,t.coefficient);
            for(i=0;i<=deg;i++)
                result->coefficient[i]=result->coefficient[i]+coefficient[i];
        }
        result->isCorrectDeg();
        return *result;
    }
    Polynom operator- (const Polynom &t){
        int i;
        Polynom *result;

        if(deg>=t.deg){ //если степень первого полинома больше степени второго
            result=new Polynom(deg,coefficient);
            for(i=0;i<=t.deg;i++)
                result->coefficient[i]=result->coefficient[i]-t.coefficient[i];
        }
        else{                   //если степень второго полинома больше степень первого
            std::cout << "Скорее всего будет ошибка, степень полинома из которого вычитаем < вычитаемого !!!\n";
            result=new Polynom(t.deg,t.coefficient);
            for(i=0;i<=deg;i++)
                result->coefficient[i]=result->coefficient[i]-coefficient[i];
        }
        result->isCorrectDeg();
        return *result;
    }
    /**
    Polynom operator + (){//поменять знаки коэффицентов на противоположные ??????
        for(int i=0;i<=deg;i++)
            coefficient[i]=(coefficient[i]*(-1));
    }*/
    Polynom operator+= (const Polynom &t){
        int i;
        Polynom *result;

        if(deg>=t.deg){ //если степень первого полинома больше степени второго
            result=new Polynom(deg,coefficient);
            for(i=0;i<=t.deg;i++)
                result->coefficient[i]=result->coefficient[i]+t.coefficient[i];
        }
        else{                   //если степень второго полинома больше степень первого
            result=new Polynom(t.deg,t.coefficient);
            for(i=0;i<=deg;i++)
                result->coefficient[i]=result->coefficient[i]+coefficient[i];
        }
        result->isCorrectDeg();
        deg=result->deg;
        coefficient=new double[deg+1];
        for(int i=0;i<=deg;i++)
            coefficient[i]=result->coefficient[i];
        return *this;
    }
    Polynom operator-= (const Polynom &t){
        int i;
        Polynom *result;

        if(deg>=t.deg){ //если степень первого полинома больше степени второго
            result=new Polynom(deg,coefficient);
            for(i=0;i<=t.deg;i++)
                result->coefficient[i]=result->coefficient[i]-t.coefficient[i];
        }
        else{                   //если степень второго полинома больше степень первого
            std::cout << "ошибка!!! степень полигона из которого вычитаем меньше вычитаемого\n";
        }
        result->isCorrectDeg();
        deg=result->deg;
        coefficient=new double[deg+1];
        for(int i=0;i<=deg;i++)
            coefficient[i]=result->coefficient[i];
        return *this;

    }

//оператор присваивания
    Polynom operator= (const Polynom &t){
        deg=t.deg;
        delete[] coefficient;
        coefficient=new double[deg+1];
        for(int i=0;i<=deg;i++)
            coefficient[i]=t.coefficient[i];
        return *this;
    }
    bool operator== (const Polynom &second){
        for(int i=0;i<=deg;i++)
            if(coefficient[i]!=second.coefficient[i]){
                return false;
            }
        return true;
    }
    bool operator!= (const Polynom &second){
        for(int i=0;i<=deg;i++)
            if(coefficient[i]==second.coefficient[i]){
                return false;
            }
        return true;
    }

//оператор умножения числа на полином

    Polynom operator* (double number){
        if(number==0){
            Polynom result;
            return result;
        }
        else{
            int deg=this->deg;
            double *tmp_coefficient=new double[deg+1];
            int h=0;
            while(h<=deg){
                tmp_coefficient[h]=number*this->coefficient[h];
                h++;
            }
            Polynom result(deg,tmp_coefficient);//создаём новый полином,который возвратив
            delete[] tmp_coefficient;//чистим
            return result;
        }
    }
    Polynom operator*= (double number){
        if(number==0){
            Polynom result;
            return result;
        }
        else{
            //int deg=temp.deg;
            T *tmp_coefficient=new double[deg+1];
            int h=0;
            while(h<=deg){
                tmp_coefficient[h]=number*coefficient[h];
                h++;
            }
            Polynom result(deg,tmp_coefficient);//создаём новый полином,который возвратив
            delete[] tmp_coefficient;//чистим

            result.isCorrectDeg();
            deg=result.deg;
            coefficient=new double[deg+1];
            for(int j=0;j<=deg;j++)
                coefficient[j]=result.coefficient[j];
            return *this;
        }
    }
    Polynom operator* (const Polynom& f){//2й тип
        Polynom temp;
        temp.deg=deg+f.deg;
        temp.coefficient=new double[temp.deg+1];
        memset(temp.coefficient, 0, (temp.deg+1)*sizeof(double));//заполнение массива 0
        for(int i=0;i<=deg;i++)
        {
            for(int j=0;j<=f.deg;j++)
            {
                temp.coefficient[i+j] +=coefficient[i]*f.coefficient[j];
            }
        }
        return temp;
    }
    Polynom operator*= (const Polynom& f){//2й тип
        Polynom temp;
        temp.deg=deg+f.deg;
        temp.coefficient=new double[temp.deg+1];
        memset(temp.coefficient, 0, (temp.deg+1)*sizeof(double));//заполнение массива 0
        for(int i=0;i<=deg;i++)
        {
            for(int j=0;j<=f.deg;j++)
            {
                temp.coefficient[i+j] +=coefficient[i]*f.coefficient[j];
            }
        }
        temp.isCorrectDeg();
        deg=temp.deg;
        coefficient=new double[deg+1];
        for(int j=0;j<=deg;j++)
            coefficient[j]=temp.coefficient[j];
        return *this;
    }

    Polynom operator/ (double number){
        if(number==0){
            std::cout << "ошибка!!! На ноль делить нельзя!!\n";
            Polynom result;
            return result;
        }
        else{
            int deg = this->deg;
            double *tmp_coefficient=new double[deg+1];
            int h=0;
            while(h<=deg){
                tmp_coefficient[h]= this->coefficient[h]/number;
                h++;
            }
            Polynom result(deg,tmp_coefficient);//создаём новый полином,который возвратив
            delete[] tmp_coefficient;//чистим
            return result;
        }
    }
    Polynom operator/= (double number){
        if(number==0){
            std::cout << "ошибка!!! На ноль делить нельзя!!\n";
            exit(4);
        }
        else{
            //int deg=temp.deg;
            double *tmp_coefficient=new double[deg+1];
            int h=0;
            while(h<=deg){
                tmp_coefficient[h]=coefficient[h]/number;
                h++;
            }
            Polynom result(deg,tmp_coefficient);//создаём новый полином,который возвратив
            delete[] tmp_coefficient;//чистим
            result.isCorrectDeg();
            deg=result.deg;
            coefficient=new double[deg+1];
            for(int j=0;j<=deg;j++)
                coefficient[j]=result.coefficient[j];
            return *this;
        }
    }
    Polynom operator/ (const Polynom& f)
    {
        Polynom temp;
        Polynom ob_1;
        Polynom ob_2;
        Polynom ob_3;

        temp.deg=deg-f.deg;
        temp.coefficient=new double[temp.deg+1];
        memset(temp.coefficient, 0, (temp.deg+1)*sizeof(double));

        ob_1.deg=deg;
        ob_1.coefficient=new double[deg+1];
        for(int i=deg;i>=0;i--)
            ob_1.coefficient[i]=coefficient[i];


        ob_2.deg=f.deg;
        ob_2.coefficient=new double[f.deg+1];
        for(int i=f.deg;i>=0;i--)
            ob_2.coefficient[i]=f.coefficient[i];

        ob_3.deg=f.deg;
        ob_3.coefficient=new double[ob_1.deg+1];

        int s=0;
        int j=0;
        int k=ob_1.deg;
        while(s==0){
            if(ob_1.deg>=ob_2.deg){
                j=ob_2.deg;
                for(int i=ob_1.deg; i>=0; i--){
                    if(j>=0){
                        ob_3.coefficient[i]=ob_2.coefficient[j];
                        j--;
                    }
                    else ob_3.coefficient[i]=0;
                }

                for(int i=0; i<=ob_1.deg; i++){
                    ob_3.coefficient[i]*=ob_1.coefficient[k];
                }
                temp.coefficient[ob_1.deg-1]=ob_1.coefficient[k];

                for(int i=0; i<=ob_1.deg; i++){
                    ob_1.coefficient[i]-=ob_3.coefficient[i];
                }

            }
            else s=1;
            k--;
            ob_1.deg--;
        }
        return temp;
    }
    Polynom operator/= (const Polynom& f)
    {
        Polynom temp;
        Polynom ob_1;
        Polynom ob_2;
        Polynom ob_3;

        temp.deg=deg-f.deg;
        temp.coefficient=new double[temp.deg+1];
        memset(temp.coefficient, 0, (temp.deg+1)*sizeof(double));

        ob_1.deg=deg;
        ob_1.coefficient=new double[deg+1];
        for(int i=deg;i>=0;i--)
            ob_1.coefficient[i]=coefficient[i];


        ob_2.deg=f.deg;
        ob_2.coefficient=new double[f.deg+1];
        for(int i=f.deg;i>=0;i--)
            ob_2.coefficient[i]=f.coefficient[i];

        ob_3.deg=f.deg;
        ob_3.coefficient=new double[ob_1.deg+1];

        int s=0;
        int j=0;
        int k=ob_1.deg;
        while(s==0){
            if(ob_1.deg>=ob_2.deg){
                j=ob_2.deg;
                for(int i=ob_1.deg; i>=0; i--){
                    if(j>=0){
                        ob_3.coefficient[i]=ob_2.coefficient[j];
                        j--;
                    }
                    else ob_3.coefficient[i]=0;
                }

                for(int i=0; i<=ob_1.deg; i++){
                    ob_3.coefficient[i]*=ob_1.coefficient[k];
                }
                temp.coefficient[ob_1.deg-1]=ob_1.coefficient[k];

                for(int i=0; i<=ob_1.deg; i++){
                    ob_1.coefficient[i]-=ob_3.coefficient[i];
                }

            }
            else s=1;
            k--;
            ob_1.deg--;
        }
        temp.isCorrectDeg();
        deg=temp.deg;
        coefficient=new double[deg+1];
        for(int j=0;j<=deg;j++)
            coefficient[j]=temp.coefficient[j];
        return *this;
    }

    void isCorrectDeg(){// при максимальной степени должен быть ненулевой коэффицент
        if(coefficient[deg]==0){//просто перескакиваем
            while(deg && coefficient[deg]==0){
                deg--;
            }
        }
    }
    friend std::ostream& operator<< (std :: ostream& stream, const Polynom<T>& t);
    friend std :: istream& operator>> (std :: istream& stream, Polynom<T>& poly);

     std::string print(unsigned int new_deg, double *new_coefficient){
        std::string str;
        int  deg = new_deg;
        //double coefficient = new_coefficient(0);
        //первое значение (начало нашего полинома)
        if(new_coefficient[deg]==1){
            str += "x^";
            str += char(deg+ '0');
        }
        else if(new_coefficient[deg]==-1){
            str += "-x^";
            str += char(deg+ '0');
        }
        else{
            str += char(new_coefficient[deg]+'0');
            str += "x^";
            str += char(deg+ '0');
        }

        for(int i=deg-1;i>0;i--){//выводим столько раз(сколько у нас коэфицентов)
            if(new_coefficient[i]>0){
                if(new_coefficient[i]==1){
                    str += " + ";
                    str += "x^";
                    str += char(i+ '0');
                }
                else{
                    str += " + ";
                    str += char(new_coefficient[i])+'0';
                    str += "x^";
                    str += char(i+ '0');
                }

            }else if(new_coefficient[i]<0)//если каждый коэфицент -цифра -> у нас вычитание
                if(new_coefficient[i]==(-1)){
                    str += " - ";
                    str += "x^";
                    str += char(i+ '0');
                }
                else{
                    str += " - ";
                    str += char((-1)*new_coefficient[i]+'0');
                    str += "x^";
                    str += char(i+ '0');
                }
        }
        //степень нулевая-свободные члены(всегда идут в конце)
        if(new_coefficient[0]>0){
            str += " + ";
            str += char(new_coefficient[0]+'0');
        }
        else if(new_coefficient[0]<0){
            str += " - ";
            str += char((-1)*new_coefficient[0]+'0');
        }
        return str;
    }

};
template <typename T>
std :: istream& operator>> (std :: istream& stream, Polynom<T>& poly){
    unsigned int  deg;
    double *coefficient;
    stream >> deg;
    coefficient=new double[deg+1];//степень не будет 0
    for(int i=0;i<deg;i++){//считываем эти коэфиценты у степеней

        stream >> coefficient[i];
    }
    while(!coefficient[deg]){
        stream >> coefficient[deg];
    }
    poly = Polynom<double>(deg, (coefficient));
    return stream;

}
template <typename T>
std::ostream& operator<< (std :: ostream& stream,  Polynom<T>& t){
    unsigned int  deg = t.GetDeg();
    double coefficient = t.GetСoefficient(0);
    //первое значение (начало нашего полинома)
    if(t.GetСoefficient(deg)==1) stream << "x^" << deg;
    else if(t.GetСoefficient(deg)==-1) stream << "-x^" << deg;
    else stream << t.GetСoefficient(deg) << "x^" << deg;

    for(int i=deg-1;i>0;i--){//выводим столько раз(сколько у нас коэфицентов)
        if(t.GetСoefficient(i)>0){
            if(t.GetСoefficient(i)==1) stream << " + " << "x^" << i;
            else stream << " + " << t.GetСoefficient(i) << "x^" << i;

        }else if(t.GetСoefficient(i)<0)//если каждый коэфицент -цифра -> у нас вычитание
            if(t.GetСoefficient(i)==(-1))stream << " - " << "x^" << i;
            else stream << " - " << (-1)*t.GetСoefficient(i) << "x^" << i;
    }
    //степень нулевая-свободные члены(всегда идут в конце)
    if(t.GetСoefficient(0)>0) stream <<" + " << t.GetСoefficient(0) << "\n";
    else if(t.GetСoefficient(0)<0) stream << " - " << (-1)*t.GetСoefficient(0) << "\n";
    return stream;
}
