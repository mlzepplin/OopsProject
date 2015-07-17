#include<iostream>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<fstream>
using namespace std;


struct material
{
	char name[10];
	int quantity;
	int cost;
};
class project;
class tender;
class company;
class employee;
class part_time;
class full_time;
class raw_mat_supplier;
class vehicle;
class transport_company;
ostream & operator<<(ostream &cout,vehicle *v);
istream & operator>>(istream &cin,material &m);
ostream & operator<<(ostream &cout,material &m);
class project
{
	char name[20];
	char details[100];
	material *m;
	int count;			//NUMBER OF MATERIALS ADDED (NON-REDUCED)

	public:
	project()
	{
		*name=NULL;
		*details=NULL;
		m=NULL;
		count=0;
	}

	project(char *str1,char *str2,material *mat)
	{
		strcpy(name,str1);
		strcpy(details,str2);
		m=mat;
		count=0;
	}
	void update_count(int a)
	{
		count=a;
	}
	void show()
	{
		int i;
		for(i=0;i<count;i++)
		{
			cout<<endl<<"material "<<i<<" : "<<endl;
			cout<<(m+i)->name<<endl;
			cout<<(m+i)->quantity;

		}
	}
	void material_list_setter(material *m)
	{
		this->m=m;
	}
	material* getlist()
	{
		return m;
	}
	int getcount()
	{
		return count;
	}

};//DONE

class raw_mat_supplier
{
	material mat[20];
	int i;
public:
	raw_mat_supplier()
	{
		i=0;
	}
	raw_mat_supplier(ifstream &in)
	{
		i=0;
		while(!in.eof())
		{
		mat[i].quantity=0;
		in>>mat[i].name;
		in>>mat[i].cost;
		i++;
		}
	}
	void display()
	{
		for(int j=0;j<i;j++)
		{
				cout<<mat[j];
				/*cout<<mat[j].name;
				cout<<" ";
				cout<<mat[j].cost<<endl;*/
		}
	}
	int costcal(material *m,int count)
	{
		int j,k;
		int cost=0;
		for(j=0;j<count;j++)
		{
			for(k=0;k<i;k++)
			{
				if(!strcmp((m+j)->name,mat[k].name))
				{
					int temp1,temp2;
					temp1=((m+j)->quantity);
					temp2=(mat[k].cost);
					cost+=(temp1)*(temp2);
				}

			}
		}
		return cost;
	}
};//DONE

class vehicle
{
	char type[20];
	char handles[20];//to be added via main, what type of materials this vehicle type handles
	int rent;
	int capacity;
	public:
	vehicle()
	{
		*type=NULL;
		*handles=NULL;
		rent=0;
		capacity=0;
	}
	vehicle(char*t,char* h,int r,int c)
	{
		strcpy(type,t);
		strcpy(handles,h);
		rent=r;
		capacity=c;
	}
	friend ostream & operator<<(ostream &cout,vehicle *v);
	/*{
		cout<<type<<endl;
		cout<<handles<<endl;
		cout<<rent<<endl;
		cout<<capacity<<endl;
	}*/
		
	int rentcal(int q)
	{
		return q*rent;
	}
	int quantitycal(int req)
	{
		float tempfloat;
		int tempint;
		tempfloat=((float)req/capacity);
		tempint=tempfloat;

		if(tempfloat!=tempint)
		{
			tempint++;
		}

		return tempint;
	}

	char* gethandles()
	{
		return handles;
	}
};



class transport_company
{
	vehicle *v[5];
	char name[20];
	public:
	transport_company()
	{
		*v=NULL;
		*name=NULL;
	}
	transport_company(char *str)
	{
		strcpy(name,str);
		*v=NULL;
	}
	vehicle* vehreturn(int a)
	{
		return v[a];
	}
	void vehicle_list_maker(ifstream &vin)
	{
		int i;
		char t[20],h[20];
		int r,c;
		for(i=0;i<5;i++)
		{
			vin>>t;
			vin>>h;
			vin>>r;
			vin>>c;
			v[i]=new vehicle(t,h,r,c);

		}
	}
	int costcal(material *m,int count)
	{
		int i,j;
		int cost=0;
		for(i=0;i<count;i++)
		{
			for(j=0;j<5;j++)
			{
				if(!strcmp((m+i)->name,(*(v+j))->gethandles()))
				{
					
					cost+=(*(v+j))->rentcal((*(v+j))->quantitycal((m+i)->quantity));
				}
			}
		}
		return cost;
	}
		
	void showlist()
	{
		for(int i=0;i<5;i++)
		{
			//(*(v+i))->show();
			cout<<*((v+i));
		}
	}
	
	
};

class tender
{
	project *p;
	raw_mat_supplier *rms;
	transport_company *tc;
	int totalcostrms;
	int totalcosttc;
	public:

	tender()
	{
		p=NULL;
		rms=NULL;
		tc=NULL;
		totalcostrms=0;
		totalcosttc=0;
	}

	tender(project *p,raw_mat_supplier *r,transport_company *t)
	{
		this->p=p;
		this->rms=r;
		this->tc=t;
		totalcostrms=0;
		totalcosttc=0;
	}

