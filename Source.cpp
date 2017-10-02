#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "stack.h"
using namespace std;
struct node
{
	char *ptr;
	bool empty;
};

ifstream fin;
ofstream fout;
void conversion(int num,char _num[])
{
	if(num<9)
	{
		num=num+(int)'0';
		_num[0]=(char)num;
		_num[1]='\0';
	}
	else
	{
	int num1;
	char *temp=new char[5];
	int j,l;
	for(l=0;num>9;l++)
	{
		num1=num%10;	
		j = num1 + (int)'0'; 
		temp[l] = (char)j;
		num=num/10;
	}
	j = num + (int)'0'; 
	temp[l] = (char)j;
	temp[l+1]='\0';
	int size=strlen(temp);
	int t,q;
	for(t=size-1,q=0;t>0;t--,q++)
	{
		_num[q]=temp[t];
	}
	_num[q]=temp[t];
	_num[q+1]='\0';
	}
}
void save(node arr[])
{
	/*cout<<"in save\n";*/
	ofstream fout;
	fout.open("disk.txt");
	if(fout.is_open())
	{
		for(int i=0;i<100;++i)
		{
			for(int k=0;k<100;k++)
			{
				fout<<arr[i].ptr[k];

			}
		}
		fout.close();
	}
	else
	{
		cout<<"Could not open File";
	}
	fout.open("disk2.txt");
	if(fout.is_open())
	{
		for(int i=0;i<100;++i)
		{
			fout<<arr[i].empty;
			fout<<" ";
		}
		fout.close();
	}
	else
	{
		cout<<"Could not open File";
	}
}
void initializearr(node arr[])
{
	/*cout<<"in initializearr\n";*/
	
		for(int i=0;i<100;++i)
		{
			if(i==0)
			{
				arr[i].empty=false;
			}
			for(int k=0;k<100;k++)
			{
				if(k==0)
				arr[i].ptr[k]='\0';
				else
				arr[i].ptr[k]=' ';
			}
		}
		arr[0].empty=false;
}
void createdisk(node arr[])
{
	/*cout<<"in createdisk\n";*/
	initializearr(arr);
	save(arr);
}
void intialize(node arr[])
{
	/*cout<<"in intialize\n";*/
	fin.open("disk.txt");
	if(!fin.is_open())
	{
		createdisk(arr);
	}
	else
	{
		initializearr(arr);
		for(int i=0;i<100;++i)
		{
			for(int k=0;k<100;k++)
			{
				fin>>arr[i].ptr[k];
			}
		}
		fin.close();

		fin.open("disk2.txt");
		if(fin.is_open())
		{
			for(int i=0;i<100;++i)
			{
				fin>>arr[i].empty;
			}
			fin.close();
		}
		/*for(int i=0;i<100;i++)
		{
			cout<<arr[0].ptr[i];
		}
		for(int i=0;i<100;i++)
		{
			cout<<arr[i].empty;
		}*/
	}
	arr[0].empty=false;

}
int emptyblock(node arr[])
{
	int i=1;
	for(;i<100;i++)
	{
		if(arr[i].empty==true)
		{
			break;
		}
	}
	arr[i].empty=false;
	return i;
}
void makefile(string _name,node arr[],int type,int dir)//1 for directory 0 for textfile
{
	char* eblock=new char[5];
	conversion(emptyblock(arr),eblock);
	int size=strlen(eblock);
	int empty=atoi(eblock);
	
	for(int k=0;k<100;k++)
	{
		if(arr[dir].ptr[k]=='\0')
		{
			arr[dir].ptr[k]='|';
			for(int i=0;_name[i]!='\0';++i)
			{
				arr[dir].ptr[++k]=_name[i];
			}
			arr[dir].ptr[++k]='[';
			for(int l=0;eblock[l]!='\0';l++)
			{
				arr[dir].ptr[++k]=eblock[l];
			}
			arr[dir].ptr[++k]=']';
			arr[dir].ptr[++k]='/';
			type=type+(int)'0';
			arr[dir].ptr[++k]=(char)type;
			arr[dir].ptr[++k]='/';
			arr[dir].ptr[++k]='\0';
			arr[empty].empty=false;
			break;
		}
	}
		save(arr);

}
bool search(string _name,node arr[],int currdir)
{
	int i,j,k;
	bool flag=false;
			for (i=0,j=0;arr[currdir].ptr[i]!='\0';i++)
			{
				if (arr[currdir].ptr[i]==_name[j])
				{
					for(k=i+1,j=j+1;_name[j]!='\0';j++)
					{
						if (arr[currdir].ptr[k]==_name[j])
						{
							flag=true;
							k++;
						}
						else
						{
				    			flag=false;
				    			break;
						}
					}
					if(arr[currdir].ptr[k]=='[')
					{
						flag=true;
					}
					else 
					{
						flag=false;
					}
					if(flag==true)
						break;
				}
			}
			return flag;
}
int getblocknum(string _name,node arr[],int currdir)
{
	int i,j,k;
	bool flag=false;
	char temp[5];
			for (i=0,j=0;arr[currdir].ptr[i]!='\0';i++)
			{
				if (arr[currdir].ptr[i]==_name[j])
				{
					for(k=i+1,j=j+1;_name[j]!='\0';j++)
					{
						if (arr[currdir].ptr[k]==_name[j])
						{
							flag=true;
							k++;
						}
						else
						{
				    			flag=false;
				    			break;
						}
					}
					if(arr[currdir].ptr[k]=='[')
					{
						flag=true;
					}
					else 
					{
						flag=false;
					}
					if(flag==true)
						break;
				}
			}
			if(flag==true)
			{
				int l;
				int a=0;
				for(l=k+1;arr[currdir].ptr[l]!=']';l++,a++)
				{
					temp[a]=arr[currdir].ptr[l];
				}
				temp[a]='\0';
				return(atoi(temp));
			}
			else
			{
				cout<<"File does not exist";
			}
}
int gettype(string _name,node arr[],int currdir)
{
	int i,j,k;
	bool flag=false;
	char *temp=new char[5];
			for (i=0,j=0;arr[currdir].ptr[i]!='\0';i++)
			{
				if (arr[currdir].ptr[i]==_name[j])
				{
					for(k=i+1,j=j+1;_name[j]!='\0';j++)
					{
						if (arr[currdir].ptr[k]==_name[j])
						{
							flag=true;
							k++;
						}
						else
						{
				    			flag=false;
				    			break;
						}
					}
					if(arr[currdir].ptr[k]=='[')
					{
						flag=true;
					}
					else 
					{
						flag=false;
					}
					if(flag==true)
						break;
				}
			}
			if(flag==true)
			{
				int l;
				int a=0;
				for(l=k+1;arr[currdir].ptr[l]!='/';l++,a++)
				{
				}
				temp[0]=arr[currdir].ptr[l+1];
				temp[1]='\0';
				return(atoi(temp));
			}
			else
			{
				cout<<"File does not exist";
			}
}
void contents(node arr[],int dir)
{
	for(int i=1;arr[dir].ptr[i]!='\0';i++)
	{
		if(arr[dir].ptr[i]=='|')
		{
			i++;
		}
		else if(arr[dir].ptr[i]=='[')
		{
			for(;arr[dir].ptr[i]!='/';i++)
			{
				
			}
			i=i+2;
			cout<<'\n';
		}
		else
		{
			cout<<arr[dir].ptr[i];
		}
	}
}
void writeinfile(string _name,char str[],node arr[],int dir)
{
	int block=getblocknum(_name,arr,dir);
	int eblock=emptyblock(arr);
	char temp[5];
	int i;
	int k=0;
	conversion(eblock,temp);
	arr[block].ptr[0]='|';
	arr[block].ptr[1]='[';
	for(i=2;temp[k]!='\0';k++,i++)
	{
		arr[block].ptr[i]=temp[k];
	}
	arr[block].ptr[i]=']';
	++i;
	arr[block].ptr[i]='/';
	i++;
	arr[block].ptr[i]='3';
	i++;
	arr[block].ptr[i]='/';
	i++;
	arr[block].ptr[i]='\0';

	arr[eblock].ptr[0]='|';
	for(i=0;str[i]!='\0';i++)
	{
		arr[eblock].ptr[i+1]=str[i];
	}
	arr[eblock].ptr[i+1]='\0';
	save(arr);
}
void changedirectory(node arr[],int &dir,string _name)
{
	dir=getblocknum(_name,arr,dir);
}
void readfile(string _name,node arr[],int dir)
{
	int block=getblocknum(_name,arr,dir);
	char* temp=new char [5];
	int k=0;
	for(int i=2;arr[block].ptr[i]!=']';i++)
	{
		temp[k]=arr[block].ptr[i];
		k++;
	}
	temp[k]='\0';
	block=atoi(temp);
	for(int i=1;arr[block].ptr[i]!='\0';i++)
	{
		cout<<arr[block].ptr[i];
	}
}
int getstartingindex(string _name,node arr[],int dir)
{
	int i,j,k;
	bool flag=false;
			for (i=0,j=0;arr[dir].ptr[i]!='\0';i++)
			{
				if (arr[dir].ptr[i]==_name[j])
				{
					for(k=i+1,j=j+1;_name[j]!='\0';j++)
					{
						if (arr[dir].ptr[k]==_name[j])
						{
							flag=true;
							k++;
						}
						else
						{
				    			flag=false;
				    			break;
						}
					}
					if(arr[dir].ptr[k]=='[')
					{
						flag=true;
					}
					else 
					{
						flag=false;
					}
					if(flag==true)
						break;
				}
			}
		  if(flag==true)
		  {
			  return k-j;
		  }
		  else 
		  {
			  return 0;

		  }
}
void clearblock(int block,node arr[],bool flag)
{
	int blocknum;
	if(flag==true)
	{
		char * temp=new char[5];
				int l;
				int a=0;
				for(l=2;arr[block].ptr[l]!=']';l++,a++)
				{
					temp[a]=arr[block].ptr[l];
				}
				temp[a]='\0';
				blocknum=atoi(temp);
	}
	for(int i=0;i<100;i++)
	{
		arr[block].ptr[i]=' ';
	}
	if(flag==true)
	{
		clearblock(blocknum,arr,false);
	}

}
void deletefile(string _name,node arr[],int dir)
{
	int block=getblocknum(_name,arr,dir);
	int type=gettype(_name,arr,dir);
	int index=getstartingindex(_name,arr,dir);
	arr[dir].ptr[index-1]=' ';
	int j;
	arr[block].empty=true;
	int size=_name.size();
	for(j=index;arr[dir].ptr[j]!='/';j++)
	{
		arr[dir].ptr[j]=' ';
	}
	arr[dir].ptr[j]=' ';
	j++;
	arr[dir].ptr[j]=' ';
	j++;
	arr[dir].ptr[j]=' ';
	/*int k,i;
	if(block<9)
	{
		i=size;
	}
	else if(block>9)
	{
		i=size+7;
	}
	for(;i>-1;i--)
	{
		for(k=j+1;arr[dir].ptr[k]!='\0';k++)
		{
			arr[dir].ptr[k-1]=arr[dir].ptr[k];
		}
		arr[dir].ptr[k-1]=arr[dir].ptr[k];
	}*/
	if(type==0)
	{
		clearblock(block,arr,true);
	}
	save(arr);


}
void print(node arr[])
{
	for(int j=0;j<100;j++)
	{
		if(arr[j].empty==false)
		{
			for(int i=0;arr[j].ptr[i]!='\0';i++)
			{
				cout<<arr[j].ptr[i];
			}
			cout<<'\n';
		}
	}
}
int main()
{
	node arr[100];
	for(int i=0;i<100;++i)
	{
		arr[i].ptr=new char[100];
		if(i==0)
		{
			arr[i].empty=false;
		}
		else
		{
			arr[i].empty=true;
		}
	}
	intialize(arr);
	int option=0;
	string name;
	char str[100];
	int currdir=0;
	stack<int> previousdirectory;
	while(1)
	{
		cout<<"Enter what you want to do\n1.Create a folder\n2.Create a textfile\n3.See contents of current directory\n4.Search for file in directory\n5.Write in file\n6.Change Directory\n7.Go to previous directory\n8.Read from file\n9.Delete a file\n10.Print File\n11.Quit\n";
		cin>>option;
		if(option==1)
		{
			cout<<"Enter name of folder\n";
			cin>>name;
			makefile(name,arr,1,currdir);
		}
		else if(option==2)
		{
			cout<<"Enter name of text file\n";
			cin>>name;
			makefile(name,arr,0,currdir);
		}
		else if(option==3)
		{
			contents(arr,currdir);
		}
		else if(option==4)
		{
			cout<<"Enter name of file";
			cin>>name;
			if(search(name,arr,currdir))
			{
				cout<<"Found\n";
			}
			else
				cout<<"Does not exist\n";

		}
		else if(option==5)
		{
			cout<<"Enter name of .txt file\n";
			cin>>name;
			cout<<"Enter text you want to enter\n";
	/*		cin>>str;*/
			cin.ignore();
			std::cin.getline(str,100);
			writeinfile(name,str,arr,currdir);
		}
		else if(option==6)
		{
			cout<<"Enter name of dirictory you want to enter";
			cin>>name;
			previousdirectory.push(currdir);
			changedirectory(arr,currdir,name);
		}
		else if(option==7)
		{
			if(currdir==0)
			{
				cout<<"Already in Desktop";
			}
			else
			{
				previousdirectory.pop(currdir);
				cout<<"Now in previous directory";
			}
		}
		else if(option==8)
		{
			cout<<"Enter file you want to read from\n";
			cin>>name;
			readfile(name,arr,currdir);
		}
		else if (option==9)
		{
			cout<<"Enter Name of file";
			cin>>name;
			deletefile(name,arr,currdir);
		}
		else if(option==10)
		{
			print(arr);
		}
		else if(option==11)
		{
			break;
		}
		Sleep(100);
		getch();
		system("cls");
	}
	//string name;
	//intialize(arr);
	////cin>>name;
	////cout<<search(name,arr,0);
	////cin>>name;
	////cout<<search(name,arr,0);
	//cin>>name;
	//makefile(name,arr,0);
	//cin>>name;
	//makefile(name,arr,1);
	//cin>>name;
	//makefile(name,arr,0);
	
	return 0;
}