	void setproject(project *p)
	{
		this->p=p;
	}
	void setrms(raw_mat_supplier *r)
	{
		this->rms=r;
	}
	void settc(transport_company *t)
	{
		this->tc=t;
	}
	int totalcost_rms()
	{

		totalcostrms=rms->costcal(p->getlist(),p->getcount());
		return totalcostrms;
	
	}
	int totalcost_tc()
	{
		totalcosttc=tc->costcal(p->getlist(),p->getcount());
		return totalcosttc;
	}

};

class employee //abstract class
{
    protected:
	int empid;
	char name[20];
	int age;
	float fixed;
	char type;
	public :
	employee()
	{
		empid=0;
		strcpy(name," ");
		age=0;
		fixed=0.0;
		type=' ';
	}
	employee(int a,char b[],int c,float d,char e)
	{
		empid=a;
		strcpy(name,b);
		age=c;
		fixed=d;
		type=e;
	}
	virtual float calmonthlysal()=0;
	/*{
		cout<<"In employee";
		return fixed;
	}*/
	virtual char retype()=0;
	virtual void setdet(int a,char b[],int c,float d,char e,int f)=0;
	virtual ~employee()
	{

	}
};

class part_time: public employee
{
	int wageperday;
	int nodays;
	int count1;
	public :
	void setdet(int a,char b[],int c,float d,char e,int f)
	{
		empid=a;
		strcpy(name,b);
		age=c;
		fixed=d;
		type=e;
		wageperday=f;
	}
	part_time ()
	{
	wageperday=0;
	nodays=0;
	}
	part_time (int a,char b[],int c,float d,char e,int f):employee(a,b,c,d,e),wageperday(f)
	{
		count1=0;
	}
	float calmonthlysal()
	{
		//cout<<"In part_time employee";
		float ms=fixed+(calnodays()*wageperday);
		return ms;
	}
	int calnodays()
	{
		if(count1==0)
		{
			srand(time(0));
			nodays=10+(rand()%20);
			count1++;
		}
		return nodays;
	}
	char retype()
	{
		return 'p';
	}
	//friend int calempcost();
};
/*struct pdate
{
	int day;
	int month;
	int year;
};*/
class full_time :public employee
{
	int monthlybonus;
	float pensionfund;
	float empgrade;
	int count2;
	public :
	void setdet(int a,char b[],int c,float d,char e,int f)
	{
		empid=a;
		strcpy(name,b);
		age=c;
		fixed=d;
		type=e;
		monthlybonus=f;
	}
	full_time(int a,char b[],int c,float d,char e,int f):employee(a,b,c,d,e),monthlybonus(f)
	{
		count2=0;
	}
	float calmonthlysal()
	{
		//cout<<"In full_time employee";
		return fixed+monthlybonus-calpensionfund();
	}
	float calpensionfund()
	{
		pensionfund=(fixed+monthlybonus)*getempgrade();
		return pensionfund;
	}
	float getempgrade()
	{
		if(count2==0)
		{
			srand(time(0));
			empgrade=(rand()%10)/100;
			count2++;
	        }
		return empgrade;
	}
	char retype()
	{
		return 'f';
	}
	//friend int calempcost();
};


class company{

	char name[20];
	char address[20];
	int eval;
	int index;
	tender *t;
	employee *e[10];
	public:

	company()
	{
		strcpy(name," ");
		strcpy(address," ");
		eval=0;
		index=0;
		t=NULL;
		for(int i=0;i<10;i++)
		{
			e[i]=NULL;
		}
	}

	company(char*n,char*a,int ev,int ind)
	{
		strcpy(name,n);
		strcpy(address,a);
		eval=ev;
		index=ind;
		t=NULL;
		for(int i=0;i<10;i++)
		{
			e[i]=NULL;
		}
	}

	int calempcost()
	{
		int sum=0;
		for(int i=0;i<7;i++)
		{
			sum=sum+e[i]->calmonthlysal();
		}
		return sum;
	}

	void tenderalloc(project *p,raw_mat_supplier *r,transport_company *tc)
	{
		t=new tender(p,r,tc);
	}
	void empalloc()
	{
		fstream ep;
		int i;
		char ch;
		int mb;
		int wpd;
		int eid;
		char na[20];
		int ag;
		float fx;
		if(index==1)
		{
			ep.open("/home/rishabh/Desktop/ak1.txt",ios::in);
		}
		else if(index==2)
		{
			ep.open("/home/rishabh/Desktop/ak2.txt",ios::in);
		}
		else if(index==3)
		{
			ep.open("/home/rishabh/Dekstop/ak3.txt",ios::in);
		}
		while(!ep.eof())
		{

			ep>>ch;
			ep>>eid;
			ep>>na;
			ep>>ag;
			ep>>fx;
			if(ch=='p')
			{
				ep>>wpd;
				e[i]=new part_time(eid,na,ag,fx,ch,wpd);
			}
			else if(ch=='f')
			{
				ep>>mb;
				e[i]=new full_time(eid,na,ag,fx,ch,mb);
			}
		}
		ep.close();
	}
	tender* gettender()
	{
		return t;
	}
		
};
char mat_main_setter(material m[],int i)
{
	char ch;
	cout<<endl<<endl<<"enter material:"<<endl;
				cin>>m[i];
				cout<<endl<<"another material ? (y/n)";
				cin>>ch;
				return ch;
}

istream & operator>>(istream &cin,material &m)
{
	m.cost=0;
	cout<<"enter material name : ";
	cin>>m.name;
	cout<<"enter quantity : ";
	cin>>m.quantity;
	return cin;
}

ostream & operator<<(ostream &cout,material &m)
{
	cout<<m.name;
	cout<<" ";
	cout<<m.cost<<endl;
	return cout;
}
void erthrower(ifstream &in)
{
	in.exceptions(in.failbit);
}

ostream & operator<<(ostream &cout,vehicle *v)
{
	cout<<v->type<<endl;
	cout<<v->handles<<endl;
	cout<<v->rent<<endl;
	cout<<v->capacity<<endl;
	return cout;
}

int main()
{
	//transport company objects

	transport_company t[3]={
				transport_company("uppal_transport"),
				transport_company("gupta_transport"),
				transport_company("singh_transport")
				};



	//INPUTING VEHICLES


	//initialising streams
	ifstream vin1("/home/rishabh/Desktop/vehicle_files/vin1.txt");
	ifstream vin2("/home/rishabh/Desktop/vehicle_files/vin2.txt");
	ifstream vin3("/home/rishabh/Desktop/vehicle_files/vin3.txt");

	//file exception handling
	try
	{
		erthrower(vin1);
		erthrower(vin2);
		erthrower(vin3);
	}
	catch(const ios_base::failure& e)
	{
		cout<<"caunght ios exception \n"
		<<"Explanatory string: " << e.what()<<'\n';
	}
	
	//making vehicle lists
	t[0].vehicle_list_maker(vin1);
	t[1].vehicle_list_maker(vin2);
	t[2].vehicle_list_maker(vin3);
	

	//INPUTING RAW MATERIAL SUPPLIERS


	//material list
	material mat_main[20];

	//initialising material streams
	ifstream in1("/home/rishabh/Desktop/supplier_files/supplier1.txt");
	ifstream in2("/home/rishabh/Desktop/supplier_files/supplier2.txt");
	ifstream in3("/home/rishabh/Desktop/supplier_files/supplier3.txt");
	
	//raw material supplier objects
	raw_mat_supplier rms[3]={
				raw_mat_supplier(in1),
				raw_mat_supplier(in2),
				raw_mat_supplier(in3)
				};

//-----------------------------------------------------
	//USER INPUT FOR PROJECT STARTS
//-----------------------------------------------------

	int i=1;
	int y;
	char c;
	cout<<"enter project name:"<<endl;
	char temp1[20];
	cin>>temp1;			
	cout<<"enter project details:"<<endl;
	char temp2[100];
	cin>>temp2;
	project p(temp1,temp2,mat_main);
	c=mat_main_setter(mat_main,0);

		while(c=='y')
		{
			c=mat_main_setter(mat_main,i);
			if(i<19)
			{
				i++;
			}
			else
			{
				cout<<"project material limit exceeded";
				break;
			}

		}
	/*catch(int i)
	{
		cout<<"project material limit exceeded";
		cout<<"can't add more materials";
	}*/

	//UPDATING COUNT OF PROJECT 
	p.update_count(i);

	//MATERIALS ASSIGNED TO PROJECT
	p.material_list_setter(mat_main);

	//CREATING COMPANY OBJECT
	company cp[3]={
			company("company1","delhi",210,1),
			company("company2","mumbai",234,2),
			company("company3","kolkata",226,3)
			};
	//ASSIGNING TENDER AND EMPLOYEE
						
	for(y=0;y<3;y++)
	{
		cp[y].tenderalloc(&p,&rms[y],&t[y]);
		cp[y].empalloc();
	}
	int r,ti,su;
	tender *w;
	/*for(y=0;y<3;y++)
	{
		cout<<"company: "<<y<<endl;
		w=cp[y].gettender();
		r=(w->totalcost_rms());
		cout<<"raw material cost : "<<r<<endl;
		ti=(w->totalcost_tc());
		cout<<"transport company cost : "<<ti<<endl;
		//su=cp[y].calempcost();
		//cout<<"company employee cost"<<su<<endl<<endl;
	}

	vehicle *temp;
	//printing vehicle lists of main()
	for(i=0;i<5;i++)
	{
		cout<<"vin1 : ";
		temp=t[0].vehreturn(i);
		//temp->show();
		cout<<temp;
		cout<<endl<<"vin2 : ";
		temp=t[1].vehreturn(i);
		//temp->show();
		cout<<temp;
		cout<<endl<<"vin3 : ";
		temp=t[2].vehreturn(i);
		//temp->show();
		cout<<temp;
		cout<<endl<<endl;
	}*/
	
	tender t1(&p,&rms[1],&t[1]);
	t1.totalcost_rms();
	
	cout<<"done";

}